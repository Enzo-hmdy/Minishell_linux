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
	
   if(unlink(*path)==-1) error("unlink()") ;



}  


int main(int argc, char ** argv)
{
    ehoummad(argc,argv);
    exit(EXIT_SUCCESS);
}


