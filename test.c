#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include "libft/includes/ft_printf.h"
# define NALLOUE 1024

extern char **environ;

int main()
{
    char *a = realloc(NULL, 10);
    char *b = malloc(12);

    strcpy(a, "boooooooooonnnnnnnnnnnnnjjjjjjjjjjjoooooooouuuuuuuur");
    ft_printf("a = %s\n", a);
    int i = 0;
    ft_printf("env path = %s\n", getenv("test"));
    return (0);
}