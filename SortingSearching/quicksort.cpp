#include <iostream>
using namespace std;

void printArray(int* a, int len)
{
    for (int i = 0; i <= len; ++i)
        cout << " " << a[i];
    cout << endl;
}
int partition(int* a, int lo, int hi,int count)
{
    int pivot = a[lo];
    int i = lo;
    int j = hi+1;
    while (true) {
        /*while (a[++i] < pivot)
        {
            if (i==hi) 
                break;
        }
        while (a[--j] > pivot)
        {
            if (j==lo) 
            {
                break;
            }
        }*/
        while (a[++i] < pivot)
            if (i==hi) break;
        while (a[--j] > pivot)
            if (j==lo) break;
        if (i >= j)
            break;
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    int tmp = a[lo];
    a[lo] = a[j];
    a[j] = tmp;
    return j;
}

void quicksort(int* a, int lo, int hi, int count)
{
    if (hi <= lo)
        return;
    int p = partition(a, lo, hi,count);
     
    quicksort(a, lo, p-1,count);
    quicksort(a, p+1,hi,count);
}

void quicksort_middle(int* a, int lo, int hi, int count)
{
    if (lo >= hi)
        return;
    int mid = lo + (hi-lo)/2;
    int pivot = a[mid];
    int i = lo;
    int j = hi;
    
    while (true) {
        while (a[i] < pivot) {
            ++i;
        }
        while (a[j] > pivot) {
            --j;
        }
        if (i >= j)
            break;
        // swap i and j items
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        ++i;
        --j;
    }
    
    quicksort_middle(a, lo, j, count);
    quicksort_middle(a, j+1,hi, count);
}
void swap(int* a, int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
void quicksort_3way(int* a, int lo, int hi, int count)
{
    if (hi <= lo)
        return;
    int i = lo;
    int lt = lo;
    int gt = hi;
    int pivot = a[lo];
    printArray(a,count);
    while (i <= gt) {
        if (a[i] < pivot)
            swap(a,lt++,i++);
        if (a[i] > pivot)
            swap(a, i, gt--);
        else 
            ++i;
        printArray(a,count);
    }
    quicksort_3way(a,lo,lt-1,count);
    quicksort_3way(a,gt+1,hi,count);
}
void main()
{
    //int input[] = {1, 12, 5, 26, 7, 14, 3, 7, 2};
    int input[] = {18,2,23,23,18,23,2,18,18,23,2,18};
    quicksort_3way(input,0,sizeof(input)/sizeof(input[0])-1,sizeof(input)/sizeof(input[0])-1);
    printArray(input,sizeof(input)/sizeof(input[0])-1);
    //quicksort(input,0,sizeof(input)/sizeof(input[0])-1,sizeof(input)/sizeof(input[0])-1);
    quicksort_middle(input,0,sizeof(input)/sizeof(input[0])-1,sizeof(input)/sizeof(input[0])-1);
    cout << "Size of input: " << sizeof(input) << endl;
    cout << "Number of items in array is: " << sizeof(input)/sizeof(input[0]) << endl;
}