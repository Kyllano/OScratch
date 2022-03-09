/*! \file OS_DEFINES.h
    \brief  fichier global regroupant les définitions
    \author CHEVALLIER Guilhem, ALI-CHERIF Keylan, JUAN Victor
    \date 7 mars 2022
*/

#ifndef OS_DEFINES
#define OS_DEFINES





/*------------------------------------------------------------
  INCLUDES
------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "timestamp.h"
#include "formatting.h"





/*------------------------------------------------------------
  DEFINES
------------------------------------------------------------*/

// pour les droits : minuscule = pas le droit, majuscule = droit ok
#define rw 0 // 00
#define rW 1 // 01
#define Rw 2 // 10
#define RW 3 // 11
#define ROOT_UID 0

#define FILENAME_MAX_SIZE 32
#define MAX_FILE_SIZE (2*1024)
#define INODE_TABLE_SIZE 10
#define MAX_MSG 1024
#define TIMESTAMP_SIZE 24+2
#define NB_USERS 5
#define CMDLINE_MAX_SIZE 128
#define ARG_MAX_SIZE 32

#define BLOCK_SIZE 4
#define SUPER_BLOCK_SIZE 4
#define INODES_START SUPER_BLOCK_SIZE*BLOCK_SIZE+1
#define INODE_SIZE FILENAME_MAX_SIZE/BLOCK_SIZE+6+(TIMESTAMP_SIZE*2)/BLOCK_SIZE

#define NO_ERROR			0
#define ERROR_FILE_ACCESS	1
#define ERROR_RIGHTS		2
#define ERROR_INODES_FULL	3
#define ERROR_FILE_TOO_BIG	4
#define ERROR_DISK_FULL		5
#define ERROR_ARGS			6
#define ERROR_MALLOC		7





/*------------------------------------------------------------
  TYPES
------------------------------------------------------------*/

typedef unsigned int uint; // même taille que int
typedef unsigned char uchar; // 8 bits non signés = octet

typedef struct user_s{
	char login[FILENAME_MAX_SIZE];
	char passwd[SHA256_BLOCK_SIZE*2 + 1];
} user_t;

typedef struct session_s{
	int userid;
} session_t;

typedef struct block_s{
	uchar data[BLOCK_SIZE];
} block_t;

typedef struct inode_s{
	// type file vs dir
	char filename[FILENAME_MAX_SIZE]; // dont '\0'
	uint size; // du fichier en octets
	uint uid; //user id proprio
	uint uright; //owner's rights between 0 and 3 coding rw in binary
	uint oright; // other's right idem
	char ctimestamp[TIMESTAMP_SIZE]; // date creation : 26 octets
	char mtimestamp[TIMESTAMP_SIZE]; // date dernière modif. : 26 octets
	uint nblock; // nblock du fichier = (size+BLOCK_SIZE-1)/BLOCK_SIZE ?
	uint first_byte; // number of the first byte on the virtual disk
} inode_t;

typedef inode_t inode_table_t[INODE_TABLE_SIZE];
typedef user_t users_table_t[NB_USERS];

typedef struct super_block_s{
	uint number_of_files;
	uint number_of_users;
	uint nb_blocks_used ;
	uint first_free_byte;
} super_block_t;

typedef struct virtual_disk_s {
	super_block_t super_block;
	users_table_t users_table;
	inode_table_t inodes;
	FILE *storage;
} virtual_disk_t;

typedef struct file_s{
uint size;
uchar data [MAX_FILE_SIZE] ;
} file_t ;

typedef struct cmd_s{
	char ** tabArgs;
	int nbArgs;
} cmd_t;





/*------------------------------------------------------------
  FONCTIONS COUCHE 1
------------------------------------------------------------*/

void print_block(block_t *bloc);
uint compute_nblock(int nb_bytes);
void write_block(block_t *bloc, uint pos);
void read_block(block_t *bloc, uint pos);
void shutoff_save();
void convert_int_to_block(block_t* block,uint nombre);
void convert_block_to_int(block_t block,uint *nombre);
void gestion_ouverture(FILE *f,char* path);
void init_disk_sos(char* path);

/*------------------------------------------------------------
  FONCTIONS COUCHE 2
------------------------------------------------------------*/

void read_int_block(block_t block, uint *pos, uint *buff);
void write_int_block(block_t block, uint *pos, uint *buff);
void read_mult_blocks(char *buff, int taille_totale, uint *pos);
void write_mult_blocks(char *buff,int taille_totale, uint *pos);
void read_inodes_table();
void write_inodes_table();
void clear_inode(int indice);
void delete_inode(int indice);
void init_inode(char* filename, uint size, uint pos);
int get_unused_inode();
void write_super_block();
void read_super_block();

/*------------------------------------------------------------
  FONCTIONS COUCHE 3
------------------------------------------------------------*/

void init_users_table();
void read_users_table();
void write_users_table();

/*------------------------------------------------------------
  FONCTIONS COUCHE 4
------------------------------------------------------------*/

int delete_file(char* filename);
int write_file(char *filename, file_t *fich);
int read_file(char* filename, file_t* file);
int load_file_from_host(char* filename_on_host, file_t* empty_file);
int store_file_to_host(char* filename);

int get_file_id(char* filename);
void write_content(char *filename,file_t *fich);
void overwrite_content(char *filename, file_t *fich, int i_fich);
void update_first_free_byte();

/*------------------------------------------------------------
  FONCTIONS COUCHE 5
------------------------------------------------------------*/

int cmd_ls();
int cmd_cat();
int cmd_rm();
int cmd_cr();
int cmd_edit();
int cmd_load();
int cmd_store();
int cmd_chown();
int cmd_chmod();
int cmd_listusers();
int cmd_quit();
int cmd_adduser();
int cmd_rmuser();

void flush();

/*------------------------------------------------------------
  VARIABLES GLOBALES
------------------------------------------------------------*/

virtual_disk_t disk;  // la variable globale de disk







#endif // OS_DEFINES
