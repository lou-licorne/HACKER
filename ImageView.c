#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int verification(char* fichier_a_test){
	int exist = 0;
	char nom_old[1024];
	strcpy(nom_old, fichier_a_test);
	strcat(nom_old, ".old");
	
	FILE* fichier=NULL;
	fichier = fopen(nom_old, "r+");
	if(fichier != NULL) exist = 1;

	if(exist){
		printf("fichier .old cree\n");
	}else{
		printf("fichier .old non cree\n");
	}

return exist;
}

void view_image(char* image){
	char commande[1024];
	strcpy(commande, "eog ");
	strcat(commande, image);
	system(commande);
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

int main(){
	int exist;

	view_image("test");

	//create_old("test");

	verification("test");
	
	//system("cp virus.c test");
	printf("You've been hacked.\n");
return 0;
}

