# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 16:13:16 by vdelsie           #+#    #+#              #
#    Updated: 2020/02/10 17:55:53 by vdelsie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_BASEDIR = ./minilibx/

# определить ОС для определения версии mlx для использования ...
TARGETOS := $(shell uname -s)

ifeq ($(TARGETOS), Darwin)
	OSXRELEASE := $(shell uname -r | sed 's/\..*//')
	ifeq ($(OSXRELEASE), 17)
		OSXVER = highsierra
		MLX = $(addprefix $(MLX_BASEDIR), $(join minilibx_macos_, $(OSXVER)))
	endif
	ifeq ($(OSXRELEASE), 16)
		OSXVER = sierra
		MLX = $(addprefix $(MLX_BASEDIR), $(join minilibx_macos_, $(OSXVER)))
	endif
	ifeq ($(OSXRELEASE), 15)
		OSXVER = elcapitan
		MLX = $(addprefix $(MLX_BASEDIR), $(join minilibx_macos_, $(OSXVER)))
	endif
	ifeq ($(OSXRELEASE), 14)
		OSXVER = yosemite
	endif
	ifeq ($(OSXRELEASE), 13)
		OSXVER = maverick
	endif
	ifeq ($(OSXRELEASE), 12)
		OSXVER = mountainlion
	endif
	ifeq ($(OSXRELEASE), 11)
		OSXVER = lion
	endif
endif

NAME = vdelsie.filler
NAME_VIZ = filler.vizual

CC = gcc -Wall -Wextra -Werror -O2 -funroll-loops
#CC = gcc -Wall -Wextra -Werror -g -fsanitize=address

C_DIR = srcs
C_VIZ_DIR = viz
ifeq ($(DEBUG), 1)
  C_DEBUG_FILE = $(C_DIR)/debug_files_others_on.c $(C_DIR)/debug_files_stratmap_on.c
else
  C_DEBUG_FILE = $(C_DIR)/debug_files_off.c
endif
C_OTHER_FILES = $(addprefix $(C_DIR)/, \
				tools_basics.c \
				tools_player.c \
				tools_strat.c \
				tools_read.c \
				first_init.c \
				get_data.c \
				put_piece.c \
				border_check.c \
				border_calc.c \
				border_clear.c \
				heat_calc_main.c \
				heat_calc_sub_fct.c \
				strat_calc.c \
				strat_adjustment.c \
				delete_and_clear.c \
				main.c)

C_VIZ_FILES = $(addprefix $(C_VIS_DIR)/, \
				color.c \
				image.c \
				key_hooks.c \
				game_state_list_utils.c \
				read_utils.c \
				render.c \
				render_str.c \
				general_utils.c \
				main.c)


C_FILES = $(C_DEBUG_FILE) $(C_OTHER_FILES)


O_DIR = objs
O_DIR_VIZ = objs_viz
O_FILES = $(C_FILES:$(C_DIR)/%.c=$(O_DIR)/%.o)
O_FILES_VIZ = $(C_VIZ_FILES:$(C_VIS_DIR)/%.c=$(O_DIR_VIZ)/%.o)


#mlx library
MLX_LIB	= $(addprefix $(MLX), mlx.a)
MLX_INC = -I $(MLX)
MLX_LINK = -L $(MLX) -l mlx -framework OpenGL -framework AppKit

#libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
H_DIR = includes

LIB = -L$(LIBFT_DIR) -lft
INCL = -I$(H_DIR) -I$(LIBFT_DIR)/includes

all : debug $(NAME) $(NAME_VIZ) $(MLX_LIB) $(LIBFT)

$(MLX_LIB) :
	@make -C $(MLX)

$(LIBFT) :
	@make -C $(LIBFT_DIR)

$(NAME_VIZ) : $(LIBFT) $(O_FILES_VIZ)
	@$(CC) $(O_FILES_VIZ) -o $@ $(LIB) $(MLX_LINK)

$(NAME) : $(LIBFT) $(O_FILES)
	@$(CC) $(O_FILES) -o $@ $(LIB)

$(O_DIR_VIZ)/%.o : $(C_VIZ_DIR)/%.c $(H_DIR)
	@mkdir -p $(O_DIR_VIZ)
	@$(CC) -o $@ -c $< $(INCL) $(MLX_INC)

$(O_DIR)/%.o : $(C_DIR)/%.c $(H_DIR)
	@mkdir -p $(O_DIR)
	@$(CC) -o $@ -c $< $(INCL)

clean :
	@make clean -C $(MLX)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(O_DIR_VIZ)
	@rm -rf $(O_DIR)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME_VIZ)
	@rm -rf $(NAME)

re : fclean all

debug:
ifeq ($(DEBUG), 1)
	@rm -rf $(O_DIR)/debug_files_off.o
else
	@rm -rf $(O_DIR)/debug_files_on.o
endif

.PHONY : clean all fclean re
