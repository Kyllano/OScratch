/*! \file couche_5.c
    \brief  fichier regroupant les fonctions de la couche 5
    \author JUAN Victor, CHEVALLIER Guilhem, ALI-CHERIF Keylan
    \date 7 mars 2022
*/

#include "OS_DEFINES.h"

// Victor
int cmd_ls(int type){
    printf(BOLD WHITE"filename                        "DEF);

    // Not Short
    if (type != 1) {
        printf(" │ "BOLD WHITE"size    "DEF);
        printf(" │ "BOLD WHITE"date de création          "DEF);
    }

    // Long
    if (type ==2){
        printf(" │ "BOLD WHITE"date de modification      "DEF);
        printf(" │ "BOLD WHITE"owner id"DEF);
    }

    printf("\n");


    for (int i=0; i<disk.super_block.number_of_files; i++){
        printf("%32s │ ", disk.inodes[i].filename);

        // Not Short
        if (type != 1) {
            printf(" │ %8d", disk.inodes[i].size);
            printf(" │ %s", disk.inodes[i].ctimestamp);
        }

        // Long
        if (type ==2){
            printf(" │ %s", disk.inodes[i].mtimestamp);
            printf(" │ %8d", disk.inodes[i].uid);
        }

        printf("\n");
    }

    return NO_ERROR;
}

// Victor
int cmd_cat(){

}

// Guilhem
int cmd_rm(){

}

// Guilhem
int cmd_cr(){

}

// Guilhem
int cmd_edit(){

}

// Guilhem
int cmd_load(){

}

// Guilhem
int cmd_store(){

}

// Keylan
int cmd_chown(){

}

// KEylan
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