// 2_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и 
// B[0..m-1]. n >> m. Найдите их пересечение.



#include <iostream>
using namespace std;
int binarySearch(int arr[], int l, int r, int x)
{
     int end_of_range = r;
  while (l < r) 
  {
    int mid = (l + r) / 2;
    if (arr[mid] < x) 
    {
      l = mid + 1;
    } 
    else 
    {
      r = mid;
    }
  }
  return (l == end_of_range || arr[l] != x) ? -1 : l;
}
int exponentialSearch(int arr[], int n, int x, int &start)
{
    if (arr[start] == x)
        return start;
    int i = start + 1;
    while (i < n && arr[i] <= x)
        i = i*2;
    return binarySearch(arr, i/2, min(n,i), x);
}


void intersection(int*a, int* b, int n, int m)
{
   
    int start = 0;
    for(int i = 0; i < m; i++)
    {
     int tmpi = exponentialSearch(a,n,b[i],start);
     if (tmpi != -1)
     {
        start = tmpi;
   
       cout << a[tmpi] << " ";
     }
     
    }
   
}
int main()
{
    int n,m;
    cin >> n >> m;
    int *a = new int [n];
    for(int i = 0; i < n; i++)
    {
         cin >> a[i];
    }
    int *b = new int [m];
      for(int i = 0; i < m; i++)
    {
         cin >> b[i];
    }
    intersection(a,b,n,m);  
    delete []a;
    delete []b;
    return 0;
}