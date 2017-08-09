# 排序算法——插入排序

[TOC]



插入排序一般指直接插入排序，其变种还有二分插入等。

插入排序的关键在于：

- 如何找到合适的插入位置
- 插入元素后不影响其他（已排序）元素。

## 1. 直接插入排序

直接插入排序用一个生活中常见的例子——扑克牌。如下图所示

![扑克牌](http://i.imgur.com/5BZ2jeI.gif)

假设我们原来手上的牌为2,4,5,10现在从牌堆中摸起来一张7，那么我们如何把7插入到合适的位置？

- 1. 从又往左一次对比，如果比较结果比摸起来的牌大，则说明不是合适的位置，继续往后面比较。
- 2. 在往后比较的同时，手中比较过的牌10要依次往后挪动一位。这样最后就会为我们插入新牌而留出一个位置。

直接插入排序的原理也是这样，下面时直接插入排序的伪代码：

```cpp
insert_sort(T array) {
  
 	for i =1 to array.length   /* 一开始手中有一张牌，认为时排好序的，从第二张开始插入 */  
      /* 寻找合适的位置 */
      key = array[i];
      j = i-1;
      while( j>=0 && key < array[j] ) {
      		array[j+1] = array[j];  /* 依次向后移位 */
        	j-=1;
      }  
      /* 找到了合适的位置 */     
  	  array[j+1]=key;	
}
```

### a.直接插入排序——C语言实现

```c
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
```



### b. 直接插入排序——c++实现

```cpp
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
```

### c. 直接插入排序——java实现

```java

public class InserSort {
    public static void  main(String[] args) {
        char[] arr = new char[]{'5','1','8','7','2','6','4','3','9','0'};

        sort(arr);
        for(char c : arr)
          System.out.println( c + " ");
    }

    /* java 不能使用泛型数组，可以使用重载 */
    public static  int sort(char[] arr) {
        char key;
        for(int i=0; i<arr.length; ++i) {
            key = arr[i];
            int j= i-1;
            while((j>=0) && (key < arr[j])) {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
        return 0;
    }
}
```



## 2. 二分插入排序

因为：**我们查找正确插入位置的序列时已经排好序**。在直接插入排序的基础上，为了加快排序速度，我们可以采用二分查找法快速找到正确的插入位置。

值得注意的时，在二分查找时我们要找的是**合适的位置**。

- 如何找到合适的位置？

  假设原来的序列为```a1,a2,a3,...,an```,其中前 k 个元素是已经排好序的，现在要把第 k+1个元素使用二分查找的方法找到合适的插入位置。

  ```a1,a2,...,ak```  ----> left 指向头部，right指向尾部。

  随着两个游标不断收拢，key插入的位置的范围也不断缩小，那么找到合适位置的条件是什么？

  - 1. mid 位置的元素恰好等于key，那么key就直接插入到mid的后面即可。

  - 2. 基数个元素的情况分析

       ```ak,ak+1,ak+2```  --->  left指向ak，right指向ak+2 ,mid指向ak+1.

       如果 key > mid ，那么 left = mid +1,指向ak+2，序列为```ak+2```。

       如果key < min  ,  那么 right = mid-1 , 指向ak,序列为```ak```。

       可以看出如果对于这种基数情况，最终left=right=mid 只有一个元素，只需要比较key和这个元素即可。返回条件就是left=right。

    3. 偶数个元素的情况分析

       ```ak,ak+1``` ---> left指向ak，right指向ak+1，mid指向ak。

       如果key > mid ,那么 left = mid +1 ，指向ak+1，序列为：```ak+1```

       如果key < mid , 那么 right = mid-1 ,**此时right<left**，序列为:```ak```

       可以看出最终也是只剩一个元素，退出条件为left=right。

   所以二分插入排序的伪代码为：

```cpp
binary_insert_sort(dataType arr) 
  	for i=1 to arr.length
        left = 0, right = i-1;
      	/* 二分查找合适的位置 */
       while left < right
          mid = (left + right) /2;
		  /* 直接插入到mid的后面 */ 
		  if(arr[mid] == key) {
            	break;
		  }else	if(key < arr[mid]) {
              right = mid -1;
		  }else {
              left = mid +1;	
		  }
	   /* 循环退出
        *   1. 因为key == arr[mid] 退出 , 插入到mid之后
        *   2. 因为 left >= right  退出 , 要比较key和mid的大小关系
        *  ============================================================
        *    5      7   要插入 4 
        *   l,m     r
        *   ------------------->  key < mid , r = m -1 ,m = (l+r)/2
        *          5 
        *    r,m   l 
        *   ------------------->  插入到 mid 之后
        *
        *  ============================================================
        *    5       7  要插入 8 
        *   l,m      r  
        *   -------------------> key >mid , l = m + 1 , m =(l+r)/2   
        *          7 
      	*        r,l,m    
        *   -------------------> 插入到 mid 之后
        *
        *   综上，如果left<right条件被破坏之后有更新mid操作
        *        那么无论哪种情况都是把key插入到mid之后。
        *        如果没有更新操作，那么就要在处理l和r时处理了。
        */

		/* 移位 */
		for j=i to mid 
          	arr[j] = arr[j-1];
		/* 插入 */
		arr[min+1] = key;
		
```

### 二分插入排序——C语言实现

```c
int binary_insert_sort(char arr[],unsigned len)
{
  char key;
  unsigned index;
  int l,r,m;
  unsigned i,j;

  for(i = 1; i < len; ++i) {
    key = arr[i];
    l = 0,r = i-1;
    while(l <= r) {
       m = (l + r)/2;
       if(key == arr[m]){
          index = m + 1;
          break;
       }

       if(key < arr[m]) {
          r = m - 1;
          index = l;
       }else {
          l = m + 1;
          index = r + 1;
       }
    }

    for (j = i; j>index; --j) {
        arr[j] = arr[j-1];
    }
    arr[index] = key;
  }

  return 0;
}
```



## 3. 插入排序的时间复杂度

**刚看了算法导论关于时间复杂的的内容，不知道对不对！**

#### a. 直接插入排序：

```cpp
int insertSort(dataType arr[],unsigned len)
{
    int i,j;                 // 2个指令的时间    
    dataType key;            // 1个指令的时间   
    // i=1 只执行一次，后两条执行 n-1-1次   	
  	for(i = 1; i < len; ++i ) {     // 1 + 2*（n-2） = 2n-3条指令时间 
        j = i-1;                    // 减法+赋值 -->  (n-2) * 2 = 2n-4 
        key = arr[i];               // 取值+赋值 -->  (n-2) * 2 = 2n-4
        // 假设每次都判断两个条件
        // 第一个花费一条指令，第二个：取值+判断两条指令的时间
        while( (j>=0) && (key < arr[j]) ) {   //  (n-2)*( (n-2) + (n-3) +...+ 1 )*3 
            arr[j+1] = arr[j];       //  (n-2)*( (n-2) + (n-3) +...+ 1 )*3       
            j--;                     //  (n-2)*( (n-2) + (n-3) +...+ 1 )*1
        }
        arr[j+1] = key;              //  (n-2) * 2      
    }
    return 0;                        //  1
}
```

假设计算机执行加法,减法，乘法，取值，赋值都花费**一个单位的时间**。那么直接插入排序的花费的总时间为以上各条语句花费时间的总和。

T(n) = 2 +1 + (2n-3) + (2n-4) + (2n-4) + ((n-2)\*((n-2)+(n-3)+...+1))\*7 + (2n-4) +1 。

可能这个有些地方不准确，但是无伤大雅。我们接着计算。

T(n) = 6n-8 + 7\*((n-2) \* (n\*(n-1)/2)) + 2n -3

​	 = 8n -11 + 7\* (n^2-n)/2

​         = 3.5n^2  + 4.5n -11

所以直接插入排序的时间复杂度为：O(n^2)  ,具体可以看《算法导论》-P44







