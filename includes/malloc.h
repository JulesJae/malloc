#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <unistd.h>
#include <pthread.h>
# include "../libft/includes/ft_printf.h"

# define N_ALLOCS 100

# define TINY 512
# define SMALL 4096
# define LARGE 4097

typedef union			u_hdr
{
	struct
	{
		union u_hdr		*next;
		int				size;
		bool			free;
	}					s;
	long 				x[2];
}						t_hdr;

typedef struct			s_zinfos
{
	int					type;
	unsigned long		size;
	t_hdr				*zone;
}						t_zinfos;

typedef struct			s_alloc
{
	t_zinfos			tiny;
	t_zinfos			small;
	t_zinfos			large;
	t_zinfos			*cur;
	int					debug;
	long				bytes;
	pthread_mutex_t		memory_mutex;
}						t_alloc;

t_alloc					g_alloc;

void					initialize_g();
t_hdr					*select_current_zone(size_t size);
int						calcul_size(int, bool);
void					show_alloc_mem();
void					print_debug(char *type, void *p);
void					printf_free_large(void *p);
void					swap_next(t_hdr *pprec, t_hdr *p);
void					add_to_zone(t_hdr *pb);
t_hdr					*create_block(size_t size, bool large);
t_hdr					*find_previous(t_hdr *p, t_hdr *next);
bool					is_block(t_hdr *pb);
void					*malloc(size_t size);
void					*realloc(void* ptr, size_t size);
void					free(void* pa);

#endif