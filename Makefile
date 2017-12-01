# Name of your program:
NAME=app

# List of all .cpp source code files included in your program (separated by spaces):
SRC= application/app.cc recipe/parser.cc recipe/ingredient.cc recipe/recipe.cc

SRCPATH=./src/
OBJ=$(addprefix $(SRCPATH), $(SRC:.cc=.o))

RM=rm -f
TYPESPATH = ./src/types
RECIPEPATH =./src/recipe
CONFIGPATH = ./src/config
HWPATH  = ./src/hardware
CPPFLAGS+= -I $(TYPESPATH) -I $(RECIPEPATH) -I $(CONFIGPATH) -I $(HWPATH) -std=c++11


all: $(OBJ)
	g++ $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	-$(RM) *~
	-$(RM) *#*
	-$(RM) *swp
	-$(RM) *.core
	-$(RM) *.stackdump
	-$(RM) $(SRCPATH)*.o
	-$(RM) $(SRCPATH)*.obj
	-$(RM) $(SRCPATH)*~
	-$(RM) $(SRCPATH)*#*
	-$(RM) $(SRCPATH)*swp
	-$(RM) $(SRCPATH)*.core
	-$(RM) $(SRCPATH)*.stackdump

fclean: clean
	-$(RM) $(NAME)

re: fclean all

