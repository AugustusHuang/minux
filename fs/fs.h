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

/* +--------------------+
 * | uint32_t      type | 
 * +--------------------+
 * | name len | val len |
 * +---------------------
 * |       name[0]      |
 * ......................-------------- struct border
 * |        name        |
 * +--------------------+
 * |        value       |
 * ......................
 * |        value       |
 * +--------------------+
 * Though value is not inside the structure, it will be there right after
 * the name string of the corresponding structure.
 * TODO: The length of all those things should be a multiple of 8 (we assume)
 * should we pad them with 0s?
 * TODO: Use union or not? */
typedef struct attr_map *attr_map;
struct attr_map {
	uint32_t attr_type;
	uint16_t attr_name_len;
	uint16_t attr_value_len;
	char attr_name[1];
};

#define ATTR_RAW  0U
#define ATTR_U8   1U
#define ATTR_I8   2U
#define ATTR_U16  3U
#define ATTR_I16  4U
#define ATTR_U32  5U
#define ATTR_I32  6U
#define ATTR_U64  7U
#define ATTR_I64  8U

/* map is a pointer to struct attr_map */
#define inode_attr_data(map) \
	(void *)((char *)map + sizeof(*map) + map->attr_name_len - 1)

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

/* data_stream type in inode. TODO: Is triple indirect level necessary? */
typedef struct data_stream *data_stream;
struct data_stream {
	block_run direct[DIRECT_BLOCKS_CONFIG];
	fs_off_t max_d_range; /* maximal direct block range */
	block_run single_indirect;
	fs_off_t max_si_range; /* maximal single indirect block range */
	block_run double_indirect;
	fs_off_t max_di_range; /* maximal double indirect block range */
	fs_off_t size;
};

/* inode etc type */
typedef struct inode_etc *inode_etc;
struct inode_etc {
	lock lock; /* r/w/a lock of this inode */
	char *content;
	int counter;
};

#define SUPER_MAGIC1 0x75787878 /* uxxx */
#define SUPER_MAGIC2 0x52544F53 /* RTOS */

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
