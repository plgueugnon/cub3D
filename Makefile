# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 14:58:12 by pgueugno          #+#    #+#              #
#    Updated: 2021/02/26 15:58:10 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#								Filename output							      #
###############################################################################

NAME		=	cub3D.out

###############################################################################
#						Sources and objects directories					      #
###############################################################################

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

###############################################################################
#								Sources filenames						      #
###############################################################################

SRCS		=	$(notdir $(shell find $(SRCS_DIR) -type f -name *.c))

###############################################################################
#							Commands and arguments						      #
###############################################################################

CC			=	@gcc
 CFLAGS		=	-Wall -Wextra -Werror -I$(HEADERS_DIR) -g3 
 #CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address -I$(HEADERS_DIR) 
 LDFLAGS		=	-L. $(LIB_LIBFT_DIR) 
 #LDFLAGS		=	-L. $(LIB_LIBFT_DIR) -Lmlx -lmlx -fsanitize=address 
 #FRAMEWORKS	=	-framework OpenGL -framework Appkit
RM			=	@rm -f
BUFSIZE		= -D BUFFER_SIZE=32

###############################################################################
#									Defining colors						      #
###############################################################################

_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_CYAN		=	\x1b[96m

###############################################################################
#									Compiling							      #
###############################################################################

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:	init_libft init_mlx init $(NAME)

init:
		@ if test -f $(NAME);\
		then echo "$(_CYAN)[Cub3D program already created]";\
		else echo "$(_YELLOW)[Initialize cub3D program]";\
		fi

init_mlx:
			@ if test -f $(MLX_LIB);\
			then echo "$(_CYAN)[mlx lib already created]";\
			else make -C $(MLX_DIR) -f $(MLX_MAKE) &&\
			cp $(MLX_DIR)/libmlx.dylib . &&\
			echo "$(_YELLOW)[mlx lib created]";\
			fi

init_libft:
			@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				@ echo "\t$(_YELLOW) compiling... $*.c"
				$(CC) $(CFLAGS) $(BUFSIZE) -c $< -o $@
	#			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@ echo "\t$(_YELLOW)[Creating cub3D.out file]"
	#		$(CC) $(OBJS) -o $@ $(LDFLAGS) $(FRAMEWORKS) 
			$(CC) $(OBJS) -o $@ $(LDFLAGS) 
			@ echo "$(_GREEN)[Cub3D program created & ready to play]"

clean:
		@ echo "$(_RED)[cleaning cub3D objects files]"
		$(RM) $(OBJS)
		@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) clean
		@ make -C $(MLX_DIR) -f $(MLX_MAKE) clean

fclean: clean
		@ echo "$(_RED)[cleaning cub3D objects and library files]"
#		$(RM) $(NAME) $(MLX_LIB) 
		$(RM) $(NAME) 
		@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) fclean

re:	fclean all

.PHONY: all clean fclean re bonus
