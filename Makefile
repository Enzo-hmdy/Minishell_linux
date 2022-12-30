#
##

CC	=	gcc 
CFLAGS	=  	-Wall
CFLAGS  +=      -D_GNU_SOURCE
CFLAGS  += 	-g

CIBLES	=	example minishell

all: $(CIBLES)

clean: 
	$(RM) -f core *.o $(CIBLES) *~

run: clean all
		./minishell
