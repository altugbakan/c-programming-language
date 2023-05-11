#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXALLOC 2048U
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

static Header base;
static Header *freep = NULL;

int main(int argc, char **argv)
{
    unsigned size = argc == 1 ? NBYTES : atoi(argv[1]);

    char *p;

    if ((p = _malloc(size)) == NULL)
        return 1;

    printf("Allocated %d bytes\n", size);

    _free(p);

    printf("Freed %d bytes\n", size);
}

static Header *morecore(unsigned);

void *_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes > MAXALLOC)
    {
        fprintf(stderr, "malloc: can't allocate more than %u bytes\n", MAXALLOC);
        return NULL;
    }

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
    if (bp->s.size > MAXALLOC)
    {
        fprintf(stderr, "free: can't free more than %u bytes\n", MAXALLOC);
        return;
    }

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
