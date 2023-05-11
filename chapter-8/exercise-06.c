#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NBYTES 5

typedef long Align;

union header
{
    struct
    {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

void *_malloc(unsigned);
void _free(void *);
void *_calloc(unsigned, unsigned);

static Header base;
static Header *freep = NULL;

int main(int argc, char **argv)
{
    unsigned size = argc == 1 ? NBYTES : atoi(argv[1]);

    char *p = _calloc(size, sizeof(char));

    printf("Allocated %d bytes with values: ", size);

    for (int i = 0; i < size; ++i)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    _free(p);
}

static Header *morecore(unsigned);

void *_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;

            return (void *)(p + 1);
        }

        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

#define NALLOC 1024

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *)-1)
        return NULL;

    up = (Header *)cp;
    up->s.size = nu;
    _free((void *)(up + 1));

    return freep;
}

void _free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;

    freep = p;
}

void *_calloc(unsigned n, unsigned size)
{
    unsigned nbytes = n * size;
    char *p, *q;

    if ((p = q = _malloc(nbytes)) != NULL)
        while (nbytes--)
            *p++ = 0;

    return q;
}