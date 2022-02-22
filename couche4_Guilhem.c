#include "OS_DEFINES.h"
const session_t user;

int inode_fich(char *filename){
  for(int i=0;i<disk.super_block.number_of_files;i++){
    if(!strcmp(disk.inodes[i].filename,filename)){return i;}
  }

  return -1;
}

void write_fich(char *filename,file_t *fich){
  init_inode(filename,fich->size,disk.super_block.first_free_byte);
  disk.inodes[unused_inode].ctimestamp=timestamp();
  disk.inodes[unused_inode].mtimestamp=disk.inodes[get_unused_inode()].ctimestamp;
  disk.inodes[unused_inode].nblock=compute_nblock(fich->size);
  disk.inodes[unused_inode].uid=user.userid;
  disk.inodes[unused_inode].uright=0;
  disk.inodes[unused_inode].oright=0;
  write_mult_blocks(fich->data,fich->size,disk.super_block.first_free_byte);
  update_first_free_byte();
}

void modify_fich(char *filename,file_t *fich){
  if(disk.inodes[i_fich].size>fich->size){
    disk.inodes[unused_inode].mtimestamp=timestamp();
    disk.inodes[unused_inode].size=fich->size;
    disk.inodes[unused_inode].nblocks=compute_nblock(fich->size);
    write_mult_blocks(fich->data,fich->size,disk.inodes[get_unused_inode()].first_byte);
  }
  else{
    delete_inode(get_unused_inode());
    write_fich(filename,fich);
  }
}

void write_file(chae *filename,file_t *fich){
  int i_fich=inode_fich(filename,unused_inode);
  if(get_unused_inode()==-1 && i_fich==-1){
    printf("Il n'y a plus assez de place pour l'écriture d'un fichier sur le disque\n");
    return 1;
  }

  if(i_fich==-1){write_fich(filename,fich);}
  else{modify_fich(filename,fich));}
}
