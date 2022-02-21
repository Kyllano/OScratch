/*! \file OS_DEFINES.h
    \brief  fichier global regroupant les définitions
    \author CHEVALLIER Guilhem, ALI-CHERIF Keylan, JUAN Victor
    \date 4 février 2022
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










/*------------------------------------------------------------
  DEFINES
------------------------------------------------------------*/

/*! \def    rw
    \brief  aucun droits

    \def    rW
    \brief  droit d'écriture seulement

    \def    Rw
    \brief  droit de lecture seulement

    \def    RW
    \brief  tous les droits

    \def    ROOT_UID
    \brief  uid de Root
*/
// pour les droits : minuscule = pas le droit, majuscule = droit ok
#define rw 0 // 00
#define rW 1 // 01
#define Rw 2 // 10
#define RW 3 // 11
#define ROOT_UID 0

/*! \def    FILENAME_MAX_SIZE
    \brief  nb max de caractères des noms de fichiers

    \def    MAX_FILE_SIZE
    \brief  taille max d'un fichier (uchar)

    \def    INODE_TABLE_SIZE
    \brief  taille de la table d'inodes 
    \note   taille fixe = nb max de fichiers dans le SE

    \def    MAX_MSG
    \brief  taille maximale d'un message
    \note   uchar

    \def    TIMESTAMP_SIZE
    \brief  taille de la timestamp
    \note   avec \0 et pour que ça tombe juste avec les blocs

    \def    NB_USERS
    \brief  nombre d'utilisateurs
*/
#define FILENAME_MAX_SIZE 32
#define MAX_FILE_SIZE (2*1024)
#define INODE_TABLE_SIZE 10
#define MAX_MSG 1024
#define TIMESTAMP_SIZE 24+2
#define NB_USERS 5

/*! \def    BLOCK_SIZE
    \brief  taille de bloc
    \note   en octets

    \def    SUPER_BLOCK_SIZE
    \brief  taille du super bloc
    \note   en nombre de blocs

    \def    INODES_START
    \brief  indice de début de la table d'inodes
    \note   en octets

    \def    INODE_SIZE
    \brief  taille d'une inode
    \note   = 27 en blocs = 8 blocs de filename+6 uint+timestamps
*/
#define BLOCK_SIZE 4
#define SUPER_BLOCK_SIZE 4
#define INODES_START SUPER_BLOCK_SIZE*BLOCK_SIZE+1
#define INODE_SIZE FILENAME_MAX_SIZE/BLOCK_SIZE+6+(TIMESTAMP_SIZE*2)/BLOCK_SIZE

typedef unsigned int uint; // même taille que int
typedef unsigned char uchar; // 8 bits non signés = octet







/*------------------------------------------------------------
  TYPES
------------------------------------------------------------*/

/*! \typedef  uint
    \brief    unsigned int
    \note     même taille que int
*/
typedef unsigned int uint;

/*! \typedef  uchar
    \brief    unsigned char
    \note     8 bits non signés = octet
*/
typedef unsigned char uchar;

/*! \typedef  user_t
    \struct user_s
    \brief  structure pour la table des utilisateurs
    \param  login   login
    \param  passwd  mot de passe
    \note   64 hex char = haché du passwd
*/
typedef struct user_s{
  char login[FILENAME_MAX_SIZE];
  char passwd[SHA256_BLOCK_SIZE*2 + 1];
} user_t;

/*! \typedef  session_t
    \struct session_s
    \brief  pour gérer l'uid tout le long de la session
    \param  userid  id utilisateur
*/
typedef struct session_s{
  int userid;
} session_t;

/*! \typedef  block_t
    \struct block_s
    \brief  Type of a block of data
    \param  data  données sous forme de tableau, une case par octet.
*/
typedef struct block_s{
    uchar data[BLOCK_SIZE];
} block_t;

/*! \typedef  inode_t
    \brief    Type of the pseudo-inode structure
    \struct inode_s
    \brief  pseudo-inode structure
    \param  filename  nom du fichier, '\0' compris.
    \param  size  taille du fichier en octets
    \param  uid   id de l'utilisateur propriétaire
    \param  uright  droits de l'utilisateur entre 0 et 3
    \param  oright  droits des autres entre 0 et 3
    \param  ctimestamp  date de création (26 octets)
    \param  mtimestamp  date de dernière modification (26 octets)
    \param  nblock  nombre de blocs occupés par le fichier
    \param  first_byte  indice du premier octet de données sur le disque virtuel
*/
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

/*! \typedef  inode_table_t
    \brief    table d'inodes
    \note     taille fixe = INODE_TABLE_SIZE
*/
typedef inode_t inode_table_t[INODE_TABLE_SIZE];

/*! \typedef  users_table_t
    \brief    table des utilisateurs
    \note     taille fixe = NB_USERS. L'indice est l'uid
*/
typedef user_t users_table_t[NB_USERS];

