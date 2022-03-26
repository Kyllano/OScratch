/*! \file couche_5.c
	\brief  fichier regroupant les fonctions de la couche 5
	\author JUAN Victor, CHEVALLIER Guilhem, ALI-CHERIF Keylan
	\date 7 mars 2022
*/

#include "OS_DEFINES.h"

// Victor
int cmd_ls(int type){

	printf(BOLD WHITE"filename                        "DEF);
	if (type != 1) {	// Not Short
		printf(" │ "BOLD WHITE"size    "DEF);
		printf(" │ "BOLD WHITE"date de création        "DEF);
	}
	if (type ==2){		// Long
		printf(" │ "BOLD WHITE"date de modification    "DEF);
		printf(" │ "BOLD WHITE"owner id"DEF);
	}
	printf("\n");


	//printf("nb_file = %d\n",disk.super_block.number_of_files);

	for (int i=0; i<disk.super_block.number_of_files; i++){
		printf("%-32s", disk.inodes[i].filename);
		if (type != 1) {	// Not Short
			printf(" │ %8d", disk.inodes[i].size);
			printf(" │ %s", disk.inodes[i].ctimestamp);
		}
		if (type ==2){	// Long
			printf(" │ %s", disk.inodes[i].mtimestamp);
			printf(" │ %8d", disk.inodes[i].uid);
		}
		printf("\n");
	}

	return NO_ERROR;
}

// Victor
int cmd_cat(char* filename){

	file_t file;
	int retour = read_file(filename, &file);
	if (retour != NO_ERROR) return retour;

	printf("%s\n", file.data);

	return NO_ERROR;
}

// Guilhem
int cmd_rm(char *filename){
	int i;
	if ((i=get_file_id(filename)) == -1){
		return ERROR_FILE_ACCESS;
	}
	if (user.userid!=0 && ((disk.inodes[i].uid==user.userid && disk.inodes[i].uright!=rW && disk.inodes[i].uright!=RW)
	|| (disk.inodes[i].uid!=user.userid && disk.inodes[i].oright!=rW && disk.inodes[i].oright!=RW))){
		return ERROR_RIGHTS;
	}
	return delete_file(filename);
}

// Guilhem
int cmd_cr(char *filename){
	int unused_inode;
	if ((unused_inode = get_unused_inode()) == -1) return ERROR_DISK_FULL;

	if (get_file_id(filename)!=-1) return ERROR_FILENAME_TAKEN;

	init_inode(filename,1, disk.super_block.first_free_byte);
	strcpy(disk.inodes[unused_inode].ctimestamp, timestamp());
	strcpy(disk.inodes[unused_inode].mtimestamp, disk.inodes[unused_inode].ctimestamp);
	disk.inodes[unused_inode].nblock = 1;
	disk.inodes[unused_inode].uid = user.userid;
	disk.inodes[unused_inode].uright = rw;
	disk.inodes[unused_inode].oright = rw;
	update_first_free_byte();
	//printf("%d\n",disk.super_block.first_free_byte);
	disk.super_block.number_of_files ++;

	return NO_ERROR;
}

// Guilhem
int cmd_edit(char *filename){
	int i;
	file_t file;
	char c;
	if ((i=get_file_id(filename))==-1) return ERROR_FILE_ACCESS;

	if(user.userid!=0  && ((disk.inodes[i].uid==user.userid && disk.inodes[i].uright!=Rw && disk.inodes[i].uright!=RW)
	|| (disk.inodes[i].uid!=user.userid && disk.inodes[i].oright!=Rw && disk.inodes[i].oright!=RW))){
		return ERROR_RIGHTS;
	}

	printf("Entrez le contenu du fichier (terminez la saisie avec $)\n");
	file.size=0;
	while ((c=fgetc(stdin))!='$' && file.size!=MAX_FILE_SIZE){
		file.data[file.size++] = c;
	}
	flush();
	return write_file(filename, &file);
}

// Guilhem
int cmd_load(char *filename){
	file_t file;
	return load_file_from_host(filename, &file);
}

// Guihem
int cmd_store(char *filename){
	return store_file_to_host(filename);
}

// Keylan
//On considere que si l user a les droits d ecriture et n est pas le proprio, il peut changer le proprio du fichier
int cmd_chown(char* filename, char* name_owner){
	int id_fich;
	int id_new_owner;
	if ((id_fich=get_file_id(filename))==-1) return ERROR_FILE_ACCESS;

	printf("PTDR\n");
	printf("%s\n%s\n", filename, name_owner);
	if(user.userid!=0  && ((disk.inodes[id_fich].uid!=user.userid && (disk.inodes[id_fich].oright==Rw || disk.inodes[id_fich].oright==rw))
	|| (disk.inodes[id_fich].uid==user.userid && (disk.inodes[id_fich].uright==Rw || disk.inodes[id_fich].uright==rw)))){
		return ERROR_RIGHTS;
	}

	if ((id_new_owner = get_user_id(name_owner)) == ERROR_USER_NOT_FOUND) return ERROR_USER_NOT_FOUND;

	disk.inodes[id_fich].uid = id_new_owner;
	return NO_ERROR;

}

