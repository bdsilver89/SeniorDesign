# Name of your program:
NAME=app

# List of all .cpp source code files included in your program (separated by spaces):
SRC =	application/app.cpp		\
		OS/OS.cpp				\
		Control/Controller.cpp	\
		Drivers/Motors.cpp		\
		Drivers/Weight.cpp		\
		UI/UI.cpp				\
		Recipe/parser.cpp		\
		Recipe/ingredient.cpp	\
		Recipe/recipe.cpp		\
		Config/config.cpp		\

SRCPATH=./code/src/
OBJ=$(addprefix $(SRCPATH), $(SRC:.cc=.o))

RM=rm -f
INC = ./code/Include/
CPPFLAGS+= -I $(INC) -std=c++11 -lrt -lwiringPi -Wno-psabi


all: $(OBJ)
	g++ $(CPPFLAGS) $(OBJ) -o $(NAME)z

clean:
	@-$(RM) *~
	@-$(RM) *#*
	@-$(RM) *swp
	@-$(RM) *.core
	@-$(RM) *.stackdump
	@-$(RM) $(SRCPATH)*.o
	@-$(RM) $(SRCPATH)*.obj
	@-$(RM) $(SRCPATH)*~
	@-$(RM) $(SRCPATH)*#*
	@-$(RM) $(SRCPATH)*swp
	@-$(RM) $(SRCPATH)*.core
	@-$(RM) $(SRCPATH)*.stackdump


fclean: clean
	@-$(RM) $(NAME)

re: fclean all


