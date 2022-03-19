/* mountain.c - Generate the memory mountain. */
/* $begin mountainmain */
#include <stdlib.h>
#include <stdio.h>
#include "fcyc2.h" /* K-best measurement timing routines */
#include "clock.h" /* routines to access the cycle counter */

#define MINBYTES (1 << 10)  /* Working set size ranges from 1 KB */
#define MAXBYTES (1 << 27)  /* ... up to 128 MB */
#define MAXSTRIDE 32        /* Strides range from 1 to 32 */
#define STRIDESTRIDE 2      /* increment stride by this amount each time */
#define MAXELEMS MAXBYTES/sizeof(int) 

int data[MAXELEMS];         /* The array we'll be traversing */

/* $end mountainmain */
void init_data(int *data, int n);
void test(int elems, int stride);
double run(int size, int stride, double Mhz);

/* $begin mountainmain */
int main()
{
    int size;        /* Working set size (in bytes) */
    int stride;      /* Stride (in array elements) */
    double Mhz;      /* Clock frequency */

    init_data(data, MAXELEMS); /* Initialize each element in data to 1 */
    Mhz = mhz(0);              /* Estimate the clock frequency */
/* $end mountainmain */
    /* Not shown in the text */
    printf("Clock frequency is approx. %.1f MHz\n", Mhz);
    printf("Memory mountain (MB/sec)\n");

    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE)
	printf("s%d\t", stride);
    printf("\n");

    /* $begin mountainmain */
    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) {
        /* $end mountainmain */
	    /* Not shown in the text */
	    if (size > (1 << 20))
	        printf("%dm\t", size / (1 << 20));
	    else
	        printf("%dk\t", size / 1024);

        /* $begin mountainmain */
	    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
	        printf("%.0f\t", run(size, stride, Mhz));
	    }
	    printf("\n");
    }
    exit(0);
}
/* $end mountainmain */

/* init_data - initializes the array */
void init_data(int *data, int n)
{
    int i;

    for (i = 0; i < n; i++)
	data[i] = 1;
}

/* $begin mountainfuns */
//void test(int elems, int stride) /* The test function */
//{
//    int i, result = 0; 
//    volatile int sink; 
//
//    for (i = 0; i < elems; i += stride)
//	result += data[i];
//    sink = result; /* So compiler doesn't optimize away the loop */
//}
//


/* test - Iterate over first "elems" elements of array "data" with
 *        stride of "stride", using 4x4 loop unrolling.
 */
/*
void test(int elems, int stride)
{
    long i, sx2 = stride*2, sx3 = stride*3, sx4 = stride*4;

    long sum;
    long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    long length = elems;
    long limit = length - sx4;

    // Combine 4 elements at a time
    for (i = 0; i < limit; i += sx4) {
        acc0 = acc0 + data[i];
        acc1 = acc1 + data[i+stride];
        acc2 = acc2 + data[i+sx2];
        acc3 = acc3 + data[i+sx3];
    }

    // Finish any remaining elements
    for (; i < length; i += stride) {
        acc0 = acc0 + data[i];
    }
    sum=((acc0 + acc1) + (acc2 + acc3));
}
*/

/* $begin mountainfuns */
/* test - Iterate over first "elems" elements of array "data" with
 *        stride of "stride", using 32x32 loop unrolling.
 */

void test(int elems, int stride)
{
    long i, sx2 = stride*2, sx3 = stride*3, sx4 = stride*4;
    long sx5 = stride*5,   sx6 = stride*6, sx7 = stride*7, sx8 = stride*8;
    long sx9 = stride*9,   sx10 = stride*10, sx11 = stride*11, sx12 = stride*12;
    long sx13 = stride*13, sx14 = stride*14, sx15 = stride*15, sx16 = stride*16;
    long sx17 = stride*17, sx18 = stride*18, sx19 = stride*19, sx20 = stride*20;
    long sx21 = stride*21, sx22 = stride*22, sx23 = stride*23, sx24 = stride*24;
    long sx25 = stride*25, sx26 = stride*26, sx27 = stride*27, sx28 = stride*28;
    long sx29 = stride*29, sx30 = stride*30, sx31 = stride*31, sx32 = stride*32;

    long sum;
    long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    long acc4 = 0, acc5 = 0, acc6 = 0, acc7 = 0;
    long acc8 = 0, acc9 = 0, acc10 = 0, acc11 = 0;
    long acc12 = 0, acc13 = 0, acc14 = 0, acc15 = 0;
    long acc16 = 0, acc17 = 0, acc18 = 0, acc19 = 0;
    long acc20 = 0, acc21 = 0, acc22 = 0, acc23 = 0;
    long acc24 = 0, acc25 = 0, acc26 = 0, acc27 = 0;
    long acc28 = 0, acc29 = 0, acc30 = 0, acc31 = 0;
    long length = elems;
    long limit = length - sx32;

    // Combine 32 elements at a time
    for (i = 0; i < limit; i += sx32) {
        acc0 = acc0 + data[i];
        acc1 = acc1 + data[i+stride];
        acc2 = acc2 + data[i+sx2];
        acc3 = acc3 + data[i+sx3];
        acc4 = acc4 + data[i+sx4];
        acc5 = acc5 + data[i+sx5];
        acc6 = acc6 + data[i+sx6];
        acc7 = acc7 + data[i+sx7];
        acc8 = acc8 + data[i+sx8];
        acc9 = acc9 + data[i+sx9];
        acc10 = acc10 + data[i+sx10];
        acc11 = acc11 + data[i+sx11];
        acc12 = acc12 + data[i+sx12];
        acc13 = acc13 + data[i+sx13];
        acc14 = acc14 + data[i+sx14];
        acc15 = acc15 + data[i+sx15];
        acc16 = acc16 + data[i+sx16];
        acc17 = acc17 + data[i+sx17];
        acc18 = acc18 + data[i+sx18];
        acc19 = acc19 + data[i+sx19];
        acc20 = acc20 + data[i+sx20];
        acc21 = acc21 + data[i+sx21];
        acc22 = acc22 + data[i+sx22];
        acc23 = acc23 + data[i+sx23];
        acc24 = acc24 + data[i+sx24];
        acc25 = acc25 + data[i+sx25];
        acc26 = acc26 + data[i+sx26];
        acc27 = acc27 + data[i+sx27];
        acc28 = acc28 + data[i+sx28];
        acc29 = acc29 + data[i+sx29];
        acc30 = acc30 + data[i+sx30];
        acc31 = acc31 + data[i+sx31];
    }

    //Finish any remaining elements
    for (; i < length; i += stride) {
        acc0 = acc0 + data[i];
    }
    //sum=((acc0 + acc1) + (acc2 + acc3));
    sum=((acc0 + acc1) + (acc2 + acc3) + (acc4 + acc5) + (acc6 + acc7) + (acc8 + acc9) + (acc10 + acc11) + (acc12 + acc13) + (acc14 + acc15) +(acc16 + acc17) + (acc18 + acc19) +(acc20 + acc21) + (acc22 + acc23) +(acc24 + acc25) + (acc26 + acc27) +(acc28 + acc29) + (acc30 + acc31));
}

/* Run test(elems, stride) and return read throughput (MB/s) */
double run(int size, int stride, double Mhz)
{
    double cycles;
    int elems = size / sizeof(int); 

    test(elems, stride);                     /* warm up the cache */
    cycles = fcyc2(test, elems, stride, 0);  /* call test(elems,stride) */
    return (size / stride) / (cycles / Mhz); /* convert cycles to MB/s */
}
/* $end mountainfuns */


