SRC = ft_printf.c
#BSRC = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

AR = ar -rcs

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) $@ $^

#bonus :$(BOBJ) $(NAME)
#	@$(AR) $(NAME) $(BOBJ)

%.o:%.c
	@cc -c $(CFLAGS)  $< 

clean :
	@rm -f *.o
fclean :  
	@rm -f *.o  $(NAME)
re :fclean all

.PHONY : all clean fclean re bonus
