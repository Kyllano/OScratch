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

	if(get_file_id(filename)!=-1) return ERROR_FILENAME_TAKEN;

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
int cmd_chown(char* filename, char* name_owner){

}

// Keylan
int cmd_chmod(){

}

// Keylan
int cmd_listusers(){
	read_users_table();

	printf(BOLD WHITE"Liste des utilisateurs :\n"DEF);
	for (int i=0; i<disk.super_block.number_of_users; i++){
		printf("%s\n", disk.users_table[i].login );
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
int cmd_rmuser(){

}

int cmd_su(char *username){
    char password [CMDLINE_MAX_SIZE];
    int id;

    printf("entrez le login de l'utilisateur :\n");
    fgets(password, CMDLINE_MAX_SIZE, stdin);
    password[strlen(password) -1] = '\0';
    
	id = get_user_id(username);
    if (id== ERROR_USER_NOT_FOUND) return ERROR_USER_NOT_FOUND;
    if (strcmp(disk.users_table[id].passwd, password)) return ERROR_PASSWORD;

    user.userid=id;    
    return NO_ERROR;
}

// Keylan
int cmd_whoami(){
	
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
			break;
	}

	printf(DEF);
}