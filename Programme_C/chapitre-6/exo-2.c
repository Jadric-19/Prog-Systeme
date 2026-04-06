/*
Ecrire un programme qui prend en argument des noms de répertoire et affiche
la liste des fichiers de ces répertoires qui ont une taille supérieure à (à peu près) 1M o avec
l’UID du propriétaire du fichier.
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define TAILLE 1048576
#define TL 100

void traitement(char rep[])
{
     DIR *dir = opendir(rep) ;
     if(!dir)
      {
          printf("\n ERREUR D'OUVERTURE DU REP \n") ;
          return ;
      }

     struct dirent *ent ;
     struct stat sb;
     char path[TL] ;
     
     printf("\n Les fichiers sup 1Mo sont : \n") ;

     while((ent = readdir(dir)) != NULL)
      {
           if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
              continue;
           
           snprintf(path , TL , "%s/%s" , rep , ent->d_name);
           
           if (stat(path, &sb) == -1) 
           {
               perror(path);
               continue;
           }
           if (S_ISREG(sb.st_mode) && sb.st_size > TAILLE) 
           {
                printf("Fichier: %s | Taille: %lld octets | UID: %d\n", path, (long long)sb.st_size , sb.st_uid);
           }
      
      }
     
     closedir(dir);
     printf("\n");
}

int main(int argc , char *argv[])
{
     if(argc < 2)
      {
         printf("\n Veullez entrer au moins un argument rep en argument : ./fichier rep1 ...\n") ;
         exit(0) ;
      }
     
     int i = 0 ;

     for(i = 0 ; i < argc ; i++)
      {
          traitement(argv[i]) ;
      }
     
   

     return 0 ;
}