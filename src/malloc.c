#include "../includes/malloc.h"

static t_hdr	*create_and_add_zone(bool create)
{
	t_hdr	*pr;

	pr = create_block(g_alloc.cur->type, false);
	if (pr == NULL)
		return NULL;
	if (create)
		g_alloc.cur->zone = pr;
	else
		add_to_zone(pr);
	return g_alloc.cur->zone;
}

static void		*create_large_block(size_t size)
{
	t_hdr	*pl;
	t_hdr	*p;

	pl = create_block(size, true);
	if (pl == NULL)
		return NULL;
	p = g_alloc.large.zone;
	if (p == NULL)
	{
		g_alloc.large.zone = pl;
		pl->s.next = pl;
	} else
	{
		while(p->s.next != g_alloc.large.zone)
			p = p->s.next;
		swap_next(p, pl);
	}
	if (g_alloc.debug)
		print_debug("allocation", pl);
	return (void*)(pl + 1);
}

static void		*find_available_bloc(t_hdr *pprec, t_hdr *p, int size)
{
	while (true)
	{
		if(p->s.free && p->s.size >= size)
		{
			pprec = p;
			if (p->s.size > size)
			{
				p->s.size -= size;
				p += p->s.size;
				p->s.size = size;
			}
			p->s.free = false;
			swap_next(pprec, p);
			if (g_alloc.debug)
				print_debug("allocation", p);
			return ((void*)p + sizeof(t_hdr));
		}
		if (p == g_alloc.cur->zone)
			if ((p = create_and_add_zone(false)) == NULL)
				return NULL;
		pprec = p;
		p = p->s.next;
	}
}

void			*malloc(size_t size)
{
	t_hdr		*p;
	t_hdr		*pprec;
	t_hdr		*ret;

	if (g_alloc.cur == NULL)
		initialize_g();
	pthread_mutex_lock(&g_alloc.memory_mutex);
	pprec = select_current_zone(size);
	if (size > SMALL)
		return create_large_block(size);
	if (pprec == NULL)
		pprec = create_and_add_zone(true);
	size = (size + sizeof(t_hdr) - 1) / sizeof(t_hdr) + 1;
	p = pprec->s.next;
	ret = find_available_bloc(pprec, p, size);
	pthread_mutex_unlock(&g_alloc.memory_mutex);
	return ret;
}
