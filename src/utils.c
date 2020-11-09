#include "../includes/malloc.h"

void		initialize_g()
{
	char	*debug;

	g_alloc.tiny.type = TINY;
	g_alloc.tiny.zone = NULL;
	g_alloc.tiny.size = 0;
	g_alloc.small.type = SMALL;
	g_alloc.small.zone = NULL;
	g_alloc.small.size = 0;
	g_alloc.large.type = LARGE;
	g_alloc.large.zone = NULL;
	g_alloc.large.size = 0;
	g_alloc.bytes = 0;
	debug = getenv("MallocDebug");
	g_alloc.debug = debug ? ft_atoi(debug) : 0;
}

t_hdr		*select_current_zone(size_t size)
{
	if (size <= TINY)
		g_alloc.cur = &g_alloc.tiny;
	else if (size <= SMALL)
		g_alloc.cur = &g_alloc.small;
	else if(size > SMALL)
		g_alloc.cur = &g_alloc.large;
	return g_alloc.cur->zone;
}

int			calcul_size(int size, bool large)
{
	int		size_b;
	int		size_z;

	size_b = size + sizeof(t_hdr);
	if (large == false)
		size_b = size_b * N_ALLOCS;
	size_z = (size_b - 1) / getpagesize() + 1;
	return size_z * getpagesize();
}

void		swap_next(t_hdr *pprec, t_hdr *p)
{
	t_hdr	*tmp;

	tmp = pprec->s.next;
	pprec->s.next = p;
	p->s.next = tmp;
}
