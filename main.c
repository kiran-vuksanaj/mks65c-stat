#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
#include<errno.h>

void smodef(char *buf, mode_t mode) {
  // printf("[mode octal: %o]\n",mode);
  short b = 0400; // the first byte to be considered is 0400, you can right shift until you've examined every bite
  short i;
  for( i = 0; i < 9; i++ ) {
    // printf("[byte octal: %6o]\n",b);
    if( b & mode ) {
      if( i % 3 == 0 ) buf[i] = 'r';
      if( i % 3 == 1 ) buf[i] = 'w';
      if( i % 3 == 2 ) buf[i] = 'x';
    }else {
      buf[i] = '-';
    }
    b = b >> 1;
  }
  buf[i] = '\0';
}

int main() {
  printf("Kiran Vuksanaj - Work 05 \n \"I need information, STAT!\"\n");
  struct stat statbuf;
  int status;
  char *filepath = "./main.c";
  // stuff
  status = stat(filepath,&statbuf);
  if(status < 0) {
    printf("Error %d while statting file: %s\n",errno,strerror(errno));
    return 1;
  }
  printf("metadata for:\t%s\n",filepath);
  printf("filesize: \t%ld bytes\n",statbuf.st_size);
  char mode[10];
  smodef(mode,statbuf.st_mode);
  printf("mode: \t\t%s\n",mode);
  printf("last accessed:\t%s\n",ctime(&statbuf.st_atim.tv_sec));
}
