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
	if(nbr_arg !=3 ){
		error("Problème nbr argument");
	}
	
    int tmp = strtol(path[1], 0, 8);
	chmod(path[2],tmp);
	return 0;
}


int main(int argc, char ** argv)
{
    ehoummad(argc,argv);
    exit(EXIT_SUCCESS);
}