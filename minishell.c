
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
      


#define BUFFER 512
#define DEBUG 1
#define MAXSIZE  64

void error(char *msg)
{
    perror(msg);
    exit(EXIT_SUCCESS);
}


int run_command(char *command, char **arg, char *fdest,int my_flag)
{
    pid_t status;
    int fd;
    status = fork();
    switch (status)
    {
    case -1:
        error("Creation processus");
    case 0:
        if (strlen(fdest) > 0 )
        {   
            switch (my_flag)
            {
            case 1 :
                fd = open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(fd, STDOUT_FILENO);
                break;
            
            case 2 : 
                fd = open(fdest, O_WRONLY | O_APPEND,0666);
                dup2(fd, STDOUT_FILENO);
                break;

            case 3:
                fd = open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                dup2(fd, STDERR_FILENO);
                break;
            case 4:
                fd = open(fdest, O_WRONLY | O_APPEND,0666);
                dup2(fd, STDERR_FILENO);
                break;
            


            default:
                break;
            }
            
        }
        if(!strcmp(command,"cd")) exit(EXIT_SUCCESS);
        if (execvp(command, arg) == -1)
            error("Erreur ");
        if (strlen(fdest) > 0)
            close(fd);
        exit(EXIT_SUCCESS);
        break;
    default:
        wait(&status);
       
            
        if (WIFEXITED(status))
        {
             if(!strcmp(command,"cd"))
            {
                if(chdir(arg[1])== -1 )
                    error("CD not working");
            }
            printf("commande exec sans erreur\n");
        }
        else
            printf("commande exec avec erreur\n");
       
    }
    return 0;
}

int read_command(char *command, char *arg[], char *fdest,int *my_flag)
{
    int cpta = 1;
    int c;
    char *chaine;
    char buffer[MAXSIZE];
    scanf("%s", command);
    if (!strcmp(command, "exit"))
        return -1;
    while ((c = getchar()) != '\n')
    {
        chaine = malloc((BUFFER - 1) * sizeof(char));
        bzero(chaine, ((BUFFER - 1) * sizeof(char)));
        scanf("%s", chaine);
        if (!strcmp(chaine, ">"))
        {   
            *my_flag = 1 ;
            scanf("%s", fdest);
            break;
        }
        else if(!strcmp(chaine, ">>"))
        {
            *my_flag = 2;
            scanf("%s", fdest);
            break;
        }
        else if(!strcmp(chaine, "2>"))
        {
            *my_flag = 3;
            scanf("%s", fdest);
            break;
            /* code */
        }
        else if(!strcmp(chaine, "2>>"))
        {
            *my_flag = 4;
            scanf("%s", fdest);
            break;
            /* code */
        }
       
        
        arg[cpta++] = chaine;
    }
    return cpta;
}

int main()
{
    char command[BUFFER];
    char fdest[BUFFER];
    char *arg[BUFFER];
    char path[BUFFER];
    struct group *grp;
    struct passwd *pwd;
    char user[BUFFER];
    int uid = getuid();
    int nb_args, i;
    grp = getgrgid(uid);
    pwd = getpwuid(uid);
    getcwd(path,BUFFER);
    getlogin_r(user,BUFFER);

    while (1)
    {
        fdest[0] = '\0';
        nb_args = 0;
        int my_flag = 0;

                
        bzero(arg, BUFFER);
        getcwd(path, BUFFER);
        printf("\033[1;32m %s@%s \033[0;34m %s\033[0m$", grp->gr_name,pwd->pw_name,path);
        nb_args = read_command(command, arg, fdest,&my_flag);
        arg[0] = command;
        // printf("%ls tmp main \n ",&tmp);
        if (nb_args == -1)
            error("nb_arg");

        if (DEBUG)
        {
            printf("commande a executer : %s, %d arguments [", command, nb_args);
            for (i = 0; i < nb_args; i++)
                printf("%s ,", arg[i]);
            printf(" ] , fdest : %s\n ", fdest);
        }
        run_command(command, arg, fdest,my_flag);
    }
    return 0;
}
