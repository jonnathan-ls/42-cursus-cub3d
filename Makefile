# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#              #
#    Updated: 2025/09/20 16:01:35 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include configs/variables.mk
include configs/functions.mk

NAME = cub3d

SHARED_SRCS = sources/shared/memory-manager.c
MAIN_SRCS = sources/main.c sources/mlx42.c
PARSER_SRCS = \
	sources/parser/validate_extension.c \
	sources/parser/parser_entry.c \
	sources/parser/parse_headers.c \
	sources/parser/parse_headers_utils.c \
	sources/parser/parse_textures.c \
	sources/parser/parse_colors.c \
	sources/parser/collect_map_lines.c \
	sources/parser/normalize_map.c \
	sources/parser/validate_map_chars.c \
	sources/parser/locate_player.c \
	sources/parser/check_closed.c \
	sources/parser/free_config.c \
	sources/parser/parser_errors.c

ENGINE_SRCS = \
	sources/engine/engine_init.c \
	sources/engine/engine_destroy.c \
	sources/engine/engine_textures.c \
	sources/engine/player_update.c \
	sources/engine/player_rotate.c \
	sources/engine/engine_loop.c 

RAY_SRCS = \
	sources/engine/ray_init.c \
	sources/engine/ray_dda.c \
	sources/engine/ray_distance.c

RENDER_SRCS = \
	sources/render/render_wall.c \
	sources/render/render_strip.c \
	sources/render/frame.c \
	sources/render/minimap.c \
	sources/render/minimap_utils.c

SOURCES = ${MAIN_SRCS} ${SHARED_SRCS} ${PARSER_SRCS} \
	${ENGINE_SRCS} ${RAY_SRCS} ${RENDER_SRCS}
TOTAL_FILES := $(words $(SOURCES)) # For progress_bar logic

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

norminette:
	@norminette $(INCS_DIR) $(LIBFT_DIR) $(SOURCES)

test:
	@$(MAKE) --no-print-directory -C tests tests_cases

valgrind: all
	@rm	-f .header_lock
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--track-fds=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	./$(NAME)

header:
	@if [ ! -f .header_lock ]; then \
		touch .header_lock; \
		echo; \
		echo "$(ORANGE)$(BOLD)🕹️   ${PROJECT_NAME}$(RESET)"; \
		echo "$(GREEN)$(BOLD)👥  Authors:$(RESET) $(AUTHORS)"; \
		echo ;\
	fi

.PHONY: all clean fclean re header norminette valgrind mlx42 libft test
