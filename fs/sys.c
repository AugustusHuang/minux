#include "vfs.h"
#include "sys.h"

int sys_symlink(const char *old_path, int fd, const char *new_path)
{
}

ssize_t sys_readlink(int fd, const char *old_path, char *buf, size_t buf_size)
{
}

int sys_mkdir(int fd, const char *path, int perms)
{
}

int sys_open(int fd, const char *path, int mode, int perms, bool coe)
{
}

int sys_close(int fd)
{
}

fs_off_t sys_lseek(int fd, fs_off_t pos, int whence)
{
}

ssize_t sys_read(int fd, void *buf, size_t len)
{
}

ssize_t sys_write(int fd, void *buf, size_t len)
{
}

int sys_ioctl(int fd, int cmd, void *arg, size_t size)
{
}

int sys_unlink(int fd, const char *path)
{
}

int sys_link(int ofd, const char *old_path, int nfd, const char *new_path)
{
}

int sys_rmdir(int fd, const char *path)
{
}

int sys_rename(int ofd, const char *old_path, int nfd, const char *new_path)
{
}

void *sys_mount(const char *fs, int fd, const char *pos, const char *dev,
		unsigned long flag, void *param, size_t len)
{
}

int sys_unmount(int fd, const char *pos)
{
}

int sys_rstat(int fd, const char *path, fs_stat st, bool eatlink)
{
}

int sys_wstat(int fd, const char *path, fs_stat st, long mask, bool eatlink)
{
}

int sys_opendir(int fd, const char *path, bool coe)
{
}

int sys_closedir(int fd)
{
}

int sys_readdir(int fd, fs_dirent buf, size_t buf_size, long count)
{
}

int sys_rewinddir(int fd)
{
}

int sys_chdir(int fd, const char *path)
{
}

int sys_access(int fd, const char *path, int mode)
{
}

int sys_sync()
{
}

