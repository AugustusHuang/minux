#ifndef FS_FS_H
#define FS_FS_H

/* Interface header file of u3x file system. */
#include "inode.h"
#include "dir.h"
#include "file.h"
#include "journal.h"
#include "bit.h"
#include "mount.h"
#include "attr.h"
#include "util.h"
#include "config.h"
#include "../kern/config.h"

typedef off_t fs_off_t;

#if WORDSIZE_CONFIG == 32
#define DIRECT_BLOCKS 20
#elif WORDSIZE_CONFIG == 64
#define DIRECT_BLOCKS 16
#else
#error word size doesn't supported.
#endif

/* +--------------------+
 * | uint32_t      type |
 * +--------------------+
 * | union        value |
 * +--------------------+
 * | uint16_t  name_len |
 * +--------------------+
 * |       name[0]      |
 * +....................+
 * |      name[1..]     |
 * +....................+
 * |  maybe value then  |
 * +--------------------+
 * Though value is not inside the structure, it will be there right after
 * the name string of the corresponding structure.
 * TODO: The length of all those things should be a multiple of 8 (we assume)
 * should we pad them with 0s?
 * TODO: Use union or not? */
typedef struct attr_map *attr_map;
struct attr_map {
	uint32_t type;
	union attr_value value;
	uint16_t name_len;
	char attr_name[1];
};

union attr_value {
	struct {
		void *ptr;
		uint16_t len;
	} raw;
	uint32_t u32;
	int32_t  i32;
	uint64_t u64;
	int64_t  i64;
	float    f;
	double   d;
};

#define ATTR_RAW    0U
#define ATTR_U32    1U
#define ATTR_I32    2U
#define ATTR_U64    3U
#define ATTR_I64    4U
#define ATTR_FLOAT  5U
#define ATTR_DOUBLE 6U

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

/* data_stream type in inode. 
 * Inode must be a power of two in size,
 * here data_stream has 8 * DIRECT_BLOCKS + 16 + sizeof(off_t) * 4
 * TODO: Is triple indirect level necessary? */
typedef struct data_stream *data_stream;
struct data_stream {
	struct block_run direct[DIRECT_BLOCKS];
	fs_off_t max_d_range; /* maximal direct block range */
	struct block_run single_indirect;
	fs_off_t max_si_range; /* maximal single indirect block range */
	struct block_run double_indirect;
	fs_off_t max_di_range; /* maximal double indirect block range */
	fs_off_t size;
};

/* Get the idea from BFS by Dominic Giampaolo.
 * +-------------------+-------------------+-...-+
 * |     N blocks      |                   |     | All blocks
 * +-------------------+-------------------+-...-+
 * | allocation grp 1  | allocation grp 2  |     |
 * +-------------------+-------------------+-...-+
 *    ^           ^
 *    |<-  len  ->|
 *  start */

typedef struct block_run *block_run;
struct block_run {
	uint32_t allocation_group; /* a virtual concept */
	uint16_t start;
	uint16_t len;
};

/* inode etc type */
typedef struct inode_etc *inode_etc;
struct inode_etc {
	lock lock; /* r/w/a lock of this inode TODO: Used in kernel? */
	char *content;
	int counter;
};

/* Our file system header. */
typedef struct fs_header *fs_header;
struct fs_header {
	fs_superblock sb;
	/* FIXME: et cetera */
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
