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

    	disk.storage = fopen(argv[1], "rb+");
	if (disk.storage == NULL){
		return ERROR_FILE_ACCESS;
	}

    char cmdline[CMDLINE_MAX_SIZE];
    char* strToken;
    cmd_t cmd;
    cmd.tabArgs = (char**) malloc (3*ARG_MAX_SIZE*sizeof(char*));
    cmd.tabArgs[0] = (char*) malloc (ARG_MAX_SIZE*sizeof(char));
    cmd.tabArgs[1] = (char*) malloc (ARG_MAX_SIZE*sizeof(char));
    cmd.tabArgs[2] = (char*) malloc (ARG_MAX_SIZE*sizeof(char));
    int loop = 1;
    int retour;

    // Tests
    user.userid = 0; 

    clear_screen();

    while (loop){

        // Lecture de la cmd.tabArgs[0]e
        printf(BLUE BOLD"► "DEF BLUE);
        fgets(cmdline, CMDLINE_MAX_SIZE, stdin);
        printf(DEF);
        cmdline[strlen(cmdline)-1] = '\0';
        
        //printf(PURPLE"%s\n"DEF, cmdline);

        cmd.nbArgs = 0;
        strToken = strtok(cmdline, " ");

        while (strToken!=NULL){

            if (strlen(strToken)>ARG_MAX_SIZE){
                while (strToken!=NULL) strToken = strtok(NULL, " ");
                printf(RED"Erreur : Un argument dépasse la taille maximale autorisée.\n"DEF);
                strcpy(cmd.tabArgs[0], "");
            }

            else{
                cmd.tabArgs = (char**) realloc (cmd.tabArgs, (1+cmd.nbArgs)*sizeof(char*));
                cmd.tabArgs[cmd.nbArgs] = (char*) realloc (cmd.tabArgs[cmd.nbArgs], (ARG_MAX_SIZE*sizeof(char))); 

                if (cmd.tabArgs[cmd.nbArgs] == NULL){
                    printf(RED"Erreur d'allocation mémoire.\n"DEF);
                    return ERROR_MALLOC;
                }

                strcpy(cmd.tabArgs[cmd.nbArgs], strToken);
                cmd.nbArgs++;
                strToken = strtok(NULL, " ");
            }
        }

        // Interprétation puis vérification et exécution
        if (!strcmp(cmd.tabArgs[0], "ls")){
            if (!strcmp(cmd.tabArgs[1],"")) retour = cmd_ls(0);
            else if (!strcmp(cmd.tabArgs[1], "-s")) retour = cmd_ls(1);
            else if (!strcmp(cmd.tabArgs[1], "-l")) retour = cmd_ls(2);
            else printf(YELLOW"usage : ls [-l | -s]\n");
        }
        else if (!strcmp(cmd.tabArgs[0], "cat")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : cat "UNDR"nom de fichier"DEF"\n");
            else retour = cmd_cat(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "rm")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : rm "UNDR"nom de fichier"DEF"\n");
            else {
                retour = cmd_rm(cmd.tabArgs[1]);
                if (retour == NO_ERROR) printf("Le fichier %s a été supprimé avec succès.\n", cmd.tabArgs[1]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "cr")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : cr "UNDR"nom de fichier"DEF"\n");
            else {
                retour = cmd_cr(cmd.tabArgs[1]);
                if (retour == NO_ERROR) printf("Le fichier %s a été créé avec succès.\n", cmd.tabArgs[1]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "edit")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : edit "UNDR"nom de fichier"DEF"\n");
            else retour = cmd_edit(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "load")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : load "UNDR"nom de fichier"DEF"\n");
            else {
                retour = cmd_load(cmd.tabArgs[1]);
                if (retour == NO_ERROR) printf("Le fichier %s a été chargé avec succès.\n", cmd.tabArgs[1]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "store")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : store "UNDR"nom de fichier"DEF"\n");
            else {
                retour = cmd_store(cmd.tabArgs[1]);
                if (retour == NO_ERROR) printf("Le fichier %s a été enregistré avec succès.\n", cmd.tabArgs[1]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "chown")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"login autre utilisateur"DEF"\n");
            else {
                scanf("%s", cmd.tabArgs[2]);
                if (!strcmp(cmd.tabArgs[2], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"login autre utilisateur"DEF"\n");
                else retour = cmd_chown(cmd.tabArgs[1], cmd.tabArgs[2]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "chmod")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"droit"DEF"\n");
            else {
                if (!strcmp(cmd.tabArgs[2], "")) printf(YELLOW"usage : chown "UNDR"nom de fichier"DEF" "UNDR YELLOW"droit"DEF"\n");
                else retour = cmd_chmod(cmd.tabArgs[1], cmd.tabArgs[2]);
            }
        }
        else if (!strcmp(cmd.tabArgs[0], "listusers")){
            cmd_listusers();
        }
        else if (!strcmp(cmd.tabArgs[0], "quit")){
            retour = cmd_quit();
            loop = 0;
        }
        else if (!strcmp(cmd.tabArgs[0], "adduser")){
            retour = cmd_adduser();
        }
        else if (!strcmp(cmd.tabArgs[0], "rmuser")){
            if (!strcmp(cmd.tabArgs[1], "")) printf(YELLOW"usage : rmuser "UNDR"login"DEF"\n");
            else retour = cmd_rmuser(cmd.tabArgs[1]);
        }
        else if (!strcmp(cmd.tabArgs[0], "help")){
            printf(
                    WHITE BOLD "\t\t- COMMANDES -\n\n"DEF
                    WHITE BOLD "cat "UNDR"nom de fichier"DEF"\n\tAffiche à l’écran le contenu d’un fichier si l’utilisateur a les droits.\n\n"
                    WHITE BOLD "rm "UNDR"nom de fichier"DEF"\n\tSupprime un fichier du système si l’utilisateur a les droits.\n\n"
                    WHITE BOLD "cr "UNDR"nom de fichier"DEF"\n\tCrée un nouveau fichier sur le système, le propriétaire est l’utilisateur.\n\n"
                    WHITE BOLD "edit "UNDR"nom de fichier"DEF"\n\tÉdite un fichier pour modifier son contenu si l’utilisateur a les droits.\n\n"
                    WHITE BOLD "load "UNDR"nom de fichier"DEF"\n\tCopie le contenu d’un fichier du système ”hôte” sur le système avec le même nom (assimilé à une création).\n\n"
                    WHITE BOLD "store "UNDR"nom de fichier"DEF"\n\tCopie le contenu d’un fichier du système sur ”hôte” avec le même nom.\n\n"
                    WHITE BOLD "chown "UNDR"nom de fichier"DEF" "WHITE BOLD UNDR"login autre utilisateur"DEF"\n\tchange le propriétaire d’un fichier si le demandeur a les droits.\n\n"
                    WHITE BOLD "chmod "UNDR"nom de fichier"DEF" "WHITE BOLD UNDR"droit"DEF"\n\tchange les droits d’un fichier pour tous les autres utilisateurs si le demandeur a les droits.\n\n"
                    WHITE BOLD "listusers"DEF"\n\tAffiche la liste des utilisateurs.\n\n"
                    WHITE BOLD "quit"DEF"\n\tSort de l’interprète de commande et du programme en sauvegardant le système de fichiers sur le disque.\n\n"
                    WHITE BOLD "adduser"DEF"\n\tAjoute un utilisateur.\n\n"
                    WHITE BOLD "rmuser "UNDR"login"DEF"\n\tSupprime un utilisateur.\n\n"
                );
        }
        else if (!strcmp(cmd.tabArgs[0], "")){}
        else {
            printf(YELLOW"commande non reconnue\n"DEF);
        }





        // Messages d'erreur
        error_message(retour);
        retour = NO_ERROR;




        // Nettoyage
        for (int i=0; i<3; i++){
            strcpy(cmd.tabArgs[i], "");
        }

    }

    return NO_ERROR;
}
