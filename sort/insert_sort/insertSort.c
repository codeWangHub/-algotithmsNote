
/*
 *  直接插入排序——C语言实现
 *         ——by codewang 2017.8.6 at HUST
 */

#include <stdio.h>

typedef int dataType;

int insertSort(dataType arr[],unsigned len)
{
    int i,j;   /* 不能使unsigned 的，j可能被减小到-1 */
    dataType key;
    /* 必须有个临时变量，如果使用arr[i]代替key
     * 因为在移位过程中这个a[i]早就发生变化了。
     */
    for(i = 1; i < len; ++i ) {
        j = i-1;
        key = arr[i];
        while( (j>=0) && (key < arr[j]) ) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    return 0;
}

int main(int argc,char **argv)
{
  int arr[] = {5,6,7,4,1,2,9,3,0,8};
  unsigned i = 0;

  insertSort(arr,10);

  while(1) {
        printf("%d ",arr[i++]);
        if( i == 9 ) {
            printf("%d\n",arr[i]);
            break;
        }
  }
  return 0;
}
