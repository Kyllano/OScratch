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

int main(int argc, char* argv[]){

    if (argc != 2){
        printf(YELLOW"usage : %s "UNDR"disk path"DEF"\n", argv[0]);
        return ERROR_ARGS;
    }

    FILE* fichier_hote = fopen(argv[1], "rw");
	if (fichier_hote == NULL){
		return ERROR_FILE_ACCESS;
	}

    char cmdline[CMDLINE_MAX_SIZE];
    char* strToken;
    cmd_t cmd;
    cmd.tabArgs = malloc(sizeof(char**)); 
    int loop = 1;

    while (loop){

        // Lecture de la cmd.tabArgs[0]e
        printf("► ");
        fgets(cmdline, CMDLINE_MAX_SIZE, stdin);

        //printf(GREEN"Still alive\n"DEF);

        cmd.nbArgs = 0;
        realloc(cmd.tabArgs, sizeof(char**));
        strToken = strtok(cmdline, " ");

        while (strToken!=NULL){
            realloc(cmd.tabArgs[cmd.nbArgs], strlen(strToken));
            realloc(cmd.tabArgs, cmd.nbArgs*sizeof(char**));
            strcpy(cmd.tabArgs[cmd.nbArgs++], strToken);
            strToken = strtok(NULL, " ");
        }

        // Interprétation puis vérification et exécution
        if (!strcmp(cmd.tabArgs[0], "ls")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1],"")) cmd_ls(0);
            else if (!strcmp(cmd.tabArgs[1], "-l")) cmd_ls(1);
            else if (!strcmp(cmd.tabArgs[1], "-s")) cmd_ls(2);
            else printf(YELLOW"usage : ls [-l | -s]\n");
        }
        else if (!strcmp(cmd.tabArgs[0], "cat")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : cat "UNDR"nom de fichier"DEF"\n");
            else cmd_cat(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "rm")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : rm "UNDR"nom de fichier"DEF"\n");
            else cmd_rm(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "cr")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : cr "UNDR"nom de fichier"DEF"\n");
            else cmd_cr(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "edit")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : edit "UNDR"nom de fichier"DEF"\n");
            else cmd_edit(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "load")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : load "UNDR"nom de fichier"DEF"\n");
            else cmd_load(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "store")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : store "UNDR"nom de fichier"DEF"\n");
            else cmd_store(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "chown")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"login autre utilisateur"DEF"\n");
            else {
                scanf("%s", cmd.tabArgs[2]);
                if (!strcmp(cmd.tabArgs[2], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"login autre utilisateur"DEF"\n");
                else cmd_chown(cmd.tabArgs[1], cmd.tabArgs[2]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "chmod")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"droit"DEF"\n");
            else {
                scanf("%s", cmd.tabArgs[2]);
                if (!strcmp(cmd.tabArgs[2], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"droit"DEF"\n");
                else cmd_chmod(cmd.tabArgs[1], cmd.tabArgs[2]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "listusers")){
            cmd_listusers();
        }
        else if (!strcmp(cmd.tabArgs[0], "quit")){
            cmd_quit();
            loop = 0;
        }
        else if (!strcmp(cmd.tabArgs[0], "adduser")){
            cmd_adduser();
        }
        else if (!strcmp(cmd.tabArgs[0], "rmuser")){
            scanf("%s", cmd.tabArgs[1]);
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : rmuser "UNDR"login"DEF"\n");
            else cmd_rmuser(cmd.tabArgs[1]);
        }
        else {
            printf(YELLOW"commande "BOLD"%s"DEF YELLOW"non reconnue\n"DEF, cmd.tabArgs[0]);
        }
    }

    return NO_ERROR;
}