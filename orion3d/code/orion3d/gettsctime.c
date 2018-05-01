
#include "gettsctime.h"

/* for rdtsc */
#include <asm/msr.h>
/* for perror */
#include <stdio.h>
/* for open/read/close */
#include <fcntl.h>
#include <unistd.h>
/* for strstr */
#include <string>
/* for atof/atoi */
#include <stdlib.h>

#define MAX_CPUINFO_SIZE 512

/* gets the cycle count of the cpu */
void gettsc(long long *time) {

  unsigned int high, low;
  high = low = 0;

  rdtsc(low, high);

  *time = (high<<16) + low;
}

/* get the speed of the computer we're running on -- only tested on linux!! */
float getmhz(void) {

  int cpuinfo_fd,c, i;
  char file[MAX_CPUINFO_SIZE],mhz_s[8];
  char *mhz_str;

  mhz_str = (char *)malloc(100);

  /* open /proc/cpuinfo */
  if( (cpuinfo_fd = open("/proc/cpuinfo",O_RDONLY)) < 0) {
    perror("error opening /proc/cpuinfo");
    exit(-1);
  }

  i = 0;
  /* read in blocks from source file */
  while( (read(cpuinfo_fd,&c,1)) > 0 ) {
    file[i] = c;
    i++;
  }

  /* cleanup */
  close(cpuinfo_fd);

  /* parse file */
  if( (mhz_str = strstr(file,"cpu MHz")) == NULL) {
    perror("cpu mhz not found");
    exit(-1);
  }

  for(i=0;i<7;i++) {
    mhz_s[i] = mhz_str[11+i];
  }
  mhz_s[i] = '\0';
  
  return atof(mhz_s);
}

/* takes in the cycle count, and returns the time in nanoseconds */
long long gettsctime(long long tsc) {

  float mhz;

  mhz = getmhz();

  return (long long)(((double)tsc/(double)mhz)*1000);
}

