#include "../includes/malloc.h"

void		add_to_zone(t_hdr *pb)
{
	t_hdr	*p;

	p = g_alloc.cur->zone;
	while (p->s.next != g_alloc.cur->zone)
		p = p->s.next;
	swap_next(p, pb);
}

static void	defragment(t_hdr *pb, t_hdr *p)
{
	t_hdr	*next;

	next = pb->s.next;
	if ((pb + pb->s.size) == next && next->s.free)
	{
		pb->s.size += pb->s.next->s.size;
		pb ->s.next = pb->s.next->s.next;
	}
	if (p->s.free && (p + p->s.size) == pb)
	{
		p->s.size += pb->s.size;
		p->s.next = pb->s.next;
	}
}

void		free_large(t_hdr *large, t_hdr *p)
{
	while (p->s.next != large)
		p = p->s.next;
	p->s.next = large->s.next;
	if (large->s.next == large)
		g_alloc.cur->zone = NULL;
	else if (large == g_alloc.cur->zone)
		g_alloc.cur->zone = p->s.next;
	munmap(large, large->s.size);
	if (g_alloc.debug)
		printf_free_large(large);
}

void		free(void* pa)
{
	t_hdr	*pb;
	t_hdr	*p;

	pb = (t_hdr*)pa - 1;
	pb->s.free = true;
	p = select_current_zone(pb->s.size * sizeof(t_hdr));
	if (g_alloc.cur->type == LARGE)
	{
		free_large(pb, p);
		return ;
	}
	while (p->s.next != pb)
	{
		if (p->s.next == g_alloc.cur->zone)
		{
			swap_next(p, pb);
			return ;
		}
		p = p->s.next;
	}
	defragment(pb, p);
	if (g_alloc.debug)
		print_debug("free", pa);
}