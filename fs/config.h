#ifndef FS_CONFIG_H
#define FS_CONFIG_H

#define FS_ENDIAN_CONFIG         ENDIAN_CONFIG

/* Block size, maybe multiple of 512 bytes. */
#define BLOCK_SIZE_CONFIG        1024U

/* Change on your own. To be aligned, use a multiple of 4! */
#define SUPER_NAME_LENGTH_CONFIG 32U

/* Directory name length. */
#define DIR_NAME_LENGTH_CONFIG   32U

/* File name length. */
#define FILE_NAME_LENGTH_CONFIG  32U

/* Shared memory file size. */
#define FS_SHM_CONFIG            1024U

#endif
