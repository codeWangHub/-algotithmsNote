
/*
 *    直接插入排序——c++实现
 *           by codewang 2017.8.7 at HUST
 */

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;


template<typename T>
int insertSort(T* arr ,unsigned len)
{

    T key;
    int i,j;

    for(i=1; i<len; ++i) {
        key = arr[i];
        j = i-1;

        while((j>=0) && (key < arr[j]) ) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    return 0;
}


int main(int argc,char **argv) {
    int  iarr[] = {5,1,3,4,6,7,9,8,2,0};

    insertSort(iarr,10);
    for(int i=0 ; i<10 ; ++i) {
        printf("%d ",iarr[i]);
    }
    printf("\n");
}
