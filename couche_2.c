/*! \file couche_2.c
    \brief  fichier regroupant les fonctions de la couche 2
    \author CHEVALLIER Guilhem, ALI-CHERIF Keylan, JUAN Victor
    \date 8 février 2022
*/

#include "OS_DEFINES.h"


// fonction permettant de lire un block et de le convertir en int
void read_int_block(block_t block, int *pos, uint *buff)
{
  read_block(&block, *pos);
  convert_block_to_int(block, buff);
  *pos += 4;
}


// fonction permettant d'écrire un entier sous forme de block
void write_int_block(block_t block, int *pos, uint *buff)
{
  convert_int_to_block(&block, *buff);
  write_block(&block, *pos);
  *pos += 4;

}


/* Victor : Selon moi on devrait intégrer à la fonction le calcul de la taille totale */
// fonction permettant de lire une multitude de blocks
void read_mult_blocks(char *buff, int taille_totale, int *pos)
{
  errno = 0;
  fread(buff, taille_totale, 1, disk.storage);
  if (errno != 0){
    perror("Erreur de lecture");
    exit(errno);
  }
  *pos += taille_totale;
}


/* Victor : Idem*/
// fonction permettant d'écrire une multitude de blocks
void write_mult_blocks(char *buff, int taille_totale, int *pos)
{
  errno = 0;

  fwrite(buff, taille_totale, 1, disk.storage);

  if (errno != 0) {
    perror("Erreur d'écriture");
    exit(errno);
  }
  
  *pos += taille_totale;
}


// fonction permettant de lire la table d'inodes stockée dans le fichier disque pour initialiser la table
void read_inodes_table(){
  int j=0;
  int pos = INODES_START;
  block_t block;

  fseek(disk.storage, INODES_START, SEEK_SET);

  while(j<10 && !feof(disk.storage))
  {
    read_mult_blocks(disk.inodes[j].filename,FILENAME_MAX_SIZE,&pos);
    read_int_block(block,&pos,&disk.inodes[j].size);
    read_int_block(block,&pos,&disk.inodes[j].uid);
    read_int_block(block,&pos,&disk.inodes[j].uright);
    read_int_block(block,&pos,&disk.inodes[j].oright);
    read_mult_blocks(disk.inodes[j].ctimestamp,TIMESTAMP_SIZE,&pos);
    read_mult_blocks(disk.inodes[j].mtimestamp,TIMESTAMP_SIZE,&pos);
    read_int_block(block,&pos,&disk.inodes[j].nblock);
    read_int_block(block,&pos,&disk.inodes[j].first_byte);
    j++;
  }
}

// fonction permettant d'écrire la table d'inodes dans le fichier disque
void write_inodes_table(){
  int j=0;
  int pos=INODES_START;
  block_t block;

  fseek(disk.storage, INODES_START, SEEK_SET);

  while(j<10 && disk.inodes[j].size!=0){
    write_mult_blocks(disk.inodes[j].filename,FILENAME_MAX_SIZE,&pos);
    write_int_block(block,&pos,&disk.inodes[j].size);
    write_int_block(block,&pos,&disk.inodes[j].uid);
    write_int_block(block,&pos,&disk.inodes[j].uright);
    write_int_block(block,&pos,&disk.inodes[j].oright);
    write_mult_blocks(disk.inodes[j].ctimestamp,TIMESTAMP_SIZE,&pos);
    write_mult_blocks(disk.inodes[j].mtimestamp,TIMESTAMP_SIZE,&pos);
    write_int_block(block,&pos,&disk.inodes[j].nblock);
    write_int_block(block,&pos,&disk.inodes[j].first_byte);
    j++;

  }
}

// fonction réinitialisant une inode
void clear_inode(int indice)
{
  disk.inodes[indice].size = 0;
  disk.inodes[indice].uid = 0;
  disk.inodes[indice].uright = 0;
  disk.inodes[indice].oright = 0;
  disk.inodes[indice].nblock = 0;
  disk.inodes[indice].first_byte = 0;
}



// fonction permettant de compacter la table d'inode
void delete_inode(int indice){
  int j = indice+1;

  disk.super_block.number_of_files -= 1;
  disk.super_block.nb_blocks_used -= disk.inodes[indice].nblock;
  disk.super_block.first_free_byte -= disk.inodes[indice].size;
  
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
  }
  clear_inode(j-1);
}

void write_super_block(){
	block_t block;
	int pos = 0;
	write_int_block(block, &pos, &disk.super_block.number_of_files);
	write_int_block(block, &pos, &disk.super_block.number_of_users);
	write_int_block(block, &pos, &disk.super_block.nb_blocks_used );
	write_int_block(block, &pos, &disk.super_block.first_free_byte);
}

void read_super_block(){
	block_t block;
	int pos = 0;
	read_int_block(block, &pos, &disk.super_block.number_of_files);
	printf("%d\n", disk.super_block.number_of_files);
	read_int_block(block, &pos, &disk.super_block.number_of_users);
	printf("%d\n", disk.super_block.number_of_users);
	read_int_block(block, &pos, &disk.super_block.nb_blocks_used );
	printf("%d\n", disk.super_block.nb_blocks_used);
	read_int_block(block, &pos, &disk.super_block.first_free_byte);
	printf("%d\n", disk.super_block.first_free_byte);
}