#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
// #include <stdlib.h>
#include <string.h>
#include "libft/includes/ft_printf.h"
#include "includes/malloc.h"
# define NALLOUE 1024
# define M (1024 * 1024)

void test_malloc_tiny()
{
    char *a, *b, *c, *d, *e, *f, *g, *h;

    a = malloc(10);
    b = malloc(20);
    c = malloc(30);
    d = malloc(40);
    e = malloc(50);
    f = malloc(60);
    g = malloc(70);
    h = malloc(80);
    ft_strcpy(a, "coucou coco");
    free(b);
    free(d);
    free(f);
    free(h);
    free(c);
    ft_printf("a = %s\n", a);
    a = realloc(a, 688);
    // free(a);
    ft_printf("a = %s\n", a);
    show_alloc_mem();
}

void test_3blocksandRealloc()
{
    int i =0;
    char *a;

    while (i < 301)
    {
        a =malloc(512);
        i++;
    }
    show_alloc_mem();
    ft_printf("toto\n");
    free(a);
    a = malloc(16);
    show_alloc_mem();
}

void test_realloc_first_pos()
{
    char *a, *b, *c;

    a = malloc(10);
    b = malloc(20);
    c = malloc(40);
    free(b);
    a = realloc(a, 20);
    show_alloc_mem();
}

void test_largeBlockRealloc()
{
    char *a, *b, *c, *d;

    a = malloc(5099);
    b = malloc(19450);
    c = malloc(25340);
    d = malloc(38490);
    a = realloc(a, 10);
    free(b);
    a = realloc(a, 56492);
    show_alloc_mem();
}

void    tes()
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        free(addr);
        i++;
    }
    show_alloc_mem();
}

void test2()
{
    char *a, *b, *c;

    a = malloc(16 * M);
    ft_strcpy(a, "Bonjours\n");
    ft_printf("a = %s\n", a);
    b = (char*)malloc(16*M);
    c = realloc(a, 128 * M);
    c[127*M] = 42;
    ft_printf("c = %s\n", c);
}

void test3()
{
    char *a;

    a = malloc(16);
    free(NULL);
    ft_printf("coucou\n");
    free((void*)a + 5);
    if ((realloc((void*)a + 5, 10)) == NULL)
        ft_printf("bonjour\n");
}

void test4()
{
    malloc(1024);
    malloc(1024 * 32);
    malloc(1024 * 1024);
    malloc(1024 * 1024 * 16);
    malloc(1024 * 1024 * 128);
    show_alloc_mem();
}

int main()
{
    // test_malloc_tiny();
    // test_3blocksandRealloc();
    // test_realloc_first_pos();
    // test_largeBlockRealloc();
    // tes();
    // test2();
    // test3();
    test4();
    return (0);
}