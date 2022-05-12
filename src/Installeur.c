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
char *format(char *dirname, int size, char* diskname){
	char* filename=(char *)malloc((strlen(dirname)+strlen(diskname)+7)*sizeof(char));
	snprintf(filename, strlen(dirname)+strlen(diskname)+7, "%s/disk/%s", dirname, diskname);
	printf("Initialisation de %s...\n", filename);
	FILE *fp = fopen(filename, "w+");
	assert(fp!=NULL);
	unsigned char zero=0;
	for(int i=0; i<size; i++) {
		int nb_write = fwrite(&zero, 1, 1, fp);
		assert(nb_write == 1);
	}
	fclose(fp);
	return filename;
}


int main(int argc, char **argv) {
	if (argc!=3) {
		printf(YELLOW"usage : %s "UNDR"disk_name"DEF YELLOW" "UNDR"disk_size\n"DEF, argv[0]);
		return 0;
	}
	int size;char *diskpath;
	if((size=atoi(argv[2]))==0){printf("la taille du disque doit être un entier non nul\n");return 1;}
	if(argc==3){
		diskpath=format(".", size, argv[1]);
	}

	if (init_disk_sos(diskpath)){
		printf(RED"Erreur d'accès au disque.\n"DEF);
		return ERROR_FILE_ACCESS;
	}

	free(diskpath);

	update_first_free_byte();
	init_users_table();

	if (!write_super_block()){
		write_inodes_table();
		return NO_ERROR;
	}

	printf(RED"Erreur d'accès au disque.\n"DEF);
	return ERROR_FILE_ACCESS;
}
