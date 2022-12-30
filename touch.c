#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int argc, char ** argv
int ehoummad(int argc, char ** argv) {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    close(fd);

    return 0;
}

int main(int argc, char ** argv)
{
    ehoummad(argc,argv);
    return 0;
}