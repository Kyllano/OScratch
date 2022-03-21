/*! \file   cmd_dump_inodes.c
    \brief  programme pour dump la table d'inodes
    \author JUAN Victor
    \date   inconnue
*/

#include "OS_DEFINES.h"
#include "formatting.h"

#include <fcntl.h>

int main(int argc, char* argv[]){

    // Erreur d'arguments
    if (argc!=2){
        printf(RED"Erreur d'arguments.\n"DEF);
        printf("usage : %s "UNDR"chemin_du_disque\n"DEF, argv[0]);
        exit(1);
    }

    disk.storage = fopen(argv[1], "r");

    // Erreur d'ouverture du disque
    if (disk.storage == NULL){
        printf(RED"Erreur d'accès.\n"DEF);
        printf("Le disque %s ne peut être lu\n",argv[1]);
        perror("argv[]");
        exit(2);
    }

    // Initialisations
    block_t bloc;
    fseek(disk.storage, disk.inodes[0].first_byte, SEEK_SET);
    
    // C'est parti
    for (int i=0; i<disk.super_block.number_of_files; i++){
        
        printf(BLUE BOLD"\n-- INODE %d --\n\n"DEF, i+1);

        printf(BLUE"\nfilename :"DEF" (%s)\n",disk.inodes[i].filename);
        for (int j=0; j<FILENAME_MAX_SIZE/BLOCK_SIZE;j++){
            fread(bloc.data,BLOCK_SIZE,1,disk.storage);
            print_block(&bloc);
        }

        printf(BLUE"\nsize :\n"DEF" (%d)",disk.inodes[i].size);
        fread(bloc.data,BLOCK_SIZE,1,disk.storage);

        printf(BLUE"\nuid :\n"DEF" (%d)",disk.inodes[i].uid);
        fread(bloc.data,BLOCK_SIZE,1,disk.storage);

        printf(BLUE"\nuright :\n"DEF" (%d)",disk.inodes[i].uright);
        fread(bloc.data,BLOCK_SIZE,1,disk.storage);

        printf(BLUE"\noright :\n"DEF" (%d)",disk.inodes[i].oright);
        fread(bloc.data,BLOCK_SIZE,1,disk.storage);

        printf(BLUE"\nctimestamp :"DEF" (%s)\n",disk.inodes[i].ctimestamp);
        for (int j=0; j<TIMESTAMP_SIZE/BLOCK_SIZE;j++){
            fread(bloc.data,BLOCK_SIZE,1,disk.storage);
            print_block(&bloc);
        }

        printf(BLUE"\nmtimestamp :"DEF" (%s)\n",disk.inodes[i].ctimestamp);
        for (int j=0; j<TIMESTAMP_SIZE/BLOCK_SIZE;j++){
            fread(bloc.data,BLOCK_SIZE,1,disk.storage);
            print_block(&bloc);
        }

        printf(BLUE"\nnblock :\n"DEF" (%d)",disk.inodes[i].nblock);
        fread(bloc.data,BLOCK_SIZE,1,disk.storage);

        printf(BLUE"\nfirst_byte :\n"DEF" (%d)",disk.inodes[i].first_byte);
        fread(bloc.data,BLOCK_SIZE,1,disk.storage);   
    }

    return 0;
}