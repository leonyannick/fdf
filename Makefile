# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 09:17:44 by lbaumann          #+#    #+#              #
#    Updated: 2023/03/13 13:26:49 by lbaumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
#CFLAGS = -Wall -Werror -Wextra

UNAME := $(shell uname)

ifeq ($(DEBUG), 1)
CFLAGS = -g
endif

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = objs/
LIBFTDIR = libft/
MLXDIR = MLX42/

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
PU	= \033[35;1m
BL	= \033[34;1m
RC	= \033[0m

HEADERS = -I $(INCDIR) -I $(LIBMLX)/include

SRC = main.c \
	line.c \
	map.c \
	projection.c \
	window.c \
	point_ops.c \
	color.c \
	utils.c \
	init_data.c

#libft
LIBFT = $(LIBFTDIR)libft.a
LIBFTINCL = -L$(LIBFTDIR) -lft

#mlx42
MLX = $(MLXDIR)build/libmlx42.a

ifeq ($(UNAME), Linux)
MLXINCL = $(MLX) -Iinclude -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME), Darwin)
MLXINCL = $(MLX) -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
endif

SRCS := $(addprefix $(SRCDIR), $(SRC))
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJDIR), $(OBJ))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXINCL) $(LIBFTINCL) $(HEADERS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	if [ ! -d "libft" ]; then git clone https://github.com/leonyannick/libft.git; fi
	$(MAKE) -C $(LIBFTDIR)

$(MLX):
	if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	cmake $(MLXDIR) -B $(MLXDIR)build && cmake --build $(MLXDIR)build -j8

clean:
	rm -rf $(OBJDIR)
	rm -f $(LIBMLX)/build
	$(MAKE) clean -C $(LIBFTDIR)

cleanlibs:
	rm -rf $(LIBFTDIR)
	rm -rf $(MLXDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re
