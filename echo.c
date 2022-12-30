#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(int argc, char ** argv) {

	if(argc>1){
		int i;
		for(i=1;i<argc;i++){
			write(1,argv[i],strlen(argv[i]));
            write(STDOUT_FILENO," ",strlen(" "));
		}
		printf("\n");
		return 0;
	}
	else{
		return EXIT_FAILURE;
	}
	
}

int main(int argc, char ** argv)
{
	ehoummad(argc,argv);
	exit(EXIT_SUCCESS);
}
