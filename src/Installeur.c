#include "OS_DEFINES.h"

// create a file named di (i = diskid) in directory dirname of size bytes
// the file is initialized with 0
// dirname must be a valid directory
// 0 <= diskid < 10
void format(char *dirname, int size, int diskid){
  char filename[strlen(dirname)+4];
  snprintf(filename, strlen(dirname)+4, "%s/d%d", dirname, diskid);
  printf("%s\n", filename);
  FILE *fp = fopen(filename, "w+");
  assert(fp!=NULL);
  unsigned char zero=0;
  for(int i=0; i<size; i++) {
    int nb_write = fwrite(&zero, 1, 1, fp);
    assert(nb_write == 1);
  }
  fclose(fp);
}

int main(int argc, char **argv) {
/// \brief command nom_repertoire taille_fichier (octets)
    if (argc!=3) {
        printf("usage %s  existing_dir_to_store_disk disk_size\n", argv[0]);
        return 0;
    }
    int size = atoi(argv[2]);
    if(argc==3) {
      int diskid = 0;
	    format(argv[1], size, diskid);
    }



    if (init_disk_sos(argv[0])){
      return ERROR_FILE_ACCESS;
    }

    update_first_free_byte();
    init_user_table();

    if (!write_super_block()){
      write_inodes_table();
      return NO_ERROR;
    }

    return ERROR_FILE_ACCESS;


}
