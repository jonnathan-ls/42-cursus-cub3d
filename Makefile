# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#              #
#    Updated: 2025/08/09 19:45:57 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = cub3d

LIBFT_DIR = ./libraries/libft
OBJS_DIR = ./objects
INCS_DIR = ./includes

MAIN_SRCS = sources/main.c

SOURCES = ${MAIN_SRCS}

OBJS = $(SOURCES:%.c=$(OBJS_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
MATH = -lm

LIBS = $(LIBFT) $(MATH)

CFLAGS = -Wall -Wextra -Werror -g -I$(INCS_DIR) -I$(LIBFT_DIR)/includes -O2

ESCAPE = \033[
RESET = $(ESCAPE)0m
BOLD = $(ESCAPE)1m
GREEN = $(ESCAPE)32m
YELLOW = $(ESCAPE)33m
BLUE = $(ESCAPE)34m
MAGENTA = $(ESCAPE)35m
CYAN = $(ESCAPE)36m
WHITE = $(ESCAPE)37m
ORANGE = $(ESCAPE)38;5;208m

VERBOSE ?= 0

all: header $(NAME)

$(LIBFT):
	$(call compile_library,$(LIBFT_DIR),libft)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(BLUE)$(BOLD)🔗  Linking files ...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(GREEN)$(BOLD)🚀  Cub3D compiled successfully!$(RESET)"
	@echo
	@rm -f .header_lock

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call compile_project,$<)

clean: header
	@printf "$(MAGENTA)$(BOLD)🗑️   Cleaning up object files $(RESET)"
	@rm -f $(OBJS)
	@$(call clean_library,$(LIBFT_DIR),libft)
	@echo "$(GREEN)$(BOLD)✓ Removed objects!$(RESET)\n"
	@rm -f .header_lock

fclean: header
	@printf "$(MAGENTA)$(BOLD)🗑️   Cleaning up object files $(RESET)"
	@rm -f $(OBJS)
	@echo "$(GREEN)$(BOLD)✓ Completed!$(RESET)"
	@printf "$(MAGENTA)$(BOLD)🗑️   Cleaning up libraries $(RESET)"
	@$(call fclean_library,$(LIBFT_DIR),libft)
	@echo "$(GREEN)$(BOLD)✓ Completed!$(RESET)"
	@printf "$(MAGENTA)$(BOLD)🗑️   Cleaning executable $(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)✓ Completed!$(RESET)"
	@rm -f .header_lock
	@echo

re:
	@rm -f .header_lock
	@$(MAKE) --no-print-directory -s fclean all

.PHONY: all clean fclean re header

# **************************************************************************** #
# Libraries Compilation - Generic function for any library in libraries/
# **************************************************************************** #

define compile_library
    $(eval LIB_NAME=$(2))
    $(eval LIB_DIR=$(1))
    $(eval BAR_SIZE=30)
    $(eval PROGRESS_MSG=🏗️   Building $(LIB_NAME) $(RESET))
    $(eval SUCCESS_MSG=🏗️   $(LIB_NAME) $(GREEN)$(BOLD)✓ Concluído!$(RESET))
    $(eval FINAL_BAR=$(shell printf '▓%.0s' $$(seq 1 $(BAR_SIZE))))

    @printf "$(BLUE)$(BOLD)$(PROGRESS_MSG)\n"
    @if [ -d "$(LIB_DIR)" ]; then \
        if [ $(VERBOSE) -eq 1 ]; then \
            echo "$(CYAN)$(BOLD)📦  Compiling library \
			$(RESET)$(CYAN)$(LIB_NAME)$(RESET) in $(LIB_DIR)"; \
            make --no-print-directory -C $(LIB_DIR); \
            printf "$(BLUE)$(BOLD)$(SUCCESS_MSG)\n"; \
        else \
            echo -n "🔄  "; \
            make --no-print-directory -C $(LIB_DIR) > /dev/null 2>&1 & \
            pid=$$!; \
            i=0; \
            while kill -0 $$pid 2>/dev/null; do \
                printf "$(YELLOW)▓$(RESET)"; \
                sleep 0.1; \
                i=$$((i+1)); \
                if [ $$i -gt $(BAR_SIZE) ]; then \
                    break; \
                fi; \
            done; \
            wait $$pid; \
            printf "\033[1A\r"; \
            printf "$(BLUE)$(BOLD)$(SUCCESS_MSG)\n"; \
            printf "🔄  $(YELLOW)$(FINAL_BAR)$(RESET) \n"; \
        fi; \
    fi
endef

define clean_library
    @if [ -d "$(1)" ]; then \
        make --no-print-directory -C $(1) clean > /dev/null 2>&1; \
    fi
endef

define fclean_library
    @if [ -d "$(1)" ]; then \
        make --no-print-directory -C $(1) fclean > /dev/null 2>&1; \
    fi
endef

# **************************************************************************** #
# Header display - only once per make execution
# **************************************************************************** #
PROJECT_NAME = Cub3D: Relive History with the First FPS Ever Created
AUTHORS = $(YELLOW)jonnathan-ls e peda-cos$(RESET)
header:
	@if [ ! -f .header_lock ]; then \
		touch .header_lock; \
		echo; \
		echo "$(ORANGE)$(BOLD)🕹️   ${PROJECT_NAME}$(RESET)"; \
		echo "$(GREEN)$(BOLD)👥  Autores:$(RESET) $(AUTHORS)"; \
		echo ;\
	fi

# **************************************************************************** #
# Detect terminal width and adjust behavior
# **************************************************************************** #
TERM_WIDTH := $(shell tput cols 2>/dev/null || echo 80)
SAFE_WIDTH := $(shell echo $$(($(TERM_WIDTH) - 10)))
PROGRESS_WIDTH := $(shell echo $$(($(SAFE_WIDTH) > 50 ? 30 : $(SAFE_WIDTH) - 20)))

# **************************************************************************** #
# Define the progress bar and verbose output functions - CLEAN & SIMPLE
# **************************************************************************** #
TOTAL_FILES := $(words $(SOURCES))
COMPILED_COUNT = 0

define compile_project
    $(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT)+1))))
    $(eval SHORT_PATH=$(shell echo $(1) | sed 's|^.*/||'))
    $(eval BAR_SIZE=20)
    $(eval PERCENT=$(shell if [ $(TOTAL_FILES) -gt 0 ]; then \
	echo $$(($(COMPILED_COUNT)*100/$(TOTAL_FILES))); else echo 0; fi))
    $(eval BARS=$(shell if [ $(TOTAL_FILES) -gt 0 ]; then \
	echo $$(($(COMPILED_COUNT)*$(BAR_SIZE)/$(TOTAL_FILES))); else echo 0; fi))
    $(eval REMAINING=$(shell if [ $(BARS) -ge $(BAR_SIZE) ]; then \
	echo 0; else echo $$(($(BAR_SIZE) - $(BARS))); fi))
    $(eval PROGRESS=$(shell printf '█%.0s' $$(seq 1 $(BARS))))
    $(eval EMPTY=$(shell if [ $(REMAINING) -gt 0 ]; then \
	printf '░%.0s' $$(seq 1 $(REMAINING)); fi))
	$(eval PROGRESS_BAR=$(RESET)$(GREEN)$(PROGRESS)$(WHITE)$(EMPTY)$(RESET))

	@echo 
	@printf "$(BLUE)$(BOLD)🏗️   Building Cub3D $(RESET)\n"
    @if [ $(VERBOSE) -eq 1 ]; then \
        echo "$(CYAN)$(BOLD)📄  Compiling $(RESET)$(CYAN)$(SHORT_PATH)$(RESET) \
		($(COMPILED_COUNT)/$(TOTAL_FILES))"; \
		echo "$(GREEN)$(BOLD)✅  Compilation completed!$(RESET)\n"; \
    else \
        printf "\r\033[K$(YELLOW)$(BOLD)🔄  $(PROGRESS_BAR) \
		$(PERCENT)%% $(CYAN)$(SHORT_PATH)$(RESET)"; \
        if [ $(COMPILED_COUNT) -eq $(TOTAL_FILES) ]; then \
            printf "\n$(GREEN)$(BOLD)✅  Compilation completed!$(RESET)\n\n"; \
        fi; \
    fi
endef