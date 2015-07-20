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

typedef off_t fs_off_t;

/* Superblock struct. Make it aligned as neatly as possible.
 * Magic numbers will be there to supply additional check.
 * The size of the superblock will be no over 512-bytes. */
typedef struct fs_superblock *fs_superblock;
struct fs_superblock {
	char name[SUPER_NAME_LENGTH_CONFIG];
	int32_t magic1;
	int32_t endian; /* endian big or small */
	uint32_t block_size; /* block size in bytes */
	fs_off_t blocks; /* how many blocks in all */
	fs_off_t raw_blocks; /* how many unused blocks */
	fs_off_t inodes; /* how many inodes in this system */
	uint32_t root_inode; /* inode address of root entry, now 32-bits */
	fs_off_t inode_map_start; /* allocated inode map */
	fs_off_t inode_map_blocks; /* how many inode map blocks */
	int32_t magic2;
	fs_off_t inode_start; /* allocated inode */
	fs_off_t inode_blocks; /* how many inode used blocks */
	fs_off_t journal_start; /* start address of journal */
	fs_off_t journal_blocks; /* how many blocks in the journal */
	fs_off_t log_start; /* block of first active entry */
	fs_off_t log_end; /* block of end of the log */
	int32_t mount;
	int32_t flag; /* clean or not */
};

#define MAGIC1 0x75787878 /* uxxx */
#define MAGIC2 0x52544F53 /* RTOS */

/* FIXME: Should be consistent with the system endian. */
#define ENDIAN_BIG   0x12345678
#define ENDIAN_SMALL 0x87654321

#define FS_CLEAN 0x434C4541
#define FS_DIRTY 0x44495254

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
