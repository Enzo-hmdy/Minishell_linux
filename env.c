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
int ehoummad(int nbr_arg, char **path,char **environ){
	
    char **envp = environ;
	while(*envp){
		printf("%s \n", *envp++);
	}
	return EXIT_SUCCESS;
}


int main(int argc, char ** argv,char **envp)
{
    ehoummad(argc,argv,envp);
    exit(EXIT_SUCCESS);
}





