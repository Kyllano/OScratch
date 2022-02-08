/*! \file couche_3.c
    \brief  fichier regroupant les fonctions de la couche 3
    \author JUAN Victor (j'ai perdu à la courte paille si vous vous demandez)
    \date 8 février 2022
*/

#include "OS_DEFINES.h"

void init_users_table(){

    // Définition du login root
    char rootlogin[] = "root";
    int i=0;
    do {
        disk.users_table[ROOT_UID].login[i] = rootlogin[i];
        i++;
    } while (rootlogin[i]!='\0');
}

void write_users_table(){
    write_mult_blocks(disk.users_table, compute_nblock(sizeof(user_t[NB_USERS])), INODES_START+INODE_TABLE_SIZE);
}

void read_users_table(){
    fseek(disk.storage,INODES_START+INODE_TABLE_SIZE, SEEK_SET);

    for (int i=0; i<NB_USERS; i++){
        fread(disk.users_table[i].login, FILENAME_MAX_SIZE, 1, disk.storage);
        fread(disk.users_table[i].passwd, SHA256_BLOCK_SIZE*2 + 1, 1, disk.storage);
    }
}