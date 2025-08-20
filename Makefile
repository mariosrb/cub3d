# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: username <username@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/XX/XX XX:XX:XX by username         #+#    #+#              #
#    Updated: 2024/XX/XX XX:XX:XX by username        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Directories
SRCDIR = src
OBJDIR = obj
LIBFTDIR = lib/libft

# Source files (architecture modulaire)
SRCS = $(SRCDIR)/core/main.c \
       $(SRCDIR)/core/game_init.c \
       $(SRCDIR)/parsing/parser_main.c \
       $(SRCDIR)/parsing/parser_config.c \
       $(SRCDIR)/parsing/parser_utils.c \
       $(SRCDIR)/rendering/renderer_main.c \
       $(SRCDIR)/rendering/raycasting.c \
       $(SRCDIR)/input/input_handler.c \
       $(SRCDIR)/input/movement.c \
       $(SRCDIR)/utils/error_handler.c \

# Bonus files
BONUS_SRCS = $(SRCS) \
             $(SRCDIR)/bonus/minimap.c \
             $(SRCDIR)/bonus/advanced_collision.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes -I$(LIBFTDIR)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a

# # MLX (adapte selon ton système)
# UNAME = $(shell uname)
# ifeq ($(UNAME), Darwin)
# 	# macOS
# 	MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
# else
# 	# Linux
# 	MLX_FLAGS = -lmlx -lXext -lX11 -lm
# endif

LDFLAGS = -L$(LIBFTDIR) -lft $(MLX_FLAGS) -lm

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(NAME) ready!"

bonus: $(LIBFT) $(BONUS_OBJS)
	@echo "🔗 Linking bonus..."
	@$(CC) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)
	@echo "✅ Bonus ready!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "⚙️  Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "📚 Building libft..."
	@make -C $(LIBFTDIR) --no-print-directory

clean:
	@echo "🧹 Cleaning..."
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean --no-print-directory

fclean: clean
	@echo "🗑️  Full clean..."
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory

re: fclean all

.PHONY: all bonus clean fclean re
