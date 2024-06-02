#pragma once

typedef short int _16bits;
typedef int _32bits;

struct _4bits {
    bool a, b, c, d;
};
struct _8bits{
    bool
        cwr,
        ece,
        urg,
        ack,
        psh,
        rst,
        syn,
        fin;
};
