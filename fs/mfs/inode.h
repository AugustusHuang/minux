#ifndef FS_INODE_H
#define FS_INODE_H

/* Inode on disk, an inode will not be larger than a block, so in-node
 * attributes can be of size (block_size - inode_common_size). */
typedef struct fs_inode *fs_inode;
struct fs_inode {
	void *addr; /* address of file inode */
	int32_t magic1;
	mode_t flag;
	tm_t ctime; /* create time */
	tm_t mtime; /* last modify time */
	void *parent; /* parent pointer, root will point to itself */
	void *attr; /* attribute pointer */
	int32_t size; /* inode size */
	struct data_stream data; /* data stream type */
	inode_etc etc; /* etc pointer */
	int32_t magic2;
	int32_t pad[6]; /* will be 0 */
	/* the rest of inode space will be attributes */
};

#define INODE_MAGIC1   0x494E4F44 /* INOD */
#define INODE_MAGIC2   0x48673138 /* Hg18, I mean Hangar 18. */

/* flag arguments */
#define INODE_INUSE    0x00000001 /* whether inode is active */
#define INODE_ATTR     0x00000002 /* whether inode is an attribute inode */
#define INODE_LOGGED   0x00000004 /* whether inode is logged by journaling */
#define INODE_REMOVED  0x00000008 /* whether inode is removed */
#define PERMANENT_FLAG 0x0000FFFF /* permanent flag mask */

/* Now the flags underlying only affect inodes loaded in memory. */
#define INODE_WRITTEN  0x00010000 /* whether inode has been written */

/* create routine of a new inode */
extern int inode_create();
extern int inode_delete();

#endif
