/*! \file couche_1.c
	\brief  fichier regroupant les fonctions de la couche 1
	\author CHEVALLIER Guilhem, ALI-CHERIF Keylan, JUAN Victor
	\date 8 février 2022
*/


#include "OS_DEFINES.h"


// Guilhem
/* fonction permettant d'afficher le contenu d'un bloc */
void print_block(block_t *bloc)
{
	for(int i=0; i<BLOCK_SIZE; i++){
		printf("%.2x ", bloc->data[i]);
	}
	printf("\n");
}


// Victor
int shutoff_save(){

	if (write_super_block()) return ERROR_FILE_ACCESS;
	if (write_inodes_table()) return ERROR_FILE_ACCESS;

	return NO_ERROR;
}


// Guilhem
/* fonction permettant de calculer le nombre de blocs nécéssaire pour stocker
nb_bytes octets
compute_nblock is define if nb_bytes > 0
*/
uint compute_nblock(int nb_bytes){
	assert(nb_bytes > 0);

	uint size_in_blocks = nb_bytes/BLOCK_SIZE;
	if (nb_bytes%BLOCK_SIZE != 0) size_in_blocks++;
	return size_in_blocks;
}


// Guilhem
/* fonction permettant d'écrire un bloc de données sur le disque dur
write_block is define if pos > -1 and pos < TAILLE_FICHIER-3
*/
int write_block(block_t *bloc, uint pos){
	if (fseek(disk.storage, pos, SEEK_SET)){
		return ERROR_FILE_ACCESS;
	}
	if (!fwrite(bloc->data, BLOCK_SIZE, 1, disk.storage)){
		return ERROR_FILE_ACCESS;
	}
	return NO_ERROR;
}

// Guilhem
/* fonction permettant de lire un bloc de données sur le disque dur
read_block is define if pos > -1 and pos < TAILLE_FICHIER-3
*/
int read_block(block_t *bloc, uint pos){
	if (fseek(disk.storage, pos, SEEK_SET)){
		return ERROR_FILE_ACCESS;
	}
	if (!fread(bloc->data, BLOCK_SIZE, 1, disk.storage)){
		return ERROR_FILE_ACCESS;
	}
	return NO_ERROR;
}


// Guilhem
/*fonction convertissant un nombre entier sous forme de block*/
void convert_int_to_block(block_t* block, uint nombre)
{
	int i = 0;
	while (nombre >= 256){
		block->data[i] = nombre%256;
		nombre /= 256;
		i++;
	}

	block->data[i] = nombre%256;

	for(i=i+1; i<4; i++){
		block->data[i] = 0;
	}
}

// Guilhem
/*fonction convertissant un block sous forme d'entier */
void convert_block_to_int(block_t block, uint *nombre){
	*nombre = 0;
	for (int i=0; i<4; i++){
		*nombre += pow(256,i)*block.data[i];
	}
}

// Guilhem
int  gestion_ouverture(FILE *f, char* rep){
	if (f == NULL){
		perror(rep);
		return ERROR_FILE_ACCESS;
	}
	return NO_ERROR;
}

/*fonction initialisant la structure de données disk
la table d'inode et la table des utilisateurs seront initialisées ultérieurement*/
int init_disk_sos(char* rep){
	disk.super_block.number_of_files = 0;
	disk.super_block.number_of_users = 0;
	disk.super_block.nb_blocks_used = 0;
	disk.super_block.first_free_byte = 0;
	disk.storage = fopen(rep,"rb+");
	return gestion_ouverture(disk.storage, rep);
}
