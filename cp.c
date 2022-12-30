#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF 1024


/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(int argc, char * argv[]) {

	if(argc !=3)
	{
		perror("argc invalid");
		exit(EXIT_FAILURE);

	}
	char buf[BUFF];
	int src_file,dest_file;
	int char_read;
	if(argc != 3){
		return EXIT_FAILURE;
		
	}
	src_file=open(argv[1],O_RDONLY);
	dest_file=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH); // 0666

	while((char_read=read(src_file,buf,BUFF)) != 0){
		write(dest_file,buf,char_read);
	}
	close(dest_file);
	close(src_file);
	exit(EXIT_SUCCESS);
	
}

int main(int argc,char **argv)
{
	ehoummad(argc,argv);
	exit(EXIT_SUCCESS);
}


