/*! \file program.c
    \brief  fichier comportant la fonction main
    \author JUAN Victor
    \date 7 mars 2022
*/

#include "OS_DEFINES.h"


void flush(){
    int c;
    do {
        c=getchar();
    } while (c!='\n' && c!=EOF);
}

int main(int args, char* argv[]){

    if (args != 2){
        printf("usage : OScratch "UNDR"disk path"DEF"\n");
        return ERROR_ARGS;
    }

    int i = get_file_id(argv[1]);
    if (i==-1) return ERROR_FILE_ACCESS;

    char* command, param1, param2; 
    int loop = 1;

    while (loop){

        // Lecture de la commande
        printf("► ");
        scanf("%s",&command);

        // Interprétation puis vérification et exécution
        if (!strcmp(command, "ls")){
            scanf("%s", param1);
            if (!strcmp(param1,"")) cmd_ls(0);
            else if (!strcmp(param1, "-l")) cmd_ls(1);
            else if (!strcmp(param1, "-s")) cmd_ls(2);
            else printf("usage : ls [-l | -s]\n");
        }
        else if (!strcmp(command, "cat")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : cat "UNDR"nom de fichier"DEF"\n");
            else cmd_cat(param1);
        }
        else if (!strcmp(command, "rm")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : rm "UNDR"nom de fichier"DEF"\n");
            else cmd_rm(param1);
        }
        else if (!strcmp(command, "cr")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : cr "UNDR"nom de fichier"DEF"\n");
            else cmd_cr(param1);
        }
        else if (!strcmp(command, "edit")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : edit "UNDR"nom de fichier"DEF"\n");
            else cmd_edit(param1);
        }
        else if (!strcmp(command, "load")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : load "UNDR"nom de fichier"DEF"\n");
            else cmd_load(param1);
        }
        else if (!strcmp(command, "store")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : store "UNDR"nom de fichier"DEF"\n");
            else cmd_store(param1);
        }
        else if (!strcmp(command, "chown")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : chown "UNDR"nom de fichier"DEF" "UNDR"login autre utilisateur"DEF"\n");
            else {
                scanf("%s", param2);
                if (!strcmp(param2, "")) printf("usage : chown "UNDR"nom de fichier"DEF" "UNDR"login autre utilisateur"DEF"\n");
                else cmd_chown(param1, param2);
            }
        }
        else if (!strcmp(command, "chmod")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : chown "UNDR"nom de fichier"DEF" "UNDR"droit"DEF"\n");
            else {
                scanf("%s", param2);
                if (!strcmp(param2, "")) printf("usage : chown "UNDR"nom de fichier"DEF" "UNDR"droit"DEF"\n");
                else cmd_chmod(param1, param2);
            }
        }
        else if (!strcmp(command, "listusers")){
            cmd_listusers();
        }
        else if (!strcmp(command, "quit")){
            cmd_quit();
            loop = 0;
        }
        else if (!strcmp(command, "adduser")){
            cmd_adduser();
        }
        else if (!strcmp(command, "rmuser")){
            scanf("%s", param1);
            if (!strcmp(param1, "")) printf("usage : rmuser "UNDR"login"DEF"\n");
            else cmd_rmuser(param1);
        }
        // Affichage du résultat
    }

    return NO_ERROR;
}