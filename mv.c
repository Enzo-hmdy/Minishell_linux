#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF 1024

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}



/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(int nbr_arg, char **argv){
	

	char buf[BUFF];
	int src_file,dest_file;
	int char_read;
	if(nbr_arg != 3){
		
        error("nbr arg incorects");
		
	}
	src_file=open(argv[1],O_RDONLY);
	dest_file=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	while((char_read=read(src_file,buf,BUFF)) != 0){
		write(dest_file,buf,char_read);
	}

    unlink(argv[1]);
	close(dest_file);

    exit(EXIT_SUCCESS);
	
}

int main(int argc,char  **argv)
 {
    ehoummad(argc,argv);
    exit(EXIT_SUCCESS);
 }
