/*! \file couche_4.c
    \brief  fichier regroupant les fonctions de la couche 4
    \author JUAN Victor, CHEVALLIER Guilhem, ALI-CHERIF Keylan
    \date 8 février 2022
*/

#include "OS_DEFINES.h"


int get_file_id(char* filename){

    int i=0;
    while (!strcmp(disk.inodes[i].filename, filename) && i<disk.super_block.number_of_files) i++;

    if (i >= disk.super_block.number_of_files) return -1;
    else return i;
}


int read_file(char* filename, file_t* file){

    int i = get_file_id(filename);
    if (i==-1) return 0;
    
    read_mult_blocks(file->data, disk.inodes[i].nblock, disk.inodes[i].first_byte);
    file->size = disk.inodes[i].size;

    return 1;
}


int delete_file(char* filename){
    
    int i = get_file_id(filename);
    if (i==-1) return 0;

    delete_inode(i);
    
    return 1;
}

