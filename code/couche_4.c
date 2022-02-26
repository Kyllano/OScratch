#include "OS_DEFINES.h"
const session_t user;

int get_file_id(char* filename){

    int i=0;
    while (!strcmp(disk.inodes[i].filename, filename) && i<disk.super_block.number_of_files) i++;

    if (i >= disk.super_block.number_of_files) return -1;
    else return i;
}

void write_content(char *filename,file_t *fich){

	int unused_inode = get_unused_inode();
	init_inode(filename, fich->size, disk.super_block.first_free_byte);

	strcpy(disk.inodes[unused_inode].ctimestamp, timestamp());
	strcpy(disk.inodes[unused_inode].mtimestamp, disk.inodes[unused_inode].ctimestamp);
	disk.inodes[unused_inode].nblock = compute_nblock(fich->size);
	disk.inodes[unused_inode].uid = user.userid;
	disk.inodes[unused_inode].uright = rw;
	disk.inodes[unused_inode].oright = rw;

	write_mult_blocks((char *)fich->data, fich->size, disk.super_block.first_free_byte);
	update_first_free_byte();
}

void overwrite_content(char *filename, file_t *fich, int i_fich){

	if (disk.inodes[i_fich].size > fich->size){

		strcpy(disk.inodes[i_fich].mtimestamp, timestamp());
		disk.inodes[i_fich].size = fich->size;
		disk.inodes[i_fich].nblock = compute_nblock(fich->size);
		write_mult_blocks((char *)fich->data, fich->size,disk.inodes[i_fich].first_byte);

	}
	else{
		delete_inode(get_unused_inode());
		write_content(filename, fich);
	}
}

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


int read_file(char* filename, file_t* file){

    int i = get_file_id(filename);
    if (i==-1) return 0;

    read_mult_blocks((char *)file->data, disk.inodes[i].nblock,disk.inodes[i].first_byte);
    file->size = disk.inodes[i].size;

    return 1;
}


int delete_file(char* filename){

    int i = get_file_id(filename);
    if (i==-1) return 0;

    delete_inode(i);

    return 1;
}
