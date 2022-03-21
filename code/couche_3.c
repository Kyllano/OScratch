/*! \file couche_3.c
    \brief  fichier regroupant les fonctions de la couche 3
    \author Ali Cherif Keylan
    \date 8 février 2022
*/

#include "OS_DEFINES.h"

void init_users_table(){

    // Définition du login root
    strcpy(disk.users_table[ROOT_UID].login, "root");
    //Definition du mdp root
    char sha_mdp [SHA256_BLOCK_SIZE*2 + 1];
    sha256ofString((BYTE*)"root", sha_mdp);
    strcpy(disk.users_table[ROOT_UID].passwd, sha_mdp);
    disk.super_block.number_of_users = 1;

    write_users_table();

}


int read_users_table(){
    file_t passwd;
    if (read_file("passwd", &passwd) == ERROR_FILE_ACCESS) return ERROR_FILE_ACCESS;

    int i_fichier=0;
    int i_user = 0;
    while (i_fichier < passwd.size){
        char c = passwd.data[i_fichier];
        int i_username = 0;

        //lecture nom user
        while(c != '\t'){
            disk.users_table[i_user].login[i_username] = c;

            i_username++;
            i_fichier ++;
            c = passwd.data[i_fichier];
        }
        disk.users_table[i_user].login[i_username] = '\0';
        i_fichier ++;

        //lecture passwd
        c = passwd.data[i_fichier];
        int i_passwd = 0;
        while(c != '\n'){
            disk.users_table[i_user].passwd[i_passwd] = c;

            i_passwd++;
            i_fichier ++;
            c = passwd.data[i_fichier];
        }
        disk.users_table[i_user].passwd[i_passwd] = '\0';
        i_fichier ++;
        i_user ++;
    }
    disk.super_block.number_of_users = i_user;

    return NO_ERROR;
}

//Separation dans fichier passwd:
//nomuser \t sha password user \n
void write_users_table(){
    file_t fich_passwd;
    strcpy((char*) fich_passwd.data, "");

    for(int i=0;i<disk.super_block.number_of_users;i++){
        strcat((char*) fich_passwd.data, disk.users_table[i].login);
        strcat((char*) fich_passwd.data, "\t");
        strcat((char*) fich_passwd.data, disk.users_table[i].passwd);
        strcat((char*) fich_passwd.data, "\n\0");
    }
    fich_passwd.size = strlen((char*) fich_passwd.data);

    write_file("passwd", &fich_passwd);
    int file_passwd_id = get_file_id("passwd");
    disk.inodes[file_passwd_id].uid = 0;
    disk.inodes[file_passwd_id].uright = RW;
    disk.inodes[file_passwd_id].oright = RW;
}

//Keylan
int get_user_id(char* user_login){
    int id = ERROR_INEXISTANT_USER;
    for (int i =0; i < disk.super_block.number_of_users; i++){
        if ( ! strcmp(disk.users_table[i].login, user_login)) id = i;
    }
    return id;
}

int add_user(char* username, char* password){
    if (disk.super_block.number_of_users >= NB_USERS) return ERROR_TOO_MANY_USER;
    if (get_user_id(username) != ERROR_INEXISTANT_USER) return ERROR_USER_ALREADY_EXIST;

    strcpy(disk.users_table[disk.super_block.number_of_users].login, username);

    char sha_mdp [SHA256_BLOCK_SIZE*2 + 1];
    sha256ofString((BYTE*) password, sha_mdp);
    strcpy(disk.users_table[disk.super_block.number_of_users].passwd, sha_mdp);

    disk.super_block.number_of_users ++;

    write_users_table();

    return NO_ERROR;
}


int remove_user(char* username){
    if (disk.super_block.number_of_users == 1){
        printf("cannot remove root or user not existent\n");
        return ERROR_NOT_ENOUGH_RIGHTS;
    }

    int uid_to_delete = get_user_id(username);
    if (uid_to_delete == ERROR_INEXISTANT_USER) return ERROR_INEXISTANT_USER;

    for (int i=uid_to_delete; i < disk.super_block.number_of_users-1; i++){
        strcpy(disk.users_table[i].login, disk.users_table[i+1].login);
        strcpy(disk.users_table[i].passwd, disk.users_table[i+1].passwd);
    }

    disk.super_block.number_of_users --;

    write_users_table();
    return NO_ERROR;
}
