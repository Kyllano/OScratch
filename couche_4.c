#include "OS_DEFINES.h"
const session_t user;

int inode_fich(char *filename){
  for(int i=0;i<disk.super_block.number_of_files;i++){
    if(!strcmp(disk.inodes[i].filename,filename)){return i;}
  }

  return -1;
}

void write_fich(char *filename,file_t *fich){
  int unused_inode=get_unused_inode();
  init_inode(filename,fich->size,disk.super_block.first_free_byte);
  strcpy(disk.inodes[unused_inode].ctimestamp,timestamp());
  strcpy(disk.inodes[unused_inode].mtimestamp,disk.inodes[unused_inode].ctimestamp);
  disk.inodes[unused_inode].nblock=compute_nblock(fich->size);
  disk.inodes[unused_inode].uid=user.userid;
  disk.inodes[unused_inode].uright=0;
  disk.inodes[unused_inode].oright=0;
  write_mult_blocks(fich->data,fich->size,disk.super_block.first_free_byte);
  update_first_free_byte();
}

void modify_fich(char *filename,file_t *fich,int i_fich){

  if(disk.inodes[i_fich].size>fich->size){
    disk.inodes[i_fich].mtimestamp=timestamp();
    disk.inodes[i_fich].size=fich->size;
    disk.inodes[i_fich].nblock=compute_nblock(fich->size);
    write_mult_blocks(fich->data,fich->size,disk.inodes[i_fich].first_byte);
  }
  else{
    delete_inode(get_unused_inode());
    write_fich(filename,fich);
  }
}

int write_file(char *filename,file_t *fich){
  int i_fich=inode_fich(filename);
  if(get_unused_inode()==-1 && i_fich==-1){
    printf("Il n'y a plus assez de place pour l'écriture d'un fichier sur le disque\n");
    return 1;
  }

  if(i_fich==-1){write_fich(filename,fich);return 0;}
  else{modify_fich(filename,fich,i_fich));return 0;}
}
