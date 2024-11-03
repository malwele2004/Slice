#include "../def/Slice.h"
#ifndef I_SLICE_H
#define I_SLICE_H

extern int _Slice_Ok(Slice_t*);
#define Slice_Ok(slice) _Slice_Ok(slice)

extern Slice_t _Slice_New(long, long);
#define Slice_New(Type, capacity) _Slice_New(sizeof(Type), capacity)

extern int _Slice_Delete(Slice_t*);
#define Slice_Delete(slice) _Slice_Delete(slice)

extern Slice_t _Slice_Mangle(Slice_t*, long, long);
#define Slice_Mangle(Type, slice, new_capacity) _Slice_Mangle(slice, sizeof(Type), new_capacity)

extern int
_Slice_Read(Slice_t *slice, long word_size, long start, long n, void *dest);
#define Slice_Read(Type, slice, start, n, dest) _Slice_Read(slice, sizeof(Type), start, n, dest)

extern
int
_Slice_Write(Slice_t *slice, long word_size, long start, long n, void *src);
#define Slice_Write(Type, slice, start, n, src) _Slice_Write(slice, sizeof(Type), start, n, src)

extern 
int 
_Slice_Get(Slice_t *slice, long word_size, long idx, void *dest);
#define Slice_Get(Type, slice, idx, dest) _Slice_Get(slice, sizeof(Type), idx, dest)

extern int
_Slice_Put(Slice_t *slice, long word_size, long idx, void *src);
#define Slice_Put(Type, slice, idx, src) _Slice_Put(slice, sizeof(Type), idx, src)

extern int
_Slice_Push(Slice_t *slice, long word_size, void *src);
#define Slice_Push(Type, slice, src) _Slice_Push(slice, sizeof(Type), src)

extern
int
_Slice_Pop(Slice_t *slice, long word_size, void *dest);
#define Slice_Pop(Type, slice, dest) _Slice_Pop(slice, sizeof(Type), dest)

extern 
long
_Slice_Iterate(Slice_t *slice, long word_size, long start, long n, int (*func) (long word_size, long index, void *res));
#define Slice_Iterate(Type, slice, start, n, FUNC) _Slice_Iterate(slice, sizeof(Type), start, n, FUNC)

#endif
