#include "OS_DEFINES.h"
#include <unistd.h>

int main(int argc, char const *argv[]) {

  block_t block1,block2;file_t loul;
  char filename[FILENAME_MAX_SIZE];
  init_disk_sos("./d0");

  disk.storage=fopen(argv[1],"rb+");
  printf("ici ?\n");
  fseek(disk.storage,49,SEEK_SET);
  printf("non.\n");
  convert_int_to_block(&block1,4096);
  write_block(&block1,49);
  read_block(&block2,49);
  print_block(&block2);
  fseek(disk.storage,0,SEEK_SET);


  printf("écriture du super_block\n");
  write_super_block();
  printf("pos = %ld\n",ftell(disk.storage));
  read_super_block();
  printf("update de free_byte\n");
  update_first_free_byte();
  strcpy(filename,"suisse");


  printf("première inode:\n");
  init_inode(filename,200,disk.super_block.first_free_byte);
  disk.super_block.number_of_files ++;
  strcpy(filename,"merde");
  update_first_free_byte();


  printf("seconde inode:\n");
  init_inode(filename,200,disk.super_block.first_free_byte);
  disk.super_block.number_of_files ++;
  strcpy(filename,"miasme");
  update_first_free_byte();


  printf("troisième inode:\n");
  init_inode(filename,200,disk.super_block.first_free_byte);
  disk.super_block.number_of_files ++;
  update_first_free_byte();
  printf("écriture du super block:\n");
  write_super_block();
  read_super_block();

  printf("get_unused_inode = %d\n",get_unused_inode());
  printf("écriture de la table d'inode:\n");
  write_inodes_table();
  printf("suppression de la deuxième inode:\n");
  delete_inode(1);
  printf("get_unused_inode = %d\n",get_unused_inode());
  write_super_block();
  read_super_block();


  printf("code erreur load = %d\n",load_file_from_host("miam.txt",&loul));
  printf("%s\n",loul.data);
  printf("get_unused_inode = %d\n",get_unused_inode());
  sleep(10);
  write_super_block();
  read_super_block();
  write_inodes_table();

  remove("miam.txt");
  printf("code erreur store = %d\n",store_file_to_host("miam.txt"));







  fclose(disk.storage);
  return 0;
}
