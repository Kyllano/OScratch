#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "OS_DEFINES.h"

virtual_disk_t disk;

/* fonction permettant d'afficher le contenu d'un bloc */
void print_block(block_t *bloc)
{
  for(int i=0;i<BLOCK_SIZE;i++)
  {
    printf("%.2x ",bloc->data[i]);
  }
  printf("\n");
}

//Peut-être que ça deviendra une fonction int si on doit retourner un n° d'erreur
void shutoff_save(){

    fseek(disk.storage, INODES_START, SEEK_SET);

    for (int i=0; i<disk.super_block.number_of_files; i++){ //i : indice de l'inode
        //     champ                        taille bloc nombre de blocs     stream
        fwrite(disk.inodes[i].filename,    BLOCK_SIZE, FILENAME_MAX_SIZE,  disk.storage);
        fwrite(&disk.inodes[i].size,       BLOCK_SIZE, 1,                  disk.storage);
        fwrite(&disk.inodes[i].uid,        BLOCK_SIZE, 1,                  disk.storage);
        fwrite(&disk.inodes[i].uright,     BLOCK_SIZE, 1,                  disk.storage);
        fwrite(&disk.inodes[i].oright,     BLOCK_SIZE, 1,                  disk.storage);
        fwrite(disk.inodes[i].ctimestamp,  BLOCK_SIZE, TIMESTAMP_SIZE,     disk.storage);
        fwrite(disk.inodes[i].mtimestamp,  BLOCK_SIZE, TIMESTAMP_SIZE,     disk.storage);
        fwrite(&disk.inodes[i].nblock,     BLOCK_SIZE, 1,                  disk.storage);
        fwrite(&disk.inodes[i].first_byte, BLOCK_SIZE, 1,                  disk.storage);
    }
}

/* fonction permettant de calculer le nombre de blocs nécéssaire pour stocker
  nb_bytes octets
  compute_nblock is define if nb_bytes > 0
  */
void compute_nblock(int nb_bytes,int *nb_blocs)
{
  assert(nb_bytes>0);
  *nb_blocs=nb_bytes/BLOCK_SIZE;
  if(nb_bytes%BLOCK_SIZE!=0){*nb_blocs+=1;}
}


/* fonction permettant d'écrire un bloc de données sur le disque dur
   write_block is define if pos > -1 and pos < TAILLE_FICHIER-3
   */
void write_block(block_t *bloc,int pos)
{
  assert(pos>-1);
  errno=0;
  fseek(disk.storage,pos,SEEK_SET);
  fwrite(bloc->data,BLOCK_SIZE,1,disk.storage);
  if(errno!=0){
    perror("erreur d'écriture");
    exit(errno);
  }
}

/* fonction permettant de lire un bloc de données sur le disque dur
   read_block is define if pos > -1 and pos < TAILLE_FICHIER-3
   */
void read_block(block_t *bloc,int pos)
{
  assert(pos>-1);
  errno=0;
  fseek(disk.storage,pos,SEEK_SET);
  fread(bloc->data,BLOCK_SIZE,1,disk.storage);
  if(errno!=0){
    perror("erreur de lecture");
    exit(errno);
  }

}

/*fonction convertissant un nombre entier sous forme de block*/
void convert_int_to_block(block_t* block,int nombre)
{

  block->data[0]=nombre%256;
  nombre/=256;
  int i=0;
  while(nombre>=256)
  {
    block->data[++i]=nombre%256;
    nombre/=256;
  }

}


/*fonction convertissant un block sous forme d'entier */
void convert_block_to_int(block_t block,int *nombre)
{
  *nombre=0;
  for(int i=0;i<4;i++)
  {
    *nombre+=pow(256,i)*block.data[i];
  }
}

void gestion_ouverture(FILE *f,char rep)
{
  if(f==NULL){
    perror(rep);
    exit(1);
  }
}

/*fonction initialisant la structure de données disk
  la table d'inode et la table des utilisateurs seront initialisées ultérieurement*/
void init_disk_sos(char rep)
{
  disk.storage=fopen(rep,"wb+");
  gestion_ouverture(disk.storage,rep);
  disk.super_block.number_of_files=0;
  disk.super_block.number_of_users=0;
  disk.super_block.nb_blocks_used=0;
  disk.super_block.first_free_byte=0;
}



int main(int argc, char const *argv[]) {
  block_t bloc;
  int beez=1025;
  disk.storage=fopen(argv[1],"wb+");
  write_int(beez,105);
  read_block(&bloc,105);
  print_block(&bloc);
  fclose(disk.storage);
  return 0;
}
