#include "OS_DEFINES.h"

virtual_disk_t disk;

int main(int argc, char const *argv[]) {
    init_disk_sos("./d0");
	
	//disk.super_block.first_free_byte = 16;
	//disk.super_block.nb_blocks_used = 4;
	//write_super_block();
	disk.super_block.first_free_byte = 77;
	disk.super_block.nb_blocks_used = 88;

    read_super_block();
	//printf("%d\n%d\n%d\n%d\n", disk.super_block.number_of_users, disk.super_block.number_of_files, disk.super_block.nb_blocks_used, disk.super_block.first_free_byte);
	
  	return 0;
}