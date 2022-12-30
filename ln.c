#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>          
#include <sys/stat.h>
#include <unistd.h>
void error(char *msg)
{
    perror(msg);
    exit(EXIT_SUCCESS);
}


/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(int nbr_arg, char **path){
	

	if (nbr_arg < 3){
		
        error("Pas assez d'argument pour ln");
		
	}

	if ( nbr_arg > 3){
		error("too many argument");
	}

	

	if(symlink(path[1], path[2]) < 0 ){
		error("symlink()");
	}


	exit(EXIT_SUCCESS);


}


int main(int argc, char ** argv)
{
    ehoummad(argc,argv);
    exit(EXIT_SUCCESS);
}