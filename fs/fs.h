#ifndef FS_FS_H
#define FS_FS_H

/* Interface header file of u3x file system. */
#include "inode.h"
#include "dir.h"
#include "file.h"
#include "journal.h"
#include "mount.h"
#include "tag.h"
#include "util.h"

/* Superblock struct. Make it aligned as neatly as possible.
 * Magic numbers will be there to supply additional check.
 * The size of the superblock will be no over 512-bytes. */
typedef struct fs_superblock *fs_superblock;
struct fs_superblock {
	unsigned char name[SUPER_NAME_LENGTH_CONFIG];
	int32_t magic1;
	/* something */
	int32_t magic2;
	/* something */
	uint32_t mount;
};

#define MAGIC1 0x75787878 /* uxxx */
#define MAGIC2 0x52544F53 /* RTOS */

/* Filesystem APIs options. */
/* mount */
#define MOUNT_RDONLY   (1 << 0)
#define MOUNT_SYNC     (1 << 1)
#define MOUNT_NOATIME  (1 << 2)
#define MOUNT_BIND     (1 << 3)
#define MOUNT_MOVE     (1 << 4)
#define MOUNT_RELATIME (1 << 5)

/* seek */
#define SEEK_SET  0
#define SEEK_CUR  1
#define SEEK_END  2
#define SEEK_DATA 3
#define SEEK_HOLE 4
#define SEEK_MAX  SEEK_HOLE

#endif
