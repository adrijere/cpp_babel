NAME		=	babbel

CXX		=	g++

RM		=	rm -rf

SRC		=	


OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -Werror
CPPFLAGS	+=	-I inc

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

