#ifndef FS_VFS_H
#define FS_VFS_H

#include "sys.h"

#define VNON  0
#define VREG  1
#define VDIR  2
#define VBLK  3
#define VCHR  4
#define VLNK  5
#define VSOCK 6
#define VBAD  7

typedef unsigned long nspace_id;
typedef long long vnode_id;
typedef struct nspace_info *nspace_info;
struct nspace_info {
	vnode_id root;
};

typedef struct vfs *vfs;
struct vfs {
	vfs next; /* next vfs */
	vfsops ops; /* vfs operations */
	vnode nodes; /* vnodes in use */
	int flag;
	int block_size; /* native block size */
	void *data;
};

typedef struct vfsops *vfsops;
struct vfsops {
	int (*vfs_mount)();
	int (*vfs_unmount)();
	int (*vfs_root)();
	int (*vfs_stat)();
	int (*vfs_sync)();
	int (*vfs_fd)();
	int (*vfs_vget)();
};

typedef struct vnode *vnode;
struct vnode {
	uint16_t flag;
	uint16_t count;
	uint16_t shared_locks;
	uint16_t ex_locks;
	vfs mounted; /* vfs mounted here */
	vnodeops ops; /* vnode operations */
	/* TODO: Realize them. */
	union {
		socket sock;
		stream strm;
	};
	vfs master; /* master vfs */
	int type; /* type */
	void *data;
};

/* +----+     +----+     +----+     +----+
 * | n1 |next>| n2 |next>| n3 |next>| n4 |
 * |    |<prev|    |<prev|    |<prev|    |
 * +----+     +----+     +----+     +----+
 *  head                             tail
 *                count = 4
 */
typedef struct vnlist *vnlist;
struct vnlist {
	vnode head;
	vnode tail;
	int count;
};

typedef struct vnlink *vnlink;
struct vnlink {
	vnode prev;
	vnode next;
};

/* Vnode layer functions. */
typedef int v_read_vnode(void *nspace, vnode_id vid, char r, void *vnode);

typedef struct vnodeops *vnodeops;
struct vnodeops {
	int (*vn_open)();
	int (*vn_close)();
	int (*vn_rdwr)();
	int (*vn_ioctl)();
	int (*vn_select)();
	int (*vn_getattr)();
	int (*vn_setattr)();
	int (*vn_access)();
	int (*vn_lookup)();
	int (*vn_create)();
	int (*vn_remove)();
	int (*vn_link)();
	int (*vn_rename)();
	int (*vn_mkdir)();
	int (*vn_rmdir)();
	int (*vn_readlink)();
	int (*vn_fsync)();
	int (*vn_inactive)();
	int (*vn_bmap)();
	int (*vn_strategy)();
	int (*vn_bread)();
	int (*vn_brelse)();
};

extern int vnode_init();

#endif
