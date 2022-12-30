#include<stdio.h>
#include<unistd.h>
#include<stdlib.h> 
#include<fcntl.h> 

/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(int argc,char *argv[])
{ 
	int fd;
    int i = 0;
    int tmp;

	
	for (i = 1; i < argc; i++) {                   
		
		fd = open(argv[i],O_RDONLY);           
		
		if(fd < 0) { 
			perror("open"); 
			exit(EXIT_FAILURE); 
		} 
		
		while(read(fd,&tmp,1))                 
			
			write(STDOUT_FILENO,&tmp,1);    
		
		close(fd);                             
	}

	return 0;
}

int main(int argc,char *argv[])
{
	ehoummad(argc,argv);
	exit(EXIT_SUCCESS);

}