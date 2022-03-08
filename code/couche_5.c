/*! \file couche_5.c
    \brief  fichier regroupant les fonctions de la couche 5
    \author JUAN Victor, CHEVALLIER Guilhem, ALI-CHERIF Keylan
    \date 7 mars 2022
*/

#include "OS_DEFINES.h"

// Victor
int cmd_ls(int type){
    printf("%32s", "filename");

    // Not Short
    if (type != 1) {
        printf(" | size    ");
        printf(" | date de création          ");
    }

    // Long
    if (type ==2){
        printf(" | date de modification      ");
        printf(" | owner id");
    }


    for (int i=0; i<disk.super_block.number_of_files; i++){
        printf("%32s | ", disk.inodes[i].filename);

        // Not Short
        if (type != 1) {
            printf(" | %8d", disk.inodes[i].size);
            printf(" | %s", disk.inodes[i].ctimestamp);
        }

        // Long
        if (type ==2){
            printf(" | %s", disk.inodes[i].mtimestamp);
            printf(" | %8d", disk.inodes[i].uid);
        }
    }

    return NO_ERROR;
}

// Victor
int cmd_cat(){

}

// Keylan
int cmd_rm(){

}


int cmd_cr(){

}


int cmd_edit(){

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