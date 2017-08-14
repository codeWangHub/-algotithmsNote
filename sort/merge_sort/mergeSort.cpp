
#include <iostream>

using namespace std;

/*  数组 ：arr[l,...m] 已排好序
 *      ：arr[m+1,...r] 已排好序
 */
void __merge(int *arr,int l,int m, int r)
{
  /*  复制两个数组 */
  int  llen = m-l+1;
  int  rlen = r-m;
  int *larr = new int[llen+1];
  int *rarr = new int[rlen+1];

  for(int i = 0; i < llen; ++i) {
      larr[i] = arr[l+i];
  }

  for(int i = 0; i < rlen; ++i) {
      rarr[i] = arr[m+1+i];
  }
  /* 放置两个哨兵，无穷大 */
  larr[llen] = 65535;
  rarr[rlen] = 65535;

  /* 合并 */
  int p = 0;
  int q = 0;
  for(int i = 0; i <  (r-l+1); ++i) {
      if( larr[p] < rarr[q] ) {
          arr[l+i] = larr[p++];
      }else{
          arr[l+i] = rarr[q++];
      }
  }

  delete larr;
  delete rarr;
}


/* 对数组的 arr[l,...r-1] 排序 */
void mergeSort(int *arr,int l, int r)
{
    cout<<"现在处理<"<<l<<","<<r<<">"<<endl;
    cout<<"是否需要继续分解？    --->";
    if(l < r) {
    cout<<"是"<<endl;
      /* 对左侧排序 */
      //cout<<"1. 左侧处理 <"<<l<<","<<(l+r)/2<<">"<<endl;
      mergeSort(arr,l,(l+r)/2);
      /* 对右侧排序 */
      //cout<<"2. 右侧处理 <"<<(l+r)/2+1<<","<<r<<">"<<endl;
      mergeSort(arr,(l+r)/2+1,r);
      /* 合并 */
      cout<<"合并：<"<<l<<","<<(l+r)/2<<","<<r<<">"<<endl;
      __merge(arr,l,(l+r)/2,r);
    }else{
      cout<<"否，直接返回"<<endl;
    }
}


int main(int argc,char **argv) {
      int arr[] = {6,5,4,3,2,1};

      mergeSort(arr,0,5);

      for(int i = 0; i < 6; ++i) {
        cout<<arr[i];
      }
      cout<<endl;

      return 0;
}
