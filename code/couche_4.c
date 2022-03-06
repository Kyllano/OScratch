#include "OS_DEFINES.h"


session_t user;
/*
user.userid=1;*/

int get_file_id(char* filename){

    int i=0;
    while (strcmp(disk.inodes[i].filename, filename) && i<disk.super_block.number_of_files) i++;

    if (i >= disk.super_block.number_of_files) return -1;
    else return i;
}


/**
  *\author Guilhem
  */
void write_content(char *filename,file_t *fich){

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
}


/**
  *\author Guilhem
  */
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



/**
  *\author Guilhem
  */
int write_file(char *filename,file_t *fich){

	int i_fich = get_file_id(filename);

	if (get_unused_inode()==-1 && i_fich==-1){
		printf("Il n'y a plus assez de place pour l'écriture d'un fichier sur le disque\n");
		return 1;
	}

	if (i_fich == -1){
		write_content(filename, fich);
		return 0;
	}
	else {
		overwrite_content(filename, fich, i_fich);
		return 0;
	}
}

// Victor
int read_file(char* filename, file_t* file){

    int i = get_file_id(filename);
    if (i==-1) return 1;

    read_mult_blocks((char *)file->data, disk.inodes[i].nblock, &disk.inodes[i].first_byte);
    file->size = disk.inodes[i].size;

    return 0;
}

// Victor
int delete_file(char* filename){

    int i = get_file_id(filename);
    if (i==-1) return 1;

    delete_inode(i);

    return 0;
}

/**
 * Ecris un fichier hote pasé en parametre dans un fichier empty file passé en parametre puis ecris ce fichier empty dans le disk
 * codes d erreur :
 * 0 si tout va bien
 * 1 si probleme d acces au fichier de l hote
 * 2 si le fichier est trop gros (dans ce cas, on l'écrit quand meme, mais on le stock tronqué)
 * 3 si y'a plus de place dans la table d'inode
 */
int load_file_from_host(char* filename_on_host, file_t* empty_file){
	FILE* fichier_hote = fopen(filename_on_host, "r");
	if (fichier_hote == NULL){
		return 1;
	}

	uchar c;
	empty_file->size = 0;
	while ((c=fgetc(fichier_hote) != EOF )&& empty_file->size < MAX_FILE_SIZE){
		empty_file->data[empty_file->size] = c;
    printf("caractère %d = %c\n",empty_file->size,c);
		empty_file->size ++;
	}

	fclose(fichier_hote);
	fichier_hote = NULL;

	if (write_file(filename_on_host, empty_file)){
		return 3;
	}

	if (empty_file->size == MAX_FILE_SIZE){
		return 2;
	}
	else{
		return 0;
	}
}


/**
 * Ecris sur l hote un des fichier du systeme SOS passé en parametre
 * Codes d erreur :
 * 0 si tout va bien
 * 1 si le fichier n existe pas ou n est pas trouvé (mauvais filename)
 * 2 si problème de droit d'ecriture sur l'hote
 * 3 il y a un probleme avec le fputc (vienvrais de l'hote)
 */
int store_file_to_host(char* filename){
	file_t file;
	if (read_file(filename, &file)){
		return 1;
	}

	FILE* host_file = fopen(filename, "w");
	if (host_file == NULL){
		return 2;
	}

	for (int i=0; i < file.size; i++){
		if(fputc(file.data[i] , host_file) == EOF){
			return 3;
		}
	}

	fclose(host_file);
	return 0;
}
