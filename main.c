#include "OS_DEFINES.h"

virtual_disk_t disk;

int main(int argc, char const *argv[]) {

    block_t bloc;
    int beez=1025;
    disk.storage=fopen(argv[1],"wb+");
    write_int(beez,105);
    read_block(&bloc,105);
    print_block(&bloc);
    fclose(disk.storage);
    return 0;
}