#ifndef FS_SYS_H
#define FS_SYS_H

extern int sys_symlink(const char *old_path, int fd, const char *new_path);
extern ssize_t sys_readlink(int fd, const char *path, char *buf,
		size_t buf_size);
extern int sys_mkdir(int fd, const char *path, int perms);
extern int sys_open(int fd, const char *path, int mode, int perms, bool);
extern int sys_close(int fd);
extern fs_off_t sys_lseek(int fd, fs_off_t pos, int whence);
extern ssize_t sys_read(int fd, void *buf, size_t len);
extern ssize_t sys_write(int fd, void *buf, size_t len);
extern int sys_ioctl(int fd, int cmd, void *arg, size_t len);
extern int sys_unlink(int fd, const char *path);
extern int sys_link(int old_fd, const char *old_path, int new_fd,
		const char *new_path);
extern int sys_rmdir(int fd, const char *path);
extern int sys_rename(int old_fd, const char *old_path, int new_fd,
		const char *new_path);
extern void *sys_mount(const char *fs, int fd, const char *where,
		const char *dev, unsigned long flag, void *parms, size_t len);
extern int sys_unmount(int fd, const char *where);
extern int sys_rstat(int fd, const char *path, fs_stat st,
		bool eatlink);
extern int sys_wstat(int fd, const char *path, fs_stat st, long mask,
		bool eatlink);
extern int sys_opendir(int fd, const char *path, bool);
extern int sys_closedir(int fd);
extern int sys_readdir(int fd, dirent buf, size_t buf_size, long count);
extern int sys_rewinddir(int fd);
extern int sys_chdir(int fd, const char *path);
extern int sys_access(int fd, const char *path, int mode);
extern int sys_sync();

#endif
