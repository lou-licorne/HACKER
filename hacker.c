#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	DIR* dirPtr;
	char * dirName[1024];
	char * filePath[1024];
	getcwd(dirName,sizeof(dirName));
	//printf("%s\n", dirName);
	dirPtr = opendir(dirName);
	struct dirent *dir;

 	while((dir=readdir(dirPtr)) != NULL) {
    		struct stat fileStat;		
		strcpy(&filePath,&dirName); // Re-initialisation du path du fichier à celui du dossier
		strcat(&filePath, "/"); // Ajout du "/"
		strcat(&filePath, dir->d_name); // Ajout du nom du fichier traité pour avoir le path absolue de ce dernier

    		if(stat(filePath,&fileStat) < 0){ // Gestion de l'erreur de lecture du fichier
			perror("stat");
			exit(EXIT_SUCCESS);
		}

    		if((fileStat.st_mode & S_IXUSR) && (fileStat.st_mode & S_IFREG)){ // SI le propriétaire a le droit d'execution ET que le fichier est régulier
			printf("%s is a regular executable file\n", dir->d_name); // On peut donc stocker le nom du fichier pour plus tard
		}else{
			printf("%s is an other file type\n", dir->d_name); 
		}
	}
    return 0;
}
