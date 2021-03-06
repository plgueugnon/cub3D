# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 14:58:12 by pgueugno          #+#    #+#              #
#    Updated: 2021/03/06 10:11:24 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               Filename output                                #
################################################################################

NAME		=	cub3D.out

################################################################################
#                         Sources and objects directories                      #
################################################################################

HEADERS_DIR	=	header
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBS_DIR	=	libs
LIBFT_DIR	=	libft
LIBFT_MAKE	=	Makefile
LIB_LIBFT_DIR	= $(LIBS_DIR)/libft.a
MLX_DIR		=	mlx
MLX_MAKE	=	Makefile
MLX_LIB		=	libmlx.dylib
OS			=	$(shell uname)

################################################################################
#                               Sources filenames                              #
################################################################################

SRCS		=	custom_gnl.c parse_ceiling_and_floor.c raycast_draw.c\
				exit.c parse_map.c raycast_start.c floodfill.c\
				parse_resolution.c save.c init.c parse_textures.c\
				sprite_draw.c keys.c parsing_error.c sprite_management.c\
				main.c parsing_hub.c texture_init.c map_to_tab.c\
				queue_management.c move.c raycast_compute.c

################################################################################
#                              Commands and arguments                          #
################################################################################

CC			=	@gcc
CFLAGS		=	-Wall -Wextra -Werror -I$(HEADERS_DIR) -g3 
#CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address -I$(HEADERS_DIR) 
#LDFLAGS = -L . $(LIB_LIBFT_DIR) -L$(MLX_DIR) -l$(MLX_DIR) -fsanitize=address 
LDFLAGS = -L . $(LIB_LIBFT_DIR) -L$(MLX_DIR) -l$(MLX_DIR)
FRAMEWORKS	=	-framework OpenGL -framework Appkit
RM			=	@rm -f
BUFSIZE		= -D BUFFER_SIZE=32

################################################################################
#                                 Defining colors                              #
################################################################################

_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_CYAN		=	\x1b[96m

################################################################################
#                                  Compiling                                   #
################################################################################

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:	init_libft os_check init_mlx init $(NAME)

os_check:
		if [ "$(OS)" = "Linux" ];\
		then	$(MLX_DIR) = mlx_l\
				$(MLX_LIB) = libmlx.a\
				$(LDFLAGS) = -L $(MLX_DIR) -lmlx -lm -lbsd\
				$(FRAMEWORKS) = -lX11 -lXest\
			 echo "$(OS)";\
		fi
init:
		@ if test -f $(NAME);\
		then echo "$(_CYAN)[Cub3D program already created]";\
		else echo "$(_YELLOW)[Initialize cub3D program]";\
		fi

init_mlx:
			@ if test -f $(MLX_LIB);\
			then echo "$(_CYAN)[mlx lib already created]";\
			else cp $(MLX_DIR)/mlx.h ./header/ &&\
			make -C $(MLX_DIR) -f $(MLX_MAKE) &&\
			cp $(MLX_DIR)/$(MLX_LIB) . &&\
			echo "$(_YELLOW)[mlx lib created]";\
			fi

init_libft:
			@ make -j -C $(LIBFT_DIR) -f $(LIBFT_MAKE)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				@ echo "\t$(_YELLOW) compiling... $*.c"
				$(CC) $(CFLAGS) $(BUFSIZE) -c $< -o $@
	#			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@ echo "\t$(_YELLOW)[Creating cub3D.out file]"
			$(CC) $(OBJS) -o $@ $(LDFLAGS) $(FRAMEWORKS) 
			@ echo "$(_GREEN)[Cub3D program created & ready to play]"

clean:
		@ echo "$(_RED)[cleaning up cub3D & mlx objects files]"
		$(RM) $(OBJS)
		@ echo "$(_RED)[deleting save file]"
		$(RM) ./save.bmp
		@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) clean
		@ make -C $(MLX_DIR) -f $(MLX_MAKE) clean

fclean: clean
		@ echo "$(_RED)[cleaning up cub3D & mlx objects and library files]"
		$(RM) $(NAME) $(MLX_LIB) 
		@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) fclean

re:	fclean all

.SILENT:
		all
.PHONY: all clean fclean re bonus
