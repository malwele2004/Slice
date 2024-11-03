#include <assert.h>
#include <stdlib.h>
#include<string.h>
#include "../def/Slice.h"

void Slice_Assert(long word_size, long capacity)
{
    assert(word_size >= 1 && capacity >= 1);
}

long Specialized_Get_Bytes(long word_size, long capacity) 
{
    return word_size * capacity;
}

long Get_Word_Size(long word_size, long capacity)
{
    Slice_Assert(word_size, capacity);
    return word_size;
}

long Get_Capacity(long word_size, long capacity)
{
    Slice_Assert(word_size, capacity);
    return capacity;
}

long Get_Bytes(long word_size, long capacity)
{
    Slice_Assert(word_size, capacity);
    return word_size * capacity;
}

int
_Slice_Ok(Slice_t *slice)
{
    return slice->origin != NULL;
}

int
_Slice_Delete(Slice_t *slice)
{
    if (!_Slice_Ok(slice)) return 0;
    free(slice->origin);
    slice->origin = NULL;
    return 1;
}

Slice_t
_Slice_New(long word_size, long capacity)
{
    return (Slice_t){.origin = malloc(Get_Bytes(word_size, capacity)), .len = 0, .cap = Get_Capacity(word_size, capacity)};
}

Slice_t
_Slice_Mangle(Slice_t *slice, long word_size, long capacity)
{
    if (!_Slice_Ok(slice)) return *slice;
    return (Slice_t){.origin = realloc(slice->origin, Get_Bytes(word_size, capacity)), .len = slice->len, .cap = Get_Capacity(word_size, capacity)};
}

// PRIVATE
void*
_Slice_Peek(Slice_t *slice, long word_size, long start, long n)
{
    if (!_Slice_Ok(slice) || start < 0 || n <= 0 || (start + n) > slice->len) return NULL; // Check read
    return slice->origin + Specialized_Get_Bytes(word_size, start);
}

// PRIVATE
int
_Slice_IO(Slice_t *slice, long word_size, long start, long n, void *res, int is_read)
{
    void *ptr; 
    if ((ptr = _Slice_Peek(slice, word_size, start, n))) {
        void *dest = (is_read) ? res : ptr; 
        void *src = (is_read) ? ptr : res ;
        memcpy(dest, src, Get_Bytes(word_size, n));
        return 1;
    }
    return 0;
}

int
_Slice_Write(Slice_t *slice, long word_size, long start, long n, void *src)
{
    return _Slice_IO(slice, word_size, start, n, src, 0);
}

int
_Slice_Read(Slice_t *slice, long word_size, long start, long n, void *dest)
{
    return _Slice_IO(slice, word_size, start, n, dest, 1);
}

int 
_Slice_Get(Slice_t *slice, long word_size, long idx, void *dest)
{
    return _Slice_Read(slice, word_size, idx, 1, dest);
}

int
_Slice_Put(Slice_t *slice, long word_size, long idx, void *src)
{
    return _Slice_Write(slice, word_size, idx, 1, src);
}

int
_Slice_Push(Slice_t *slice, long word_size, void *src)
{
    if (!_Slice_Ok(slice)) return 0;
    if (slice->len == slice->cap) // full
        {
            long new_cap = slice->cap * 2.0;
            Slice_t res; 
            if(!(res =_Slice_Mangle(slice, word_size, new_cap)).origin) return 0;
            *slice = res;
        }
    slice->len++;
    return _Slice_Put(slice, word_size, slice->len - 1, src);
}

int
_Slice_Pop(Slice_t *slice, long word_size, void *dest)
{
    if (!_Slice_Ok(slice) || slice->len <= 0) return 0;
    int r = _Slice_Get(slice, word_size, slice->len - 1, dest);
    slice->len--;
    return r;
}

long
_Slice_Iterate(Slice_t *slice, long word_size, long start, long n, int (*func) (long word_size, long index, void *res))
{
    for (long i = 0 ; i < n ; i++) 
        {
            if (!func(word_size, i, _Slice_Peek(slice, word_size, start + i , 1)))
                {
                    return i;
                }
        }
    return slice->len;
}