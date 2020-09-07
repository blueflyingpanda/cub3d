# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/04 18:35:14 by lhelper           #+#    #+#              #
#    Updated: 2020/09/03 14:18:35 by lhelper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = mandatory/main.c\
		mandatory/colors.c\
		mandatory/hook.c\
		mandatory/map.c\
		mandatory/get_next_line.c\
		mandatory/get_next_line_utils.c\
		mandatory/ft_atoi.c\
		mandatory/ft_split.c\
		mandatory/mini.c\
		mandatory/ray.c\
		mandatory/saveandline.c\
		mandatory/utils.c\
		mandatory/more_utils.c\
		mandatory/main_utils.c\
		mandatory/draw_utils.c\
		mandatory/get1.c\
		mandatory/get2.c\
		mandatory/init.c\

SRCB = bonus/main.c\
		bonus/colors.c\
		bonus/hook.c\
		bonus/map.c\
		bonus/get_next_line.c\
		bonus/get_next_line_utils.c\
		bonus/ft_atoi.c\
		bonus/ft_split.c\
		bonus/mini.c\
		bonus/ray.c\
		bonus/saveandline.c\
		bonus/utils.c\
		bonus/more_utils.c\
		bonus/main_utils.c\
		bonus/draw_utils.c\
		bonus/get1.c\
		bonus/get2.c\
		bonus/init.c\
		bonus/hud.c\
		bonus/bonus.c\
		bonus/bonus_utils.c\
		bonus/more_bonus_utils.c\

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
COMPILER = gcc -Wall -Wextra -Werror
LIBRARY = -L. -lmlx
HEADER = mandatory/cub3d.h
HEADERB = bonus/cub3d.h
MMS = libmlx.dylib

all: $(MMS) $(NAME)

%.o: %.c $(HEADER)
	$(COMPILER) -c $< -o $@

$(MMS):
	cd mms && make
	mv mms/libmlx.dylib ./libmlx.dylib

$(NAME): $(OBJ)
	@$(COMPILER) $(LIBRARY) $(OBJ) -o $(NAME)

bonus: $(MMS) $(OBJB)
	@$(COMPILER) $(LIBRARY) $(OBJB) -o $(NAME)

%.o: %.c $(HEADERB)
	$(COMPILER) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(MMS)

re: fclean all
