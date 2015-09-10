#include <iostream>

void counting_sort(int* in, int inlen, int* out, int* tmp, int tmplen)
{
    // initialize the temporary array, this holds all counts, from 0 to 9
    for (int i = 0; i < tmplen; ++i)
        tmp[i] = 0;
    // count occurance of each item in 'in' and update counter in tmp array
    for (int i = 0; i < inlen; ++i)
        tmp[in[i]] += 1;
    // now accumulate all the counts, this array now has:
    // 1. tmp[i] --> Number of items that are less than tmp[i+1]
    // 2. tmp[i] --> Number of items that are less than or equal to what is stored in in[i]
    // 3. tmp[i+1]-tmp[i] : Number of items that are duplicates.
    for (int i = 1; i < tmplen; ++i)
        tmp[i] += tmp[i-1];
    // Now starting from the last item, do the following:
    // get the value stored at in[i], get the count of this value in th temp array.
    // the (count-1) position in in array gives the sorted location of this item.
    for (int i = inlen-1; i >= 0; --i)
    {
        // get the item from the in array
        int item = in[i];
        // get the cummulative count of this item in the tmp array
        int count = tmp[item];
        // this count now represents the index in the sorted array of the in[i] item
        out[count-1] = in[i];
        --tmp[item];
    }
}
void main()
{
    int in[] = {1, 4, 1, 2, 7, 5, 2};
    int* out = new int[sizeof(in)/sizeof(in[0])];
    memset(out,0,sizeof(in));
    int tmp[10];
    counting_sort(in,sizeof(in)/sizeof(in[0]),out,tmp,10);
}