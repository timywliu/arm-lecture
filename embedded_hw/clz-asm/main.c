#include <stdio.h>

extern int clz(unsigned int x);

int main(int argc, char **argv)
{
  int number=0;
  int result=0;

  scanf("%d",&number);
  result = clz(number);   
  printf("The clz(%d) is: %d\n", number, result);
}

