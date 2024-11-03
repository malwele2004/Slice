#include <josiah/slice/include/Slice.h>
#include <stdio.h>

int print_all(long wsize, long index, void *res) 
{
    int *v = res;
    printf("=> %d\n", *v);
    return 1; // continue
}

int main()
{
    Slice_t slice = Slice_New(int, 4);
    
    Slice_Iterate(int, &slice, 0, slice.len, print_all);

    for (int i = 0; i < 100 ; i++)
        Slice_Push(int, &slice, &i);
    
    Slice_Iterate(int, &slice, 0, 5, print_all);
    
    Slice_Delete(&slice);

    return 0;
}
