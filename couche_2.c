#include "OS_DEFINES.h"


// fonction permettant de lire un block et de le convertir en int
void read_int_block(block_t block,int *pos,uint *buff)
{
  read_block(&block,*pos);
  convert_block_to_int(block,buff);
  *pos+=4;
}


// fonction permettant d'écrire un entier sous forme de block
void write_int_block(block_t block,int *pos,uint *buff)
{
  convert_int_to_block(&block,*buff);
  write_block(&block,*pos);
  *pos+=4;

}


/* Victor : Selon moi on devrait intégrer à la fonction le calcul de la taille totale */
// fonction permettant de lire une multitude de blocks
void read_mult_blocks(char *buff,int taille_totale,int *pos)
{
  errno=0;
  fread(buff,taille_totale,1,disk.storage);
  if(errno!=0){
    perror("Erreur de lecture");
    exit(errno);
  }
  *pos+=taille_totale;
}


/* Victor : Idem*/
// fonction permettant d'écrire une multitude de blocks
void write_mult_blocks(char *buff,int taille_totale,int *pos)
{
  errno=0;
  fwrite(buff,taille_totale,1,disk.storage);
  if(errno!=0){
    perror("Erreur d'écriture");
    exit(errno);
  }
  *pos+=taille_totale;
}


// fonction permettant de lire la table d'inodes stockée dans le fichier disque pour initialiser la table
void read_inodes_table(){
  int j=0,pos=INODES_START;block_t block;
  fseek(disk.storage,INODES_START,SEEK_SET);
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
  int j=0,pos=INODES_START;block_t block;
  fseek(disk.storage,INODES_START,SEEK_SET);
  while(j<10 && disk.inodes[j].size!=0)
  {
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
  disk.inodes[indice].size=0;
  disk.inodes[indice].uid=0;
  disk.inodes[indice].uright=0;
  disk.inodes[indice].oright=0;
  disk.inodes[indice].nblock=0;
  disk.inodes[indice].first_byte=0;
}



// fonction permettant de compacter la table d'inode
void delete_inode(int indice){
  int j=indice+1;
  while(j<10 && disk.inodes[j].size!=0)
  {
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
  if(j<10){
    clear_inode(j);
  }

}

void write_super_block(){
    write_block(disk.super_block.number_of_files, 0);
    write_block(disk.super_block.number_of_users, 1);
    write_block(disk.super_block.nb_blocks_used , 2);
    write_block(disk.super_block.first_free_byte, 3);
}