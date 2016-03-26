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
// o(n^2) 稳定
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
//o(n^2) 稳定
//特点：两两比较，矮子往前
void bubblesort(int array[],int n) {
	for (int i = 0; i < n-1; i++)
		for (int j = n-1; j > i; j--) {
			if (array[j] > array[j-1])
        swap(array,j,j-1);
		}
};

//选择排序
//o(n^2) 不稳定
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
//近似o(n^1.5 增量为2) 不稳定
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
//o(n*logn ~ n^2) 不稳定
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
//o(n*logn) 稳定
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

//堆排序
//o(n*logn) 不稳定
//堆结构的构建和维护

//从下往上的堆有序化（上浮）
void swim(int array[], int k) {
  while( k>0 && array[(k-1)/2] < array[k]) {
    swap(array, (k-1)/2, k);
    k = (k-1) / 2;
  }
}
//从上往下的堆有序化（下沉）
void sink(int array[], int k, int n) {
  while( 2*k+1 < n) {
    int j = 2*k + 1;
    if (j<n-1 && array[j] < array[j+1]) j++;
    if (array[k] >= array[j]) break;
    swap(array,k,j)
    k = j;
  }
}

void heapsort(int array[], int n) {
  for (int k = n/2-1; k>=0; k--)
    sink(array,k,n);  //build heap;
  while(n>1) {
    swap(array,0,--n);
    sink(array,0,n);
  }
}

//基数排序
//o(n*log(r)m), r:基数 m:堆数 稳定
//特点：按 个十百千万 数位比较排序。用额外数组建一个桶。
//非重点，详细参看（http://blog.csdn.net/piaojun_pj/article/details/5911914）


//顺序查找
//o(n)
//特点：从头到尾依次比较
int sequentialsearcy(int array[], int n, int key) {
  int res = -1;
  for(int i=0; i<n; ++i) {
    if (array[i] == key) return i;
  }
  return -1;
}

//折半查找，二分查找
//最坏：o(n*logn) 平均：o(logn)
//特点：有序数组，二分查找
int binarysearch(int array[], int n, int key) { //pre-sort array
  int lo = 0, hi = n - 1;
  while(lo <= hi) {
    int mid = lo + (hi - lo)/2;
    if (key < array[mid])
      hi = mid - 1;
    else if (key > array[mid])
      lo = mid + 1；
    else
      return mid;
  }
  return -1;
}


//二叉树查找
//o(logn)
//
class Node
{
public:
  Node(int key, int val, int n){
    this.key = key;
    this.val = val;
    this.N = n;
    this.left = Null;
    this.right = Null;
  };
  ~Node() {
    if (left != Null) delete left;
    if (right != Null) delete right;
  };
public:
  int key;
  int value;
  Node *left, *right;
  int N;
};

Node *root = Null;
void size(Node *root) {
  if (root == Null) return 0;
  else return root->N;
}
void remove(Node *x) {
  x->right = Null;
  x->left = Null;
  delete x;
}
void put(int key, int val) {
  root = put(root, key ,val);
};
Node* put(Node* x, int key, int val) {
  if (x == Null) 
    return new Node(key, val, 1);
  if (key < x->key) 
    x->left = put(x->left, key, val);
  else if (key > x-> key)
    x->right = put(x->right, key, val);
  else
    x->val = val;
  x->N = size(x->left) + size(x->right) + 1;
  return x;    
}
int get(int key) {
  return get(root,key);
}
int get(Node* x, int key) {
  if (x == null) return -1;
  if (x->key > key) 
    return get(x->left, key);
  else if (x->key < key) 
    return get(x->right, key);
  else 
    return x->val;
}
Node* min(Node* x) {
  if (x == Null) return Null;
  if (x->left == Null) return x;
  else return min(x->left);
}
Node* deleteMin(Node* x) {
  if (x == Null) return Null;
  if (x->left == Null) {
    Node* tmp = x->right;
    x->right = Null;
    delete x;
    return tmp;
  }
  else {
   x->left = deleteMin(x->left);
   x->N = size(x->left) + size(x->right) + 1;
   return x;
 }
}
Node* delete(Node* x, int key) {
  if (x == Null) return Null;
  if (x->key > key)
    x->left = delete(x->left,key);
  else if (x->key < key)
    x->right = delete(x->right,key);
  else {
    Node* tmp = Null;
    if (x->left == Null) tmp = x->right;
    if (x->right == Null) tmp = x->left;
    if (tmp != Null) {
      remove(x);
      return tmp;
    }
    Node *t = x;
    x = min(x->right);
    x = new Node(x->key,x->val,1);
    x->right = deleteMin(t->right);
    x->left = t->left;
    remove(t);
  }
  x->N = size(x->left)+size(x->right)+1;
  return x;
}

