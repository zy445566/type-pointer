#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

int typeFlush(const char* path,long unsigned int szie)
{
    szie = 4096;
    int fd;
    fd = open(path,O_CREAT|O_RDWR|O_TRUNC,00777);
    void * p_map;
    p_map=(void *)mmap(NULL,szie,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    write(fd,"",szie);
    close(fd);
    munmap(p_map,szie);
    return 0;
}

long unsigned int typeWrite(const char* path,long unsigned int szie,long unsigned int offset,double obj)
{
    int fd;
    double * p_map;
    fd = open(path,O_CREAT|O_RDWR,00777);
    p_map=(void *)mmap(NULL,szie,PROT_READ|PROT_WRITE,MAP_SHARED,fd,offset);
    close(fd);
    memcpy(p_map,&obj,sizeof(double));
    munmap(p_map,sizeof(double));
    return offset;
}

double typeRead(const char* path,long unsigned int szie,long unsigned int offset)
{
    int fd;
    double * p_map;
    fd = open(path,O_CREAT|O_RDWR,00777);
    p_map=(void *)mmap(NULL,szie,PROT_READ|PROT_WRITE,MAP_SHARED,fd,offset);
    close(fd);
    return *p_map;
}

int main()
{
    const char path[60] = "/Users/noder/Documents/GitHub/type-pointer/data/shareMem";
    long unsigned int szie = 4096;
    double testObj1 = 888.0;
    typeFlush(path,szie);
    printf("test1\n");
    long unsigned int  offset = typeWrite(path,szie,0,testObj1);
    printf("test2\n");
    double testObj2 = typeRead(path,szie,offset);
    printf("test3\n");
    printf("testObj2:%f\n",testObj2);
    return 0;
}