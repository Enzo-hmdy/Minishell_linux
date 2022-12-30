#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <string.h>


#define BUF_MAX_SIZE 100


char buff[BUF_MAX_SIZE];    ////buffer pour la modification des chaines de caratères pour l'affichage 
char path[BUF_MAX_SIZE];     //Un buffer contenant  le directory du fichier pour l'appel à lstat
char name[BUF_MAX_SIZE];     //Un buffer contenant le nom du fichier pour l'affichage
char my_arg[BUF_MAX_SIZE]; //buffer contenant par défaut argv[1] ou '.' si nous n'avons aucun paramètre en entrée.


/**
 * @brief Print toute les permissions d'accès à un fichier où à un dossier
 * 
 * @param file  Fichier/directory passé en paramètre 
 */
void show_perm(struct stat file)
{
    if (S_ISFIFO(file.st_mode))
        printf("p");
    else if (S_ISLNK(file.st_mode)) // on vérifie si c'est un lien symbolique et si c'est le cas on précise que c'est un lien en affichant l 
        printf("l");
    else
        printf((S_ISDIR(file.st_mode)) ? "d" : "-"); // d si c'est un directory

    // affichage des droits
    printf((file.st_mode & S_IRUSR) ? "r" : "-"); // Le propriétaire à le droit de lecture
    printf((file.st_mode & S_IWUSR) ? "w" : "-"); // Le propriétaire à le droit de d'écriture
    printf((file.st_mode & S_IXUSR) ? "x" : "-"); // Le propriétaire à le droit d'excécution
    printf((file.st_mode & S_IRGRP) ? "r" : "-"); // Le groupe à le droit de lecture
    printf((file.st_mode & S_IWGRP) ? "w" : "-"); // Le groupe à le droit de d'écriture
    printf((file.st_mode & S_IXGRP) ? "x" : "-"); // Le groupe à le droit d'exécution
    printf((file.st_mode & S_IROTH) ? "r" : "-"); // Les autres ont le droit de lecture
    printf((file.st_mode & S_IWOTH) ? "w" : "-"); // Les autres ont le droit de d'écriture
    printf((file.st_mode & S_IXOTH) ? "x" : "-"); // Les autres ont le droit  d'exécution
}

/**
 * @brief  Affiche le nombre de lien d'un fichier
 * 
 * @param file 
 */
void show_nbr_link(struct stat my_file)
{
    printf(" %lu", my_file.st_nlink);                 

}
/**
 * @brief Montre le nom du propriétaire
 * 
 * @param my_file 
 */
void show_pwuid(struct stat my_fyle)
{
    printf(" %s", getpwuid(my_fyle.st_uid)->pw_name); 
}

/**
 * @brief  Affiche le nom de groupe associé au fichier
 * 
 * @param my_fyle 
 */
void show_gruid(struct stat my_fyle) 
{
    printf(" %s", getgrgid(my_fyle.st_gid)->gr_name); 
}
/**
 * @brief  Print la taille du fichier ou du dossier en Octet
 * 
 * @param my_fyle 
 */
void show_size(struct stat my_fyle)
{
    printf(" %ld", my_fyle.st_size);                
}

void afficher_temps (struct stat *file)
{
    
    char time[BUF_MAX_SIZE]; // Buffer pour stocker le temps 
    struct tm *file_time = localtime(&file->st_mtime);
    
    strftime(time, BUF_MAX_SIZE, "%a %e %h %Y %H:%M:%S", file_time); 
    printf(" %s", time);                                 

}


int main(int argc, char **argv)
{ 

    if (argc > 2) //Si on passe plus d'un nom de fichier ou de directory il faut créer une erreur
    {
        printf("Number of argument must be  < 2 \n"); 
        exit(EXIT_FAILURE);
    }

    
    struct stat my_fyle; // stat permet de récupérer beaucoup d'information sur le fichier nous allons utilise my_fyle pour récupérer toutes les informations du fichier passé en paramètre
    DIR *dir;
    struct dirent *read_dir;

    if (argc == 1) 
        strcpy(my_arg, "."); //Pas d'argument -> . comme valeur par defaut
    else
    {
        strcpy(my_arg, argv[1]); //Si un argument alors on utilise ce nom la
    }

    if (lstat(my_arg, &my_fyle) == -1) // Gestion de si le fichier existe pas
    {
        perror("stat");
        exit(EXIT_SUCCESS);
    }

    if (S_ISDIR(my_fyle.st_mode)) //Si on pointe sur un répertoive on va l'ouvrir
    {
        dir = opendir(my_arg);    // ouverture répertoire
        read_dir = readdir(dir);  // lecture repertoire 
    }

    // Pour un directory on veut afficher tout ce qu'il contient il faut donc boucler tant que ce n'est pas finnis (ce n'est pas le cas pour un fichier)
    do
    {
        if (S_ISDIR(my_fyle.st_mode) || argc == 1)
        {
            strcpy(path, my_arg); //Pour avoir le path, on mets le nom du repertoire puis un / :
            strcat(path, "/");
            strcat(path, read_dir->d_name); //On ajoute le nom du fichier au path: repertoire/fichier
            strcpy(name, read_dir->d_name);
            lstat(path, &my_fyle);
            if (strcmp("..", name) == 0 || strcmp(".", name) == 0)
                continue; 
        }
        else //dans le cas où ce n'est pas un répertoire on fait : path = nom de fichier
        {
            strcpy(path, my_arg);
            strcpy(name, my_arg);
        }

        show_perm(my_fyle);
        show_nbr_link(my_fyle) ;
        show_pwuid(my_fyle);
        show_gruid(my_fyle);
        show_size(my_fyle);
        afficher_temps(&my_fyle);

        if (S_ISLNK(my_fyle.st_mode)) // On regarde si c'est un lein symbolique 
        {
            readlink(path, buff, BUF_MAX_SIZE); //Alors on copie le nom du fichier pointe dans buff
            printf(" %s -> %s\n", name, buff);  //On affiche le nom du lien + nom du fichier pointC)
        }
        else
            printf(" %s\n", name);              //Si ce n'est pas un lien on affiche seulement le nom du fichier
    } while (dir && (read_dir = readdir(dir))); // Si ce n'est pas un directory c'est que c'est un fichier ainsi on n'a qu'une seul ligne en théorie à afficher donc pas besoin de reboucler !
                                                
    closedir(dir);
    exit(EXIT_SUCCESS);
}
