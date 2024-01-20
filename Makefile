# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 10:13:17 by plouvel           #+#    #+#              #
#    Updated: 2024/01/20 14:28:24 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR	=	objs/

SRCS_DIR	=	srcs/

SRCS		=	memory/ft_memset.c 			\
				memory/ft_bzero.c 			\
				memory/ft_memcpy.c 			\
				memory/ft_memmove.c 		\
				memory/ft_memchr.c 			\
				memory/ft_memcmp.c			\
				memory/ft_calloc.c			\
				memory/ft_realloc.c			\
				string/ft_strlen.c			\
				string/ft_strlcpy.c			\
				string/ft_strlcat.c			\
				string/ft_strcat.c			\
				string/ft_strncat.c			\
				string/ft_strncmp.c			\
				string/ft_strcmp.c			\
				string/ft_strcmp_ignore_case.c	\
				string/ft_strchr.c			\
				string/ft_strrchr.c			\
				string/ft_strnstr.c			\
				string/ft_strdup.c			\
				string/ft_strndup.c			\
				string/ft_strdelchrs.c		\
				string/ft_strdelchr.c		\
				string/ft_straddc.c			\
				string/ft_straddbc.c		\
				string/ft_straddec.c		\
				string/ft_straddbs.c		\
				string/ft_straddes.c	 	\
				string/ft_strnew_nchar.c	\
				string/ft_strnew_chars.c	\
				string/ft_strmapi.c			\
				string/ft_striteri.c		\
				string/ft_split.c			\
				string/ft_substr.c			\
				string/ft_strjoin.c			\
				string/ft_strjoinc.c		\
				string/ft_strtrim.c			\
				string/ft_atoi.c			\
				string/ft_atof.c			\
				string/ft_atoi_base.c		\
				string/ft_itoa.c			\
				string/ft_itoa_base.c		\
				string/ft_itoa_ubase.c		\
				string/ft_strmatch_int.c    \
				string/ft_strmatch_hex.c    \
				io/ft_putchar_fd.c			\
				io/ft_putchar.c			\
				io/ft_putstr_fd.c		\
				io/ft_putstr.c			\
				io/ft_putendl_fd.c		\
				io/ft_putnbr_fd.c		\
				io/ft_putnbr_base_fd.c	\
				io/ft_putbin_fd.c		\
				types/ft_isalpha.c		\
				types/ft_isdigit.c		\
				types/ft_isalnum.c		\
				types/ft_isascii.c		\
				types/ft_isprint.c		\
				types/ft_toupper.c		\
				types/ft_tolower.c		\
				types/ft_islower.c		\
				types/ft_isupper.c		\
				types/ft_stronly_digits.c \
				linked_list/ft_lstnew.c			\
				linked_list/ft_dlstnew.c		\
				linked_list/ft_lstadd_front.c	\
				linked_list/ft_lstsize.c		\
				linked_list/ft_dlstsize.c		\
				linked_list/ft_lstlast.c		\
				linked_list/ft_dlstlast.c		\
				linked_list/ft_lstadd_back.c	\
				linked_list/ft_dlstadd_back.c	\
				linked_list/ft_lstdelone.c					\
				linked_list/ft_dlstdelone.c					\
				linked_list/ft_lstclear.c					\
				linked_list/ft_dlstclear.c					\
				linked_list/ft_lstiter.c					\
				linked_list/ft_dlstiter.c					\
				linked_list/ft_lstmap.c						\
				parsing/ft_args_parser.c					\
				parsing/ft_args_parser_generate_docs.c		\

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS		=	-Wall -Werror -Wextra -I includes -g3

CC			=	cc

NAME		=	libft.a

RM			=	rm -rf

$(NAME): 		$(OBJS)
				ar r ${NAME} ${OBJS}
				ranlib ${NAME}

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@mkdir -p $(dir $@)
				${CC} ${CFLAGS} -c $< -o $@

all:			$(NAME)

clean:
				${RM} ${OBJS_DIR}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:	all clean fclean re
