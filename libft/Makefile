# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 10:07:13 by pgueugno          #+#    #+#              #
#    Updated: 2021/02/21 11:52:46 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#							Filename output								      #
###############################################################################

NAME		=	../libs/libft.a

###############################################################################
#						Sources and objects directories					      #
###############################################################################

HEADERS_DIR	=	../header
SRCS_DIR	=	srcs
OBJS_DIR	=	../objs
LIBS_DIR	=	../libs

###############################################################################
#							Sources filenames							      #
###############################################################################

SRCS		=	$(notdir $(shell find $(SRCS_DIR) -type f -name *.c))

###############################################################################
#							Commands and arguments						      #
###############################################################################

CC		=	@gcc
CFLAGS		=	-Wall -Wextra -Werror -I$(HEADERS_DIR) -g
BUFSIZE		=	-D BUFFER_SIZE=32
RM		=	@rm -f
AR		=	@ar -rcs

###############################################################################
#								Defining colors							      #
###############################################################################

_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_CYAN		=	\x1b[96m

###############################################################################
#									Compiling							      #
###############################################################################

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:	init $(NAME)

init:
	@ if test -f ../libs/libft.a;\
	then echo "$(_CYAN)[libft.a already created]";\
	else echo "$(_YELLOW)[Initialize libft]";\
	fi
	@ $(shell mkdir -p $(OBJS_DIR))
	@ $(shell mkdir -p $(LIBS_DIR))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				$(CC) $(CFLAGS) $(BUFSIZE) -c $< -o $@

$(NAME): $(OBJS)
		@ echo "\t$(_YELLOW)[Creating library...]"
		$(AR) $(NAME) $(OBJS)
		@ echo "$(_GREEN)[libft.a created]"

clean:
		@ echo "\t$(_RED)[cleaning libft objects files]"
		$(RM) $(OBJS)

fclean: clean
		@ echo "\t$(_RED)[cleaning libft objects and library files]"
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
