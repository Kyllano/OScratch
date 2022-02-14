#include "OS_DEFINES.h"

int main(int argc, char const *argv[]) {

  block_t block1,block2;
  
  init_disk_sos("./d0");
  printf("ici ?\n");
  fseek(disk.storage,49,SEEK_SET);
  printf("non.\n");
  convert_int_to_block(&block1,4096);
  write_block(&block1,49);
  read_block(&block2,49);
  print_block(&block2);
  read_inodes_table();
  fclose(disk.storage);
  return 0;
}