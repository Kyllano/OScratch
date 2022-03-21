/*! \file couche_2.c
	\brief  fichier regroupant les fonctions de la couche 2
	\author CHEVALLIER Guilhem, ALI-CHERIF Keylan, JUAN Victor
	\date 8 février 2022
*/

#include "OS_DEFINES.h"


// Guilhem
// fonction permettant de lire un block et de le convertir en int
int read_int_block(block_t block, uint *pos, uint *buff){
	if (read_block(&block, *pos)){
		return ERROR_FILE_ACCESS;
	}
	convert_block_to_int(block, buff);
	*pos += 4;
	return NO_ERROR;
}



// Guilhem
// fonction permettant d'écrire un entier sous forme de block
int write_int_block(block_t block, uint *pos, uint *buff){
	convert_int_to_block(&block, *buff);
	if (write_block(&block, *pos)){
		return ERROR_FILE_ACCESS;
	}
	*pos += 4;
	return NO_ERROR;
}

// Guilhem
// fonction permettant de lire une multitude de blocks
void read_mult_blocks(char *s, int nblock, uint *pos,int taille_max_s){
	block_t block;
	fseek(disk.storage, *pos, SEEK_SET);

	for (int j=0; j<BLOCK_SIZE*nblock; j+=4){
		
		read_block(&block, *pos);
		for (int k=0; k<4; k++){
			if(j+k<taille_max_s){
				s[j+k] = block.data[k];
			}
		}
		*pos += BLOCK_SIZE;
	}
}

// Guilhem
// fonction permettant d'écrire une multitude de blocks
void write_mult_blocks(char *s, int nblock, uint *pos,int taille_max_s){
	block_t block;
	fseek(disk.storage, *pos, SEEK_SET);

	for (int j=0; j<BLOCK_SIZE*nblock; j+=4){
		for (int k=0; k<4; k++){
			block.data[k] = (j+k>=taille_max_s ? '\0' : s[j+k]);
		}
		write_block(&block,*pos);
		*pos += BLOCK_SIZE;
	}
}

// Guilhem
// fonction permettant de lire la table d'inodes stockée dans le fichier disque pour initialiser la table
int read_inodes_table(){
	int j=0;
	uint pos = INODES_START;
	block_t block;

	if (fseek(disk.storage, INODES_START, SEEK_SET)){
		return ERROR_FILE_ACCESS;
	}

	while (j < disk.super_block.number_of_files){
		read_mult_blocks(disk.inodes[j].filename,compute_nblock(FILENAME_MAX_SIZE),&pos,FILENAME_MAX_SIZE);
		read_int_block(block,&pos,&disk.inodes[j].size);
		read_int_block(block,&pos,&disk.inodes[j].uid);
		read_int_block(block,&pos,&disk.inodes[j].uright);
		read_int_block(block,&pos,&disk.inodes[j].oright);
		read_mult_blocks(disk.inodes[j].ctimestamp,compute_nblock(TIMESTAMP_SIZE),&pos,TIMESTAMP_SIZE);
		read_mult_blocks(disk.inodes[j].mtimestamp,compute_nblock(TIMESTAMP_SIZE),&pos,TIMESTAMP_SIZE);
		read_int_block(block,&pos,&disk.inodes[j].nblock);
		read_int_block(block,&pos,&disk.inodes[j].first_byte);
		j++;
	}

	return NO_ERROR;
}


// Guilhem
// fonction permettant d'écrire la table d'inodes dans le fichier disque
int write_inodes_table(){
	int j=0;
	uint pos=INODES_START;
	block_t block;

	if (fseek(disk.storage, INODES_START, SEEK_SET)){
		return ERROR_FILE_ACCESS;
	}

	while (j < disk.super_block.number_of_files){
		write_mult_blocks(disk.inodes[j].filename,compute_nblock(FILENAME_MAX_SIZE),&pos,FILENAME_MAX_SIZE);
		write_int_block(block,&pos,&disk.inodes[j].size);
		write_int_block(block,&pos,&disk.inodes[j].uid);
		write_int_block(block,&pos,&disk.inodes[j].uright);
		write_int_block(block,&pos,&disk.inodes[j].oright);
		write_mult_blocks(disk.inodes[j].ctimestamp,compute_nblock(TIMESTAMP_SIZE),&pos,TIMESTAMP_SIZE);
		write_mult_blocks(disk.inodes[j].mtimestamp,compute_nblock(TIMESTAMP_SIZE),&pos,TIMESTAMP_SIZE);
		write_int_block(block,&pos,&disk.inodes[j].nblock);
		write_int_block(block,&pos,&disk.inodes[j].first_byte);
		j++;
	}
	return NO_ERROR;
}


