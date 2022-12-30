#include<stdio.h>
#include<unistd.h>
#include<stdlib.h> 
#include<fcntl.h> 

/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(){
	write(1, "\33[H\33[2J", 8);
	return 0;
}


int main(int argc,char *argv[])
{
	ehoummad();
	exit(EXIT_SUCCESS);

}