#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd;
    char path[54] = "/Users/noder/Documents/GitHub/type-pointer/data/shareMem";
    fd = open(path,O_CREAT|O_RDWR,00777);
    double * p_map;
    double val = 15.0;
    p_map=(double *)mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    write(fd,"",1);
    close(fd);
    printf("%p\n",p_map);
    printf("val:%f,%p,%lu\n",val,&val,sizeof(double));
    memcpy(p_map,&val,sizeof(double));
    printf("p_map:%f,%p,%lu\n",*p_map,p_map,sizeof(double));
    munmap(p_map,1);
    return 0;
}

// int main()
// {
//     int fd;
//     char path[54] = "/Users/noder/Documents/GitHub/type-pointer/data/shareMem";
//     double *p_map;
//     fd=open(path,O_CREAT|O_RDWR,00777);
//     p_map=(double *)mmap(NULL,sizeof(double),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
//     printf("p_map2:%f;\n",*p_map);
//     munmap(p_map,sizeof(double));
//     return 0;
// }