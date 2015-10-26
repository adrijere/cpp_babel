NAME		=	babel_server

CXX			=	g++

RM			=	rm -rf

SRC			=	main.cpp \
				src/Core.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -I inc/

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)

clean		:
				$(RM) $(OBJ)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all
