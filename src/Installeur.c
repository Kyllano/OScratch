/*! \file 	installeur.c
	\brief  fichier du code de l'installeur
	\author JUAN Victor, CHEVALLIER Guilhem
	\date 	11 mai 2022
*/

#include "OS_DEFINES.h"

// create a file named di (i = diskid) in directory dirname of size bytes
// the file is initialized with 0
// dirname must be a valid directory
// 0 <= diskid < 10
void format(char *dirname, int size, char* diskname){
	char filename[strlen(dirname)+strlen(diskname)+2];
	snprintf(filename, strlen(dirname)+strlen(diskname)+2, "%s/%s", dirname, diskname);
	printf("Initialisation de %s...\n", filename);
	FILE *fp = fopen(filename, "w+");
	assert(fp!=NULL);
	unsigned char zero=0;
	for(int i=0; i<size; i++) {
		int nb_write = fwrite(&zero, 1, 1, fp);
		assert(nb_write == 1);
	}
	fclose(fp);
}


int main(int argc, char **argv) {
	if (argc!=3) {
		printf(YELLOW"usage : %s disk_name disk_size\n"DEF, argv[0]);
		return 0;
	}
	int size;
	if((size=atoi(argv[2]))==0){printf("la taille du disque doit être un entier non nul\n");return 1;}
	if(argc==3){
		format(".", size, argv[1]);
	}

	if (init_disk_sos(argv[1])){
		printf(RED"Erreur d'accès au disque.\n"DEF);
		return ERROR_FILE_ACCESS;
	}

	update_first_free_byte();
	init_users_table();

	if (!write_super_block()){
		write_inodes_table();
		return NO_ERROR;
	}

	printf(RED"Erreur d'accès au disque.\n"DEF);
	return ERROR_FILE_ACCESS;
}