// Guilhem
// fonction réinitialisant une inode
void clear_inode(int indice){
	strcpy(disk.inodes[indice].filename, "");
	strcpy(disk.inodes[indice].ctimestamp, "");
	strcpy(disk.inodes[indice].mtimestamp, "");
	disk.inodes[indice].size = 0;
	disk.inodes[indice].uid = 0;
	disk.inodes[indice].uright = 0;
	disk.inodes[indice].oright = 0;
	disk.inodes[indice].nblock = 0;
	disk.inodes[indice].first_byte = 0;
}

// Victor
int get_unused_inode(){
	int i=0;
	// TODO Ajouter le cas ou la table d inode est pleine
	while (disk.inodes[i].size != 0 && i < INODE_TABLE_SIZE) i++;

	if (i == INODE_TABLE_SIZE) return -1;
	else return i;
}


int write_super_block(){
	block_t block;
	uint pos = 0;

	if (write_int_block(block, &pos, &disk.super_block.number_of_files)) return ERROR_FILE_ACCESS;

	write_int_block(block, &pos, &disk.super_block.number_of_users);
	write_int_block(block, &pos, &disk.super_block.nb_blocks_used );
	write_int_block(block, &pos, &disk.super_block.first_free_byte);
	return NO_ERROR;
}

int read_super_block(){
	block_t block;
	uint pos = 0;

	if (read_int_block(block, &pos, &disk.super_block.number_of_files))return ERROR_FILE_ACCESS;

	read_int_block(block, &pos, &disk.super_block.number_of_users);
	read_int_block(block, &pos, &disk.super_block.nb_blocks_used );
	read_int_block(block, &pos, &disk.super_block.first_free_byte);
	return NO_ERROR;
}

//A n'appeler que si la table d'inode a été initialisée
void update_first_free_byte(){
	if (get_unused_inode() == 0){
		disk.super_block.first_free_byte = (INODE_TABLE_SIZE*INODE_SIZE)*4 + INODES_START + 1;
	}
	else{
		disk.super_block.first_free_byte = disk.inodes[get_unused_inode()-1].first_byte + disk.inodes[get_unused_inode()-1].size +1;
	}
}



// Guilhem
// fonction permettant de compacter la table d'inode
void delete_inode(int indice){
	int j = indice+1;

	// update du super bloc
	disk.super_block.number_of_files -= 1;
	disk.super_block.nb_blocks_used -= disk.inodes[indice].nblock;

	// suppression
	while(j<10 && disk.inodes[j].size!=0){
		strcpy(disk.inodes[j-1].filename,disk.inodes[j].filename);
		disk.inodes[j-1].size=disk.inodes[j].size;
		disk.inodes[j-1].uid=disk.inodes[j].uid;
		disk.inodes[j-1].uright=disk.inodes[j].uright;
		disk.inodes[j-1].oright=disk.inodes[j].oright;
		strcpy(disk.inodes[j-1].ctimestamp,disk.inodes[j].ctimestamp);
		strcpy(disk.inodes[j-1].mtimestamp,disk.inodes[j].mtimestamp);
		disk.inodes[j-1].nblock=disk.inodes[j].nblock;
		disk.inodes[j-1].first_byte=disk.inodes[j].first_byte;
		j++;
	}
	clear_inode(j-1);
	update_first_free_byte();
}



// Victor
void init_inode(char* filename, uint size, uint pos){
	int i = get_unused_inode();
	strcpy(disk.inodes[i].filename, filename);
	disk.inodes[i].size = size;
	disk.inodes[i].first_byte = pos;
}
