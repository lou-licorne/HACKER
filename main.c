#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

void exec_old(char* file){
	if(strcmp(file, "main.exe")!=0){
		char commande[1024];
		strcpy(commande, "./");
		strcat(commande,file);
		strcat(commande, ".old");
		system(commande);
	}
}

void create_old(char* file){
	char commande[1024];
	strcpy (commande, "cp ");
	strcat(commande, file);
	strcat(commande, " ");
	strcat(commande, file);
	strcat(commande, ".old");
	system(commande);
}

int main(int argc, char **argv)
{
	printf("main\n");

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
			create_old(dir->d_name); //cree un fichier .exe en .old
			exec_old(dir->d_name); //execute les fichiers .exe du répertoire
		}
	}
    return 0;
}
