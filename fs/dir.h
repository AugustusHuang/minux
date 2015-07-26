#ifndef FS_DIR_H
#define FS_DIR_H

typedef struct fs_dir *fs_dir;
struct fs_dir {
	unsigned char name[DIR_NAME_LENGTH_CONFIG];
};

typedef struct fs_dirent *fs_dirent;
struct fs_dirent {
};

#endif
