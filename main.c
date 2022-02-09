#include "OS_DEFINES.h"

virtual_disk_t disk;

int main(int argc, char const *argv[]) {

  block_t block1,block2;
  disk.storage=fopen(argv[1],"wb+");
  fseek(disk.storage,49,SEEK_SET);
  convert_int_to_block(&block1,4096);
  write_block(&block1,49);
  read_block(&block2,49);
  print_block(&block2);
  read_inodes_table();
  fclose(disk.storage);
  return 0;
}