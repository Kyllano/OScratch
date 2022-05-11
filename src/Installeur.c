/*! \file 	installeur.c
	\brief  fichier du code de l'installeur
	\author JUAN Victor, CHEVALLIER Guilhem
	\date 	11 mai 2022
*/


#include "OS_DEFINES.h"
// Guilhem

// create a file named di (i = diskid) in directory dirname of size bytes
// the file is initialized with 0
// dirname must be a valid directory
// 0 <= diskid < 10
void format(char *dirname, int size, int diskid){
	char filename[strlen(dirname)+4];
	snprintf(filename, strlen(dirname)+4, "%s/d%d", dirname, diskid);
	printf("%s\n", filename);
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
	//if (argc!=3) {
	if (argc!=2) {
		//printf("usage %s  existing_dir_to_store_disk disk_size\n", argv[0]);
		printf(YELLOW"usage : %s disk_size\n"DEF, argv[0]);
		return 0;
	}
	//int size = atoi(argv[2]);
	int size = atoi(argv[1]);
	if(argc==3) {
		int diskid = 0;
		//format(argv[1], size, diskid);
		format("./", size, diskid);
	}

	if (init_disk_sos("d0")){
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
