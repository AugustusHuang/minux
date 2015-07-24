#ifndef FS_VFS_H
#define FS_VFS_H

#define VNON  0
#define VREG  1
#define VDIR  2
#define VBLK  3
#define VCHR  4
#define VLNK  5
#define VSOCK 6
#define VBAD  7
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

#endif
