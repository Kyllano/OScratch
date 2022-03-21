#include "OS_DEFINES.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("ptdr");

	user.userid = 0;


	if (init_disk_sos("d0")){
		return ERROR_FILE_ACCESS;
	}

	if (!read_super_block()){
		read_inodes_table();
	}
	update_first_free_byte();


	init_users_table();

	add_user("jean", "prout");
	add_user("mec", "t moche");
	add_user("mais", "euh");
	add_user("j", "pp");
	add_user("lol", "chirac");

	cmd_cat("passwd");

	printf("\n\nON MESS UP LA VARIABLE\n");
	disk.super_block.number_of_users = 1;
	strcpy(disk.users_table[0].login, "portefeuille");
	strcpy(disk.users_table[1].login, "jaan marie");

	read_users_table();

	for (int i=0; i < disk.super_block.number_of_users; i++){
		printf("user : %s\nmdp : %s\nid: %d\n", disk.users_table[i].login, disk.users_table[i].passwd, i);
	}

	printf("\n\nON DELETE J et MEC\n\n");

	printf("CAT PRIMITIF\n\n");
	cmd_cat("passwd");

	remove_user("mec");
	printf("CAT\n");
	cmd_cat("passwd");
	remove_user("j");

	for (int i=0; i < disk.super_block.number_of_users; i++){
		printf("user : %s\nmdp : %s\nid: %d\n", disk.users_table[i].login, disk.users_table[i].passwd, i);
	}

	printf("ON CAT\n\n\n");
	cmd_cat("passwd");
	printf("\n\n");

	read_users_table();

	for (int i=0; i < disk.super_block.number_of_users; i++){
		printf("user : %s\nmdp : %s\nid: %d\n", disk.users_table[i].login, disk.users_table[i].passwd, i);
	}

  fclose(disk.storage);
  return 0;
}
