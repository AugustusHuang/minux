#ifndef FS_INODE_H
#define FS_INODE_H

typedef struct fs_inode *fs_inode;
struct fs_inode {
	void *addr; /* address of file inode */
	int32_t magic;
	mode_t flag;
	tm_t ctime; /* create time */
	tm_t mtime; /* last modify time */
	void *parent; /* parent pointer, root will point to itself */
	int32_t size; /* inode size */
	void *data; /* the content */
};

/* flag arguments */

#endif
