#ifndef FS_FILE_H
#define FS_FILE_H

typedef struct fs_file *fs_file;
struct fs_file {
	unsigned char name[FILE_NAME_LENGTH_CONFIG];
};

#endif
