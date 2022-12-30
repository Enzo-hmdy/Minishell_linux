#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>          
#include <sys/stat.h>

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
	if (nbr_arg == 1){
		error("Pas d'agument");
	}
	int i = 1;
	for (i = 1 ; i < nbr_arg ; i++){
		
		if ( mkdir(path[i], 0666) < 0 ){
			error("mkdir()");
		}
	}
	return 0;
}


int main(int argc, char ** argv)
{
    ehoummad(argc,argv);
    exit(EXIT_SUCCESS);
}