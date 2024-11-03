#ifndef D_SLICE_H
#define D_SLICE_H

typedef struct {
    void* origin;
    long len, cap;
} Slice_t ;

#endif