/*! \typedef  super_block_t
    \brief    type du super bloc
    \struct super_block_s
    \brief  structure du super bloc
    \param  number_of_files nombre de fichiers dans le super bloc
    \param  number_of_users nombre d'utilisateurs dans le super bloc
    \param  nb_blocks_used  nombre de blocs utilisés
    \param  first_free_byte premier octet libre
*/
typedef struct super_block_s{
  uint number_of_files;
  uint number_of_users;
  uint nb_blocks_used ;
  uint first_free_byte;
  } super_block_t;

/*! \typedef  virtual_disk_t
    \brief    type du disque virtuel
    \struct virtual_disk_s
    \brief  structure du disque virtuel
    \param  super_block super bloc
    \param  users_table table des utilisateurs
    \param  inodes      table d'inodes
    \param  storage     fichier vdisk du système de fichiers
*/
typedef struct virtual_disk_s {
    super_block_t super_block;
    users_table_t users_table;
    inode_table_t inodes;
    FILE *storage;
} virtual_disk_t;

/*! \typedef  file_t
    \brief    type pour les fichiers
    \struct file_s
    \brief  structure pour les fichiers
    \param  size  taille du fichier en octets avec pading (complétion du dernier bloc avec des zéros)
    \param  data  données du fichier
    \note   fichiers texte seulement
*/
typedef struct file_s{
  uint size;
  uchar data [MAX_FILE_SIZE] ;
} file_t ;

/*! \typedef  cmd_t
    \brief    type pour gérer les commandes de l'interprète
    \struct cmd_s
    \brief  strucutre pour gérer les commandes de l'interprète
    \param  tabArgs tableau des arguments
    \param  nb_args nombre d'arguments
*/
typedef struct cmd_s{
    char ** tabArgs;
    int nbArgs;
} cmd_t;

virtual_disk_t disk;  // la variable globale de disk









/*------------------------------------------------------------
  FONCTIONS COUCHE 1
------------------------------------------------------------*/

/*! \fn print_block
    \brief  fonction permettant d'afficher le contenu d'un bloc
    \author Guilhem C.
    \param[in]  bloc  bloc à afficher
*/
void print_block(block_t *bloc);

/*! \fn compute_nblock
    \brief  fonction permettant de calculer le nombre de blocs nécéssaire pour stocker nb_bytes octets
    \author Guilhem C.
    \pre    compute_nblock est défini pour nb_bytes > 0
    \param[in]  nb_bytes  nombre d'octets à convertir
    \param[out] size_in_blocks  nombre de blocs
*/
int compute_nblock(int nb_bytes);

/*! \fn write_block
    \brief  fonction permettant d'écrire un bloc de données sur le disque dur
    \author Guilhem C.
    \pre    write_block est défini pour pos > -1 et pos < TAILLE_FICHIER-3
    \param[in]  bloc  emplacement oùp est stocké le bloc à écrire
    \param[in]  pos   position où écrire le bloc
*/
void write_block(block_t *bloc, int pos);

/*! \fn read_block
    \brief  fonction permettant de lire un bloc de données sur le disque dur
    \author Guilhem C.
    \pre    read_block est défini pour pos > -1 et pos < TAILLE_FICHIER-3
    \param[in]  bloc  emplacement où le bloc lu sera stocké
    \param[in]  pos   position du bloc à lire
*/
void read_block(block_t *bloc, int pos);

/*! \fn shutoff_save
    \brief  fonction permettant de sauvegarder la table d'inodes avant extinction du système
    \author Victor J.
*/
void shutoff_save();
int compute_nblock(int nb_bytes);
void write_block(block_t *bloc,int pos);
void read_block(block_t *bloc,int pos);
void convert_int_to_block(block_t* block,uint nombre);
void convert_block_to_int(block_t block,uint *nombre);
void gestion_ouverture(FILE *f,char* path);
void init_disk_sos(char* path);
//couche 2
void read_int_block(block_t block,int *pos,uint *buff);
void write_int_block(block_t block,int *pos,uint *buff);
void read_mult_blocks(char *buff,int taille_block,int *pos);
void write_mult_blocks(char *buff,int taille_block,int *pos);
void read_inodes_table();

/*! \fn write_inodes_table
    \brief  fonction permettant d'écrire la table d'inodes dans le fichier disque
    \author Guilhem C.
*/
void write_inodes_table();

/*! \fn clear_inode
    \brief  fonction réinitialisant une inode
    \author Guilhem C.
    \param[in]  indice  indice de l'inode à réinitialiser
*/
void clear_inode(int indice);

/*! \fn delete_inode
    \brief  fonction permettant de supprimer une inode
    \author Guilhem C.
    \param[in]  indice  indice de l'inode à supprimer
    \note   cette fonction ne laisse pas de trou dans la table d'inodes
*/
void delete_inode(int indice);
int get_unused_inode();
void write_super_block();

/*! \fn read_super_block
    \brief  fonction permettant de lire le super bloc au début du fichier disque
    \author Keylan A.
*/
void read_super_block();

//couche 3
void init_users_table();
void read_users_table();
void write_users_table();

#endif // OS_DEFINES