// Keylan
//On considere que si l user a les droits d ecriture et n est pas le proprio, il peut changer les droits du fichier
int cmd_chmod(char* filename, char* uright, char* oright){
	int id_fich;
	if ((id_fich=get_file_id(filename))==-1) return ERROR_FILE_ACCESS;

//probablement faux, a changer
	if(user.userid!=0  && ((disk.inodes[id_fich].uid==user.userid)
	|| (disk.inodes[id_fich].uid!=user.userid && disk.inodes[id_fich].oright!=Rw && disk.inodes[id_fich].oright!=RW))){
		return ERROR_RIGHTS;
	}

	if 		(strcmp(uright, "rw"))	disk.inodes[id_fich].uright = rw;
	else if (strcmp(uright, "Rw"))	disk.inodes[id_fich].uright = Rw;
	else if (strcmp(uright, "rW"))	disk.inodes[id_fich].uright = rW;
	else if (strcmp(uright, "RW"))	disk.inodes[id_fich].uright = RW;
	else							printf("Droits user non reconnu\n");

	if 		(strcmp(oright, "rw"))	disk.inodes[id_fich].oright = rw;
	else if (strcmp(oright, "Rw"))	disk.inodes[id_fich].oright = Rw;
	else if (strcmp(oright, "rW"))	disk.inodes[id_fich].oright = rW;
	else if (strcmp(oright, "RW"))	disk.inodes[id_fich].oright = RW;
	else							printf("Droits autres non reconnu\n");

	printf("changement des droits effectués\n");
	return NO_ERROR;
}

// Keylan
int cmd_listusers(){
	read_users_table();

	printf(BOLD WHITE"Liste des utilisateurs :\n"DEF);
	for (int i=0; i<disk.super_block.number_of_users; i++){
		if (i == user.userid){
			printf(BOLD GREEN "%s\n" DEF, disk.users_table[i].login );
		}
		else{
			printf("%s\n", disk.users_table[i].login );
		}
	}
	return NO_ERROR;
}

// Victor
int cmd_quit(){
	printf("Sauvegarde des données...\n");
	if (shutoff_save()){
		return ERROR_FILE_ACCESS;
	}
	printf("Arrêt du programme.\n");
	return NO_ERROR;
}

// Keylan
int cmd_adduser(){
	read_users_table();
	if (disk.super_block.number_of_users == NB_USERS) return ERROR_TOO_MANY_USERS;

	printf("Nom du nouvel utilisateur : ");
	char username [CMDLINE_MAX_SIZE];
	fgets(username, CMDLINE_MAX_SIZE, stdin);
	username[strlen(username) -1] = '\0';

	printf("Mot de passe du nouvel utilisateur : ");
	char password [CMDLINE_MAX_SIZE];
	fgets(password, CMDLINE_MAX_SIZE, stdin);
	password[strlen(password) -1] = '\0';

	int retour = add_user(username, password);

	if (retour == NO_ERROR) printf("Utilisateur créé\n");
	return retour;
}

// Keylan
int cmd_rmuser(char* username){
	char password [CMDLINE_MAX_SIZE];
	char sha_mdp[SHA256_BLOCK_SIZE*2 + 1];
	int id_user_to_del;

	if ((id_user_to_del = get_user_id(username)) == ERROR_USER_NOT_FOUND) return ERROR_USER_NOT_FOUND;
	if (user.userid != id_user_to_del && user.userid != ROOT_UID){
		printf("Entrez le mot de passe de %s : ", username);
		fgets(password, CMDLINE_MAX_SIZE, stdin);
		password[strlen(password) -1] = '\0';

		sha256ofString((BYTE*)password, sha_mdp);
    	if (strcmp(disk.users_table[id_user_to_del].passwd, sha_mdp)) return ERROR_PASSWORD;
	}

	remove_user(username);
	printf("Utilisateur %s supprimé\n", username);
	return NO_ERROR;
}

// Guilhem
int cmd_su(char *username){
    char password [CMDLINE_MAX_SIZE];
	char sha_mdp[SHA256_BLOCK_SIZE*2 + 1];
    int id;

	id = get_user_id(username);
    if (id == ERROR_USER_NOT_FOUND) return ERROR_USER_NOT_FOUND;

	if (user.userid != ROOT_UID){
		printf("Entrez le mot de passe de l'utilisateur :\n");
		fgets(password, CMDLINE_MAX_SIZE, stdin);
		password[strlen(password) -1] = '\0';

		sha256ofString((BYTE*)password, sha_mdp);
		if (strcmp(disk.users_table[id].passwd, sha_mdp)) return ERROR_PASSWORD;
	}


	printf("Changement d'utilisateur de %s vers %s\n", disk.users_table[user.userid].login, username);
    user.userid=id;
    return NO_ERROR;
}

