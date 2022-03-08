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

int cmd_rm(){
  int i;
  if((i=get_file_id(filename))==-1){
    return ERROR_FILE_ACCESS;
  }
  if((disk.inodes[i].uid==user.userid && disk.inodes[i].uright!=rW&& disk.inodes[i].uright!=RW)
  || (disk.inodes[i].uid!=user.userid && disk.inodes[i].oright!=rW && disk.inodes[i].oright!=RW)){
    return 2;
  }
  return delete_file(filename);
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
  disk.inodes[unused_inode].nblock = 1;
  disk.inodes[unused_inode].uid = user.userid;
  disk.inodes[unused_inode].uright = rw;
  disk.inodes[unused_inode].oright = rw;
  update_first_free_byte();
  disk.super_block.number_of_files ++;
  return 0;

}


int cmd_edit(char *filename){
  int i;file_t file;char c;
  if((i=get_file_id(filename))==-1){
    return ERROR_FILE_ACCESS;
  }
  if((disk.inodes[i].uid==user.userid && disk.inodes[i].uright!=Rw && disk.inodes[i].uright!=RW)
  || (disk.inodes[i].uid!=user.userid && disk.inodes[i].oright!=Rw && disk.inodes[i].oright!=RW)){
    return 2;
  }
  printf("entrez le contenu du fichier (terminer la saisie avec une tabulation)\n");
  file.size=0;
  while((c=fgetc(stdin))!='\t' && file.size!=MAX_FILE_SIZE){
    file.data[file.size++]=c;
  }
  return write_file(filename,&file);


}



int cmd_load(char *filename){
  file_t *file;
  return load_file_from_host(filename,file);

}


int cmd_store(char *filename){
  return store_file_to_host(filename);
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
