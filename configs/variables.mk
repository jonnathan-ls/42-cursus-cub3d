# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    variables.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#              #
#    Updated: 2025/10/06 03:12:27 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

MLX42_DIR = ./libraries/mlx42
LIBFT_DIR = ./libraries/libft
OBJS_DIR = ./objects
INCS_DIR = ./includes

LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MLX42_DIR)/build/libmlx42.a

MINILIBX_INCLUDES = -I$(MLX42_DIR)/include
MINILIBX_LIBS = -ldl -lglfw -pthread -lm
INCLUDES = -I$(INCS_DIR) -I$(LIBFT_DIR)/includes $(MINILIBX_INCLUDES)
CFLAGS = -Wall -Wextra -Werror -O2 $(INCLUDES)

ESCAPE = \033[
RED = $(ESCAPE)31m
RESET = $(ESCAPE)0m
BOLD = $(ESCAPE)1m
GREEN = $(ESCAPE)32m
YELLOW = $(ESCAPE)33m
BLUE = $(ESCAPE)34m
MAGENTA = $(ESCAPE)35m
CYAN = $(ESCAPE)36m
WHITE = $(ESCAPE)37m
ORANGE = $(ESCAPE)38;5;208m
PURPLE = $(ESCAPE)38;5;129m

v ?= 0
V ?= $(v)
VERBOSE ?= $(V)
BAR_SIZE=20

# **************************************************************************** #
# Header display - only once per make execution
# **************************************************************************** #
PROJECT_NAME = Cub3D: Relive History with the First FPS Ever Created
AUTHORS = $(YELLOW)jonnathan-ls e peda-cos$(RESET)

# **************************************************************************** #
# Detect terminal width and adjust behavior
# **************************************************************************** #
TERM_WIDTH := $(shell tput cols 2>/dev/null || echo 80)
SAFE_WIDTH := $(shell echo $$(($(TERM_WIDTH) - 10)))
PROGRESS_WIDTH := $(shell echo $$(($(SAFE_WIDTH) > 50 ? 30 : $(SAFE_WIDTH) - 20)))

# **************************************************************************** #
# Define the progress bar and verbose output functions - CLEAN & SIMPLE
# **************************************************************************** #
COMPILED_COUNT = 0
TITLE_FLAG = 0
PRINT_COMPLETED = $(GREEN)$(BOLD)✅  Build completed!$(RESET)