// Victor
int cmd_whoami(){
	printf("%s\n", disk.users_table[user.userid].login);
	return NO_ERROR;
}

// Victor
int cmd_help(){
	printf(
		WHITE BOLD "\t\t- COMMANDES -\n\n"DEF
		WHITE BOLD "adduser"DEF"\n\tAjoute un utilisateur.\n\n"
		WHITE BOLD "cat "UNDR"nom de fichier"DEF"\n\tAffiche à l’écran le contenu d’un fichier si l’utilisateur a les droits.\n\n"
		ITAL"(à venir) "WHITE BOLD "chown "UNDR"nom de fichier"DEF" "WHITE BOLD UNDR"login autre utilisateur"DEF"\n\tchange le propriétaire d’un fichier si le demandeur a les droits.\n\n"
		ITAL"(à venir) "WHITE BOLD "chmod "UNDR"nom de fichier"DEF" "WHITE BOLD UNDR"droit"DEF"\n\tchange les droits d’un fichier pour tous les autres utilisateurs si le demandeur a les droits.\n\n"
		WHITE BOLD "clear "DEF"\n\tVide l'affichage\n\n"
		WHITE BOLD "cr "UNDR"nom de fichier"DEF"\n\tCrée un nouveau fichier sur le système, le propriétaire est l’utilisateur.\n\n"
		WHITE BOLD "edit "UNDR"nom de fichier"DEF"\n\tÉdite un fichier pour modifier son contenu si l’utilisateur a les droits.\n\n"
		WHITE BOLD "listusers"DEF"\n\tAffiche la liste des utilisateurs.\n\n"
		WHITE BOLD "load "UNDR"nom de fichier"DEF"\n\tCopie le contenu d’un fichier du système ”hôte” sur le système avec le même nom (assimilé à une création).\n\n"
		WHITE BOLD "ls [-l | -s]"DEF"\n\tAffiche la liste des fichiers du disque.\n\n"
		WHITE BOLD "quit"DEF"\n\tSort de l’interprète de commande et du programme en sauvegardant le système de fichiers sur le disque.\n\n"
		WHITE BOLD "rm "UNDR"nom de fichier"DEF"\n\tSupprime un fichier du système si l’utilisateur a les droits.\n\n"
		ITAL"(à venir) "WHITE BOLD "rmuser "UNDR"login"DEF"\n\tSupprime un utilisateur.\n\n"
		WHITE BOLD "store "UNDR"nom de fichier"DEF"\n\tCopie le contenu d’un fichier du système sur ”hôte” avec le même nom.\n\n"
		WHITE BOLD "su "UNDR"nom d'utilisateur"DEF"\n\tChange d'utilisateur.\n\n"
		WHITE BOLD "whoami"DEF"\n\tAffiche le nom de l'utilisateur courant.\n\n"
	);
	return NO_ERROR;
}





// Victor
void clear_screen(){
	printf("\e[1;1H\e[2J");
}

// Victor
void flush(){
    int c;
    do {
        c=getchar();
    } while (c!='\n' && c!=EOF);
}

// Victor
void error_message(int i){
	printf(RED);

	switch (i){
		case NO_ERROR:
			break;

		case ERROR_FILE_ACCESS:
			printf("Erreur d'accès au fichier.\n");
			break;

		case ERROR_RIGHTS:
			printf("Erreur : Vous n'avez pas les droits nécessaires.\n");
			break;

		case ERROR_INODES_FULL:
			printf("Erreur : la table d'inodes est pleine.\n");
			break;

		case ERROR_FILE_TOO_BIG:
			printf(YELLOW"Attention : Le fichier est trop volumineux. Il a été tronqué.\n");
			break;

		case ERROR_DISK_FULL:
			printf("Erreur : Il n'y a plus de d'espace disque disponible.\n");
			break;

		case ERROR_ARGS:
			printf("Erreur d'arguments.\n");
			break;

		case ERROR_MALLOC:
			printf("Erreur d'allocation mémoire.\n");
			break;

		case ERROR_FILENAME_TAKEN:
			printf("Erreur : Le fichier existe déjà.\n");
			break;

		case ERROR_USER_NOT_OWNER:
			printf("Erreur : Cet utilisateur n'est pas le propriétaire du fichier.\n");
			break;

		case ERROR_USER_NOT_FOUND:
			printf("Erreur : Cet utilisateur n'existe pas.\n");
			break;

		case ERROR_TOO_MANY_USERS:
			printf("Erreur : Le nombre d'utilisateurs maximal est déjà atteint.\n");
			break;

		case ERROR_USERNAME_TAKEN:
			printf("Erreur : Ce nom d'utilisateur est déjà pris.\n");
			break;
		
		case ERROR_PASSWORD:
			printf("Erreur : le mot de passe est erroné.\n");
			break;
	}

	printf(DEF);
}