#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv)
{
    int f=open(argv[1], O_RDONLY);
    struct stat b;
    size_t fs;
    char a[1024], chr;
    int k=0, sum=0, last=1;
    int i=0;
    int bad=0;
    if (argc != 2){
        printf("Wrong args\n");
        return -1;
    }
    if (f<0){
        printf("%s\n", strerror(errno));
        return -1;
    }
    fstat(f, &b);
    if ((b.st_mode & S_IFMT)!=S_IFREG){
        printf("Is a dir\n");
        return -1;
    }
    fs=b.st_size;
    if (b.st_size<=0) {
        printf("File empty\n");
    }
    for (i=0; i<fs; i++){
        read(f, &chr, 1);
        a[k]=chr;
        k++;
        if (isdigit(chr)){
            sum+=chr-'0';
            last=chr-'0';
        }
        else {
            if (isspace(chr)){
                if (sum!=0){
                    if (sum%3==0&&bad==0)
                        printf("BIZZ");
                    if ((last==5||last==0)&&bad==0)
                        printf("BUZZ");
                    printf(" ");
                    if ((sum%3!=0&&last!=5&&last!=0)||bad==1){
                        bad=0;
                        for (last=0; last<k; last++){
                            printf("%c", a[last]);
                        }
                    }
                    last=0;
                    k=0;
                    sum=0;
                }
            }
            else
                bad=1;
        }
    }
    close(f);
    printf("\n");
    return 0;
}
