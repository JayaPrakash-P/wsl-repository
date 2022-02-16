#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

struct MMAPInfo
{
    void*   mmap_addr;
    size_t  mmap_length;
    int     mmap_prot;
    int     mmap_flags;
    int     mmap_fd;
    size_t  mmap_offset;
    char*   mappedBuffer;
} srcInfo;

typedef struct MMAPInfo MMAPInfo;

struct FileInfo
{
    char* fileName;
    int fd;
    struct stat fileStat;
} srcfile, dstFile;

void MMAP(MMAPInfo* info)
{
    info->mappedBuffer = (char*)mmap(info->mmap_addr, info->mmap_length, info->mmap_prot, info->mmap_flags, info->mmap_fd,info->mmap_offset);
    if (info->mappedBuffer == MAP_FAILED)
        fprintf(stderr, "MMAP FAIL : %d - %s\n", errno, strerror(errno));
}

int MUNMAP(MMAPInfo* info)
{
    return (int)munmap(info->mmap_addr, info->mmap_length);
}

int main()
{
    srcfile.fileName = "./MMAPPhysical.txt";

    srcfile.fd = open(srcfile.fileName, O_RDWR,0);
    fstat(srcfile.fd, &srcfile.fileStat);
    printf("srcfile.fd = %d\n",srcfile.fd);
    printf("srcfile.fileStat.st_size = %ld\n",srcfile.fileStat.st_size);

    srcInfo = (MMAPInfo){NULL,srcfile.fileStat.st_size,PROT_READ,MAP_SHARED,srcfile.fd,0,NULL};
    MMAP(&srcInfo);
    printf("srcInfo.mappedBuffer = %s\n",(srcInfo.mappedBuffer));
    printf("MUNMAP Result        = %d\n",MUNMAP(&srcInfo));
}