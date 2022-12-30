#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(char *file)
{
	FILE *my_fyle = fopen(file, "r+");
	int nbrLignes = 0;
	int nbrword = 0;
	int nbr_octet = 0;
	char buff[1];
	while (read(fileno(my_fyle),buff,1) ==1 )
	{
		nbr_octet++;

		if(buff[0] == ' ')
			{nbrword ++;}

		else if (buff[0] == '\n')
			{nbrLignes++;
			nbrword ++;}
	}
	printf("Number of lines of file %s is : %d\nNumber of word : %d \n Number of bytes : %d \n", file, nbrLignes+1,nbrword+1,nbr_octet);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	ehoummad(argv[1]);
	exit(EXIT_SUCCESS);
}
