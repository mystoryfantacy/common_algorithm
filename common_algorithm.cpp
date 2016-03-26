/*
1. 排序查找（搜索）
2. 字符串问题
3. 队列和栈（线性表）
4. 链表
5. 二叉树和堆（树形结构）
6. 图论算法
7. 动态规划
8. 位运算
9. 排列组合
10. 概率算法
*/

//插入排序
// o(n^2)
//特点：逐个插入
void InsertSort(int array[], int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; j>0; j--) {
			if (array[j] > array[j-1])
				swap(array,j,j-1);
			else
				break;
		}
};

//冒泡排序
//o(n^2)
//特点：两两比较，矮子往前
void bubblesort(int array[],int n) {
	for (int i = 0; i < n-1; i++)
		for (int j = n-1; j > i; j--) {
			if (array[j] > array[j-1])
        swap(array,j,j-1);
		}
};

//选择排序
//o(n^2)
//特点：先找到最小的放到第一个，再找到剩余中最小的，放到第二个。
void selectionsort(int array[], int n) {
  for (int i=0; i < n-1; i++) {
    int smallest = i;
    for (int j=i+1, j < n; j++) {
      if (array[smallest] > array[j])
        smallest = j;
    }
    swap(array,i,smallest);
  }
};

//希尔排序
//近似o(n^1.5 增量为2)
//特点: 分段插入排序
void sellsort(int array[], int n) {
  int step,h;
  for(h=1; h<=N/9; h = 3*h + 1);
  for (;h>0;h/3) {
    for (step = h; step < n; step++) {
      for (int i = step; i>= h; i -= h) {
        if (array[i] < array[i - h])
          swap(array, i, i-h);
      }
    }
  }
}

//快速排序
//o(n*logn ~ n^2)
// 递归调用， ？
void quicksort(int array[], int lo, int hi) {
  int i = lo, j = hi + 1;
  int v = array[lo];
  while(true) {
    while(array[++i] < v) if (i == hi) break;
    while(array[--j] > v) if (j == lo) break;
    if (i >= j) break;
    swap(array,i,j);
  }
  swap(array,lo,j);
  quicksort(array,lo,j-1);
  quicksort(array,j+1,hi);
}

//归并排序
//o(n*logn)
//分治排序
void merge(int array[], int aux[], int lo, int mid, int hi) {
  int i = lo, j = mid + 1;

  for (int k = lo; k <= hi; k++)
    aux[k] = array[k];

  for(int k = lo; k <= hi; k++)
    if (i > mid) a[k] = aux[j++];
    else if (j > hi) a[k] = aux[i++];
    else if (aux[j] < aux[i]) a[k] = aux[j++];
    else a[k] = aux[i++];
}
// 自顶向下
void mergesort(int array[], int aux[], int lo, int hi) {
  if (hi <= lo) return;
  int mid = lo + (hi -lo)/2;
  mergesort(array,aux,lo,mid);
  mergesort(array,aux,mid+1,hi);
  merge(array,aux,lo,mid,hi);
}



