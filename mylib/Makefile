##
## EPITECH PROJECT, 2020
## libmy
## File description:
## first makefile
##

NBR_SRC		=	$(wildcard ./my_nbr/*.c)
STR_SRC		=	$(wildcard ./my_str/*.c)
PRINT_SRC	=	$(wildcard ./my_printf/*.c)
INC_DIR		=	../include/
INC_PRINT	=	./my_printf/include/
CFLAGS		=	-I$(INC_DIR) -I$(INC_PRINT) -W -Wall
OBJ			=	$(NBR_SRC:.c=.o) $(STR_SRC:.c=.o) $(PRINT_SRC:.c=.o)
NAME		=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all
