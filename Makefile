NAME		=	babbel

CXX		=	g++

RM		=	rm -rf

SRC		=	src/BabbelOpus.cpp \
			src/BabbelAudio.cpp \
			src/main_test.cpp


OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -Werror
CPPFLAGS	+=	-I inc

LDFLAGS		= -lrt -lasound -ljack -lpthread -L./lib/ -lportaudio -L./lib/ -lopus

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
