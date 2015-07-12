#ifndef FS_FS_H
#define FS_FS_H

/* Interface header file of u3x file system. */
#include "inode.h"
/* et cetera */

/* Superblock struct. Make it aligned as neatly as possible.
 * Magic numbers will be there to supply additional check.
 * The size of the superblock will be no over 512-bytes. */
typedef struct fs_superblock *fs_superblock;
struct fs_superblock {
	char name[SUPER_NAME_LENGTH_CONFIG];
	int32_t magic1;
	/* something */
	int32_t magic2;
	/* something */
	int32_t magic3;
	/* something */
};

#define MAGIC1 /* uxxx */
#define MAGIC2 /* rtos */
#define MAGIC3 /* uxfs */

#endif
