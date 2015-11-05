NAME		=	babbel

CXX		=	clang++

RM		=	rm -rf

SRC		=	src/BabbelOpus.cpp \
			src/BabbelAudio.cpp \
			src/PlugAudio.cpp \
			src/APlugin.cpp \
			src/main_test.cpp


OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-g -W -Wall -Wextra
CPPFLAGS	+=	-I inc -pthread -std=c++11

LDFLAGS		=	-lrt -lasound -ljack -lpthread -L./lib/ -lportaudio -L./lib/ -lopus

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
