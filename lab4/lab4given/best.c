#include <stdio.h>
#include <unistd.h>

#include "mem.h"

typedef long Align;

union header
{
   struct
   {
      union header *ptr;
      size_t size;
   } s;
   Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

static Header *morecore(size_t);

void *lab_malloc(size_t nbytes)
{
   Header *p, *prevp;
   Header *minp = NULL, *minprevp = NULL;
   size_t nunits;
   int min_size = 0;

   nunits = (nbytes + sizeof(Header) - 1)/ sizeof(Header) + 1;
   if ((prevp = freep) == NULL)
   {
      base.s.ptr = freep = prevp = &base;
      base.s.size = 0;
   }
   for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
   {
      if (p->s.size >= nunits)
      {
         if (p->s.size == nunits)
         {
            prevp->s.ptr = p->s.ptr;
            freep = prevp;
            return (void *)(p + 1);
         }
         else
         {
             if (minp == NULL || p->s.size < min_size) {
                minp = p;
                minprevp = prevp;
                min_size = minp->s.size;
             }
         }
      }
      if (p == freep)
      {
        if (minp != NULL) {
            minp->s.size -= nunits;
            minp += minp ->s.size;
            minp->s.size = nunits;
            freep = minprevp;
            return (void *)(minp + 1);
        }
        if ((p = morecore(nunits)) == NULL)
        {
           return NULL;
        }
      }
   }
}

#define NALLOC 1024
static Header *morecore(size_t nu)
{
   char *cp;
   Header *up;

   if (nu < NALLOC)
   {
      nu = NALLOC;
   }
   cp = sbrk(nu * sizeof(Header));
   if (cp == (char *) -1)
   {
      return NULL;
   }
   up = (Header *) cp;
   up->s.size = nu;
   lab_free((void *)(up + 1));
   return freep;
}

void lab_free(void *ap)
{
   Header *bp, *p;

   bp = (Header *)ap - 1;
   for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
   {
      if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      {
         break;
      }
   }
   if (bp + bp->s.size == p->s.ptr)
   {
      bp->s.size += p->s.ptr->s.size;
      bp->s.ptr = p->s.ptr->s.ptr;
   }
   else
   {
      bp->s.ptr = p->s.ptr;
   }
   if (p + p->s.size == bp)
   {
      p->s.size += bp->s.size;
      p->s.ptr = bp->s.ptr;
   }
   else
   {
      p->s.ptr = bp;
   }
   freep = p;
}

