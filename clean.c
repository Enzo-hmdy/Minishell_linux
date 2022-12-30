#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
*NOM: Hoummady
*PRENOM: ENZO
*/
int ehoummad(char *file) {
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if( fd == -1)
    {
        perror("open()");
    }
    
    return 0;
}

int main(int argc,char **argv)
{
    ehoummad(argv[1]);
    exit(EXIT_SUCCESS);
}