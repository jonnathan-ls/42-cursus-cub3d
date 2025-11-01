# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 20:44:31 by jlacerda          #+#    #+#              #
#    Updated: 2025/10/31 23:15:05 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(INCLUDES_DIR)

SRCS_DIR = ./sources
OBJS_DIR = ./objects
INCLUDES_DIR = ./includes

SOURCES = \
	$(SRCS_DIR)/ft_atoi.c \
	$(SRCS_DIR)/ft_bzero.c \
	$(SRCS_DIR)/ft_calloc.c \
	$(SRCS_DIR)/ft_isalnum.c \
	$(SRCS_DIR)/ft_isalpha.c \
	$(SRCS_DIR)/ft_isascii.c \
	$(SRCS_DIR)/ft_isdigit.c \
	$(SRCS_DIR)/ft_isprint.c \
	$(SRCS_DIR)/ft_memchr.c \
	$(SRCS_DIR)/ft_memcmp.c \
	$(SRCS_DIR)/ft_memcpy.c \
	$(SRCS_DIR)/ft_memmove.c \
	$(SRCS_DIR)/ft_memset.c \
	$(SRCS_DIR)/ft_putchar_fd.c \
	$(SRCS_DIR)/ft_putendl_fd.c \
	$(SRCS_DIR)/ft_putnbr_fd.c \
	$(SRCS_DIR)/ft_putstr_fd.c \
	$(SRCS_DIR)/ft_split.c \
	$(SRCS_DIR)/ft_strchr.c \
	$(SRCS_DIR)/ft_strdup.c \
	$(SRCS_DIR)/ft_striteri.c \
	$(SRCS_DIR)/ft_strjoin.c \
	$(SRCS_DIR)/ft_strlcat.c \
	$(SRCS_DIR)/ft_strlcpy.c \
	$(SRCS_DIR)/ft_strlen.c \
	$(SRCS_DIR)/ft_strmapi.c \
	$(SRCS_DIR)/ft_strncmp.c \
	$(SRCS_DIR)/ft_strnstr.c \
	$(SRCS_DIR)/ft_strrchr.c \
	$(SRCS_DIR)/ft_strtrim.c \
	$(SRCS_DIR)/ft_substr.c \
	$(SRCS_DIR)/ft_tolower.c \
	$(SRCS_DIR)/ft_toupper.c \
	$(SRCS_DIR)/ft_itoa.c \
	$(SRCS_DIR)/ft_lstnew_bonus.c \
	$(SRCS_DIR)/ft_lstadd_front_bonus.c \
	$(SRCS_DIR)/ft_lstsize_bonus.c \
	$(SRCS_DIR)/ft_lstlast_bonus.c \
	$(SRCS_DIR)/ft_lstadd_back_bonus.c \
	$(SRCS_DIR)/ft_lstdelone_bonus.c \
	$(SRCS_DIR)/ft_lstclear_bonus.c \
	$(SRCS_DIR)/ft_lstiter_bonus.c \
	$(SRCS_DIR)/ft_lstmap_bonus.c \
	$(SRCS_DIR)/get_next_line.c \
	$(SRCS_DIR)/get_next_line_utils.c \

OBJECTS = $(SOURCES:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
