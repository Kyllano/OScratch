
#include "OS_DEFINES.h"

virtual_disk_t disk;


/*
 * \brief fonction permettant de lire un block et de le convertir en int
 *
 */
void read_int_block(block_t block,int *pos,uint *buff)
{
  read_block(&block,*pos);
  print_block(&block);
  convert_block_to_int(block,buff);
  *pos+=4;
}


/*fonction permettant d'écrire un entier sous forme de block*/
void write_int_block(block_t block,int *pos,uint *buff)
{
  convert_int_to_block(&block,*buff);
  write_block(&block,*pos);
  *pos+=4;

}


/*fonction permettant de lire une multitude de blocks*/
void read_mult_blocks(char *buff,int taille_block,int *pos)
{
  errno=0;
  fread(buff,taille_block,1,disk.storage);
  if(errno!=0){
    perror("Erreur de lecture");
    exit(errno);
  }
  *pos+=taille_block;

}


/*fonction permettant d'écrire une multitude de blocks*/
void write_mult_blocks(char *buff,int taille_block,int *pos)
{
  errno=0;
  fwrite(buff,taille_block,1,disk.storage);
  if(errno!=0){
    perror("Erreur d'écriture");
    exit(errno);
  }
  *pos+=taille_block;
}


/*fonction permettant de lire la table d'inodes stockée dans le fichier disque*/
void read_inodes_table(){
  int j=0,pos=INODES_START;block_t block;
  fseek(disk.storage,INODES_START,SEEK_SET);
  while(j!=10 && !feof(disk.storage))
  {
    read_mult_blocks(disk.inodes[j].filename,FILENAME_MAX_SIZE,&pos);
    read_int_block(block,&pos,&disk.inodes[j].size);
    read_int_block(block,&pos,&disk.inodes[j].uid);
    read_int_block(block,&pos,&disk.inodes[j].uright);
    read_int_block(block,&pos,&disk.inodes[j].oright);
    read_mult_blocks(disk.inodes[j].ctimestamp,TIMESTAMP_SIZE,&pos);
    read_mult_blocks(disk.inodes[j].ctimestamp,TIMESTAMP_SIZE,&pos);
    read_int_block(block,&pos,&disk.inodes[j].nblock);
    read_int_block(block,&pos,&disk.inodes[j].first_byte);
    j++;

  }
}

/*fonction permettant d'écrire la table d'inodes dans le fichier disque*/
void write_inodes_table(){
  int j=0,pos=INODES_START;block_t block;
  fseek(disk.storage,INODES_START,SEEK_SET);
  while(j!=10 && disk.inodes[j].size!=0)
  {
    write_mult_blocks(disk.inodes[j].filename,FILENAME_MAX_SIZE,&pos);
    write_int_block(block,&pos,&disk.inodes[j].size);
    write_int_block(block,&pos,&disk.inodes[j].uid);
    write_int_block(block,&pos,&disk.inodes[j].uright);
    write_int_block(block,&pos,&disk.inodes[j].oright);
    write_mult_blocks(disk.inodes[j].ctimestamp,TIMESTAMP_SIZE,&pos);
    write_mult_blocks(disk.inodes[j].ctimestamp,TIMESTAMP_SIZE,&pos);
    write_int_block(block,&pos,&disk.inodes[j].nblock);
    write_int_block(block,&pos,&disk.inodes[j].first_byte);
    j++;

  }
}

/*tests*/
int main(int argc, char const *argv[]) {
  block_t block1,block2;
  disk.storage=fopen(argv[1],"wb+");
  fseek(disk.storage,49,SEEK_SET);
  convert_int_to_block(&block1,4096);
  write_block(&block1,49);
  read_block(&block2,49);
  print_block(&block2);
  read_inodes_table();
  fclose(disk.storage);
  return 0;
}


/*void delete_inode(int indice){
  int j=indice+1;
  while(j!=10 && disk.inodes[j].size!=0)
  {
    &disk.inodes[j-1].filename=&disk.inodes[j].filename;
    disk.inodes[j-1].filename=disk.inodes[j].filename;
    disk.inodes[j-1].filename=disk.inodes[j].filename;
    disk.inodes[j-1].filename=disk.inodes[j].filename;
    disk.inodes[j-1].filename=disk.inodes[j].filename;
    &disk.inodes[j-1].filename=&disk.inodes[j].filename;
    &disk.inodes[j-1].filename=&disk.inodes[j].filename;
    disk.inodes[j-1].filename=disk.inodes[j].filename;
    disk.inodes[j-1].filename=disk.inodes[j].filename;
  }
}*/
