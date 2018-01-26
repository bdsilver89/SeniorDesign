# Name of your program:
NAME=servo

# List of all .cpp source code files included in your program (separated by spaces):
SRC= main.cpp   \
	 servo_driver.cpp

SRCPATH=./
OBJ=$(addprefix $(SRCPATH), $(SRC:.cc=.o))

RM=rm -f
INC = ./
CPPFLAGS+= -I $(INC) -std=c++11


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

