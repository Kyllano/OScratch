/*! \file couche_5.c
    \brief  fichier regroupant les fonctions de la couche 5
    \author JUAN Victor, CHEVALLIER Guilhem, ALI-CHERIF Keylan
    \date 7 mars 2022
*/

#include "OS_DEFINES.h"

// Victor
int cmd_ls(){

}

// Victor
int cmd_cat(){

}

// Keylan
int cmd_rm(){

}


int cmd_cr(char *filename){
  int unused_inode;
  if((unused_inode=get_unused_inode())==-1){
    printf("il n'y a plus de d'espace disque disponible la création d'un fichier\n");
    return 1;
  }
  init_inode(filename,1, disk.super_block.first_free_byte);
  strcpy(disk.inodes[unused_inode].ctimestamp, timestamp());
  strcpy(disk.inodes[unused_inode].mtimestamp, disk.inodes[unused_inode].ctimestamp);
  disk.inodes[unused_inode].nblock = 1
  disk.inodes[unused_inode].uid = user.userid;
  disk.inodes[unused_inode].uright = rw;
  disk.inodes[unused_inode].oright = rw;
  update_first_free_byte();
  disk.super_block.number_of_files ++;
  return 0;

}


int cmd_edit(char *filename){
  int i;
  if((i=get_file_id(filename))==-1){
    return 1;
  }
  if(disk.inodes[i].uid==user.userid && (disk.inodes[i].uright=Rw || disk.inodes[i].uright=RW))
}



int cmd_load(){

}


int cmd_store(){

}


int cmd_chown(){

}


int cmd_chmod(){

}

// Keylan
int cmd_listusers(){

}

// Victor
int cmd_quit(){

}

// Keylan
int cmd_adduser(){

}

// Keylan
int cmd_rmuser(){

}
