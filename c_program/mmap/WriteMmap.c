#include "stdio.h"
#include "fcntl.h"
#include "unistd.h"
#include "string.h"
#include <sys/mman.h>

#define PATH "./mymap"


typedef struct Mmap{
    int size;
    char str[100];
}Mmap_s;

int main()
{
    int fd = open(PATH,O_RDWR|O_CREAT|O_TRUNC,0664);
    if(-1 == fd)
        printf("W:open error\n");
    Mmap_s * DataAddr;
    Mmap_s   Data={11,"hello world"};
    ftruncate(fd,sizeof(Data));
    DataAddr = mmap(NULL,sizeof(Data),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (MAP_FAILED == DataAddr)
        printf("W:map error!\n");
    close(fd);
    memcpy(DataAddr,&Data,sizeof(Data));
    munmap(DataAddr,sizeof(Data));
    return 0;
}
