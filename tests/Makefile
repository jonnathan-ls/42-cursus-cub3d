# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#              #
#    Updated: 2025/08/16 19:03:38 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../configs/variables.mk
include ../configs/functions.mk

NAME = cub3dTestsCases

MLX42_DIR = ../libraries/mlx42
LIBFT_DIR = ../libraries/libft
OBJS_DIR = ../objects
INCS_DIR = ../includes

SHARED_SRCS = ../sources/shared/memory-manager.c
MODULES_SRCS = $(SHARED_SRCS)

CORE_SRCS = sources/core.c sources/expects.c

CASES_SRCS = \
	cases/shared/shared_tests.c \
	cases/shared/memory_manager.c

SOURCES =  sources/tests.c ${MODULES_SRCS} ${CORE_SRCS} ${CASES_SRCS}
TOTAL_FILES := $(words $(SOURCES)) # For progress_bar logic

CFLAGS = -Wall -Wextra -Werror -g -O2 $(INCLUDES) -I includes
OBJS = $(SOURCES:%.c=$(OBJS_DIR)/%.o)

all: header $(NAME)

print_build:
	@printf "$(BLUE)$(BOLD)🏗️   Building Cub3D $(RESET)\n"

libft:
	$(call compile_library,$(LIBFT_DIR),libft)

mlx42:
	$(call compile_library,$(MLX42_DIR),MLX42)

$(NAME): libft mlx42 $(OBJS)
	@printf "$(BLUE)$(BOLD)🔗  Linking files ...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) $(MINILIBX_LIBS)
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
	@rm -rf $(MLX42_DIR)/build
	@echo "$(GREEN)$(BOLD)✓ Completed!$(RESET)"
	@printf "$(MAGENTA)$(BOLD)🗑️   Cleaning executable $(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)✓ Completed!$(RESET)"
	@rm -f .header_lock
	@echo

re:
	@rm -f .header_lock
	@$(MAKE) --no-print-directory -s fclean all

tests_cases: all
	@printf "$(PURPLE)$(BOLD)🧪  Running Tests Cases ...$(RESET)\n\n"
	@valgrind -s --leak-check=full --show-reachable=yes --track-origins=yes \
	--track-fds=yes --show-leak-kinds=all --log-file=valgrind.log ./$(NAME)
	@cat valgrind.log | grep LEAK > /dev/null && \
	echo "$(RED)$(BOLD)💧  Memory leak detected!$(RESET)" \
	&& echo "$(YELLOW)📄  Verifies 'valgrind.log' for details." \
	|| echo "$(GREEN)$(BOLD)🧱  No memory leak detected!$(RESET)"
	@echo
	@rm -f .header_lock

header:
	@if [ ! -f .header_lock ]; then \
		touch .header_lock; \
		echo; \
		echo "$(ORANGE)$(BOLD)🕹️   ${PROJECT_NAME}$(RESET)"; \
		echo "$(GREEN)$(BOLD)👥  Authors:$(RESET) $(AUTHORS)"; \
		echo ;\
	fi

.PHONY: all clean fclean re header mlx42 libft test