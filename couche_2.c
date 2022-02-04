#include "OS_DEFINES.h"


void write_super_block(){
    write_block(disk->super_block.number_of_files, 0);
    write_block(disk->super_block.number_of_users, 1);
    write_block(disk->super_block.nb_blocks_used , 2);
    write_block(disk->super_block.first_free_byte, 3);
}

void read_super