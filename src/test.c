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

	read_users_table();

  fclose(disk.storage);
  return 0;
}
