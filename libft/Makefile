# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/26 18:53:37 by lmunoz-q          #+#    #+#              #
#    Updated: 2018/04/16 21:47:25 by lmunoz-q         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCFILES = ft_striter.c \
		   ft_strmap.c \
		   ft_strmapi.c \
		   ft_itoa.c \
		   ft_striteri.c \
		   ft_strtrim.c \
		   ft_memset.c \
		   ft_putchar.c \
		   ft_putchar_fd.c \
		   ft_putendl.c \
		   ft_bzero.c \
		   ft_putendl_fd.c \
		   ft_putnbr.c \
		   ft_putnbr_fd.c \
		   ft_putstr.c \
		   ft_putstr_fd.c \
		   ft_strsub.c \
		   ft_strsplit.c \
		   ft_strjoin.c \
		   ft_strdel.c \
		   ft_strdup.c \
		   ft_strcat.c \
		   ft_strlcat.c \
		   ft_strncat.c \
		   ft_strclr.c \
		   ft_strcmp.c \
		   ft_strcpy.c \
		   ft_strlen.c \
		   ft_strncpy.c \
		   ft_memalloc.c \
		   ft_memdel.c \
		   ft_memcpy.c \
		   ft_memccpy.c \
		   ft_memmove.c \
		   ft_atoi.c \
		   ft_memchr.c \
		   ft_memcmp.c \
		   ft_strchr.c \
		   ft_strncmp.c \
		   ft_isalpha.c \
		   ft_isdigit.c \
		   ft_isalnum.c \
		   ft_isascii.c \
		   ft_isprint.c \
		   ft_toupper.c \
		   ft_tolower.c \
		   ft_strrchr.c \
		   ft_strstr.c \
		   ft_strequ.c \
		   ft_strnequ.c \
		   ft_strnew.c \
		   ft_strnstr.c \
		   ft_lstnew.c \
		   ft_lstdelone.c \
		   ft_lstdel.c \
		   ft_lstadd.c \
		   ft_lstiter.c \
		   ft_lstmap.c \
		   ft_putstr_list.c \
		   ft_lstaddback.c \
		   ft_strpbrk.c \
		   ft_strspn.c \
		   ft_strcspn.c \
		   ft_strcchar.c \
		   get_next_line.c \

OBJ = $(SRCFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
