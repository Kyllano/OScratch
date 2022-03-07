/*! \file couche_3.c
    \brief  fichier regroupant les fonctions de la couche 3
    \author JUAN Victor, CHEVALLIER Guilhem, ALI-CHERIF Keylan
    \date 7 mars 2022
*/

#include "OS_DEFINES.h"


session_t user;
/*
user.userid=1;*/

// Victor
int get_file_id(char* filename){

    int i=0;
    while (strcmp(disk.inodes[i].filename, filename) && i<disk.super_block.number_of_files) i++;

    if (i >= disk.super_block.number_of_files) return -1;
    else return i;
}


// Guilhem
void write_content(char *filename,file_t *fich){
  printf("taille write : %d\n",fich->size);
	int unused_inode = get_unused_inode();
	init_inode(filename, fich->size, disk.super_block.first_free_byte);

	strcpy(disk.inodes[unused_inode].ctimestamp, timestamp());
	strcpy(disk.inodes[unused_inode].mtimestamp, disk.inodes[unused_inode].ctimestamp);
	disk.inodes[unused_inode].nblock = compute_nblock(fich->size);
	disk.inodes[unused_inode].uid = 1 ;/*user.userid;*/
	disk.inodes[unused_inode].uright = rw;
	disk.inodes[unused_inode].oright = rw;

	write_mult_blocks((char *)fich->data, fich->size, &disk.super_block.first_free_byte);
	update_first_free_byte();
  disk.super_block.number_of_files ++;
}


// Guilhem
void overwrite_content(char *filename, file_t *fich, int i_fich){

	if (disk.inodes[i_fich].size >= fich->size){

		strcpy(disk.inodes[i_fich].mtimestamp, timestamp());
		disk.inodes[i_fich].size = fich->size;
		disk.inodes[i_fich].nblock = compute_nblock(fich->size);
		write_mult_blocks((char *)fich->data, fich->size, &disk.inodes[i_fich].first_byte);

	}
	else{
		delete_inode(i_fich);
		write_content(filename, fich);
	}
}


// Guilhem
int write_file(char *filename,file_t *fich){

	int i_fich = get_file_id(filename);

	if (get_unused_inode()==-1 && i_fich==-1){
		printf("Il n'y a plus assez de place pour l'écriture d'un fichier sur le disque\n");
		return ERROR_DISK_FULL;
	}

	if (i_fich == -1){
		write_content(filename, fich);
		return NO_ERROR;
	}
	else {
		overwrite_content(filename, fich, i_fich);
		return NO_ERROR;
	}
}

// Victor
int read_file(char* filename, file_t* file){

    int i = get_file_id(filename);
    if (i==-1) return ERROR_FILE_ACCESS;

    read_mult_blocks((char *)file->data, disk.inodes[i].size, &disk.inodes[i].first_byte);
    file->size = disk.inodes[i].size;

    return NO_ERROR;
}

// Victor
int delete_file(char* filename){

    int i = get_file_id(filename);
    if (i==-1) return ERROR_FILE_ACCESS;

    delete_inode(i);

    return NO_ERROR;
}


// Ecrit un fichier hote pasé en parametre dans un fichier empty file passé en parametre puis ecris ce fichier empty dans le disk
// Keylan
int load_file_from_host(char* filename_on_host, file_t* empty_file){
	FILE* fichier_hote = fopen(filename_on_host, "r");
	if (fichier_hote == NULL){
		return ERROR_FILE_ACCESS;
	}


	uchar c;
	empty_file->size = 0;
	c = fgetc(fichier_hote);
	while (!feof(fichier_hote) && empty_file->size < MAX_FILE_SIZE){
		empty_file->data[empty_file->size] = c;
		empty_file->size ++;
		c = fgetc(fichier_hote);
	}
  	// if (empty_file->size < MAX_FILE_SIZE) empty_file->size--;

	fclose(fichier_hote);
	fichier_hote = NULL;

	if (write_file(filename_on_host, empty_file)) return ERROR_INODES_FULL;
	if (empty_file->size == MAX_FILE_SIZE) return ERROR_FILE_TOO_BIG;	// Le fichier est stocké mais tronqué
	else return NO_ERROR;
}


// Ecris sur l hote un des fichier du systeme SOS passé en parametre
// Keylan
int store_file_to_host(char* filename){
	file_t file;
	if (read_file(filename, &file)!=0) return ERROR_FILE_ACCESS;

	FILE* host_file = fopen(filename, "w+");
	if (host_file == NULL) return ERROR_RIGHTS;

	for (int i=0; i < file.size; i++){
		fputc(file.data[i] , host_file);
	}

	fclose(host_file);
	return NO_ERROR;
}
