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
int ehoummad(int argc, char ** argv){
	if (argc == 1){
		error("pas d'argument pour rmdir");
	}
	int i = 1;
	for (i = 1 ; i < argc ; i++){
		// Try deleting the directory
		if ( rmdir(argv[i]) < 0 ){
			error("prolbème lors de rmdir");
		
		}
	}
	return 0;
}

int main(int argc, char ** argv)
{
	ehoummad(argc,argv);
	exit(EXIT_SUCCESS);
}