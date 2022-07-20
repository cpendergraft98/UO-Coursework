#import <stdio.h>
#import <stdlib.h>

void sum(long *array, long n, long *dest){
  int i = n;
  int j = n;
  goto loop1;

  loop1:
    if i > 0{
      *dest = 0;
      goto loop2;
    }else{
      goto end;
    }

  loop2:
    if j > 0{
      *dest += *array;
      array += 1;
      j -= 1;
      goto loop2;
    }else{
      j = n;
      dest += 1;
      i -= 1;
      goto loop1;
    }

  end:
    break
