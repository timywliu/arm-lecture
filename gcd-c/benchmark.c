#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 1000
#define MAX_COUNT 10
#define FIXED_START_NUM 7

extern int findGCDv1(int a,int b);
extern int findGCDv2(int a,int b);
extern int findGCDv3(int a,int b);

double benchmark1(int bound, int(*findGCD)(int, int)) {
  double startTime = 0, endTime = 0, average = 0;
  int i, j, count, v;

  for(count = 0; count < MAX_COUNT; count++)
  {
    startTime = (double)clock()/CLOCKS_PER_SEC;
    for(i = 2; i < bound; i++) {
      for(j = 2; j < bound; j++)
        v = (*findGCD)(i,j);
    }
    endTime = (double)clock()/CLOCKS_PER_SEC;
    average += endTime-startTime;
  }
  average /= MAX_COUNT;
  //printf("GCD(%d, %d)=%d, average=%f\n", i, j, v, average);
  return average;
}

double benchmark2(int bound, int(*findGCD)(int, int)) {
  double startTime = 0, endTime = 0, average = 0;
  int i, count, v;

  for(count = 0;count < MAX_COUNT; count++)
  {
    startTime = (double)clock()/CLOCKS_PER_SEC;
    for(i = FIXED_START_NUM; i < bound; i++) {
      v = (*findGCD)(FIXED_START_NUM,i);
    }
    endTime = (double)clock()/CLOCKS_PER_SEC;
    average += endTime-startTime;
  }
  average /= MAX_COUNT;
  //printf("GCD(%d, %d)=%d, average=%f\n", FIXED_START_NUM, i, v, average);
  return average;
}

int main(int argc, char **argv) {
  int version, bnum, i;
  int (*fp)(int,int);
  char filename[8];
  FILE *f;
  double avg;

  if (argc != 3) {
    printf("Cmd format should be: benchmark [GCD_version] [benchmark#]\n(GCD_verstion = 1-3, benchmark# = 1-2) \n");
    return 1;
  }

  version = atoi(argv[1]);
  switch(version) {
    case 1:
      fp = findGCDv1;
      break;
    case 2:
      fp = findGCDv2;
      break;
    case 3:
      fp = findGCDv3;
      break;
    default:
      printf("No this GCD version: %d\n", version);
      return 1;
  }

  bnum = atoi(argv[2]);
  if (bnum < 1 || bnum > 2) {
      printf("No this benchmark #: %d\n", bnum);
      return 1;
  }

  sprintf(filename, "time_v%d", version);
  f = fopen(filename, "a+");  // a+ : read and write file without overwriting.

  if(f == NULL) {
    printf("CANNOT OPEN FILE %s !\n", filename);
    return 1;
  }

  for (i = 10; i <= MAX_NUM; i+=10) {
    if (bnum == 1)
      avg = benchmark1(i, fp);
    else
      avg = benchmark2(i, fp);

    fprintf(f, "%d %f\n", i, avg);
  }

  fclose(f);
  return 0;
}

