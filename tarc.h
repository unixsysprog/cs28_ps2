#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BLOCK_SIZE 512
//#define BLOCK_SIZE 10240
//#define CONTENT_SIZE 10240
//#define CONTENT_SIZE 9728

#define REGULAR     '0'
#define HARDLINK    '1'
#define SYMLINK     '2'
#define CHAR        '3'
#define BLOCK       '4'
#define DIRECTORY   '5'
#define FIFO        '6'
#define CONTIGUOUS  '7'

/* for reference
struct tar_header {
    char name[100];     // name of the file
    char mode[8];       // file mode
    char uid[8];        // owner userid
    char gid[8];        // owner group id
    char size[12];      // size of file
    char mtime[12];     // modification time
    char checksum[8];   // checksum
    char type;          // file type
    char linkname[100]; // name of linked file
    char ustar[8];      // ustar
    char uname[32];     // owner user name
    char gname[32];     // owner group name
    char devmajor[8];   // device major number
    char devminor[8];   // device minor number
    char prefix[155];   // file name prefix
};
*/

#define NAME_SIZE 100
#define NAME_OFFSET 0

#define MODE_SIZE 8
#define MODE_OFFSET 100

#define UID_SIZE 8
#define UID_OFFSET 108

#define GID_SIZE 8
#define GID_OFFSET 116

#define SIZE_SIZE 12
#define SIZE_OFFSET 124

#define MTIME_SIZE 12
#define MTIME_OFFSET 136

#define CHECKSUM_SIZE 8
#define CHECKSUM_OFFSET 148

#define TYPE_SIZE 1
#define TYPE_OFFSET 156

#define LINKNAME_SIZE 100
#define LINKNAME_OFFSET 157

#define USTAR_SIZE 6
#define USTAR_OFFSET 257

#define USTAR_V_SIZE 2
#define USTAR_V_OFFSET 263

#define UNAME_SIZE 32
#define UNAME_OFFSET 265

#define GNAME_SIZE 32
#define GNAME_OFFSET 297

#define DEVMAJOR_SIZE 8
#define DEVMAJOR_OFFSET 329

#define DEVMINOR_SIZE 8
#define DEVMINOR_OFFSET 337

#define PREFIX_SIZE 155
#define PREFIX_OFFSET 345

typedef struct stat stat_t;

int tar_it(int, char *);
void pad_file(int);
