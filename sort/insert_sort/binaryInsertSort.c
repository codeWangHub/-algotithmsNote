#include <stdio.h>
#include <stdlib.h>


int binary_insert_sort(int arr[],unsigned len)
{
  int i,j;
  unsigned left,right,mid;
  int key;
  unsigned index = 0;

    

  return 0;
}

int main(int argc,char **argv) {
      int arr[] = {1,5,6,9,8,0,2,4,3,7};
      int i;
      binary_insert_sort(arr,10);

      for (i=0; i<10; i++) {
        printf("%d ",arr[i]);
      }
      return 0;
}
