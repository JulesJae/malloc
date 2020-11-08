#include "../includes/malloc.h"

static void	print_zone(t_zinfos *z)
{
	if (z->type == TINY)
		ft_printf("TINY :\t%p : {green}%ld octets{eoc}\n", z->zone, z->size);
	else if (z->type == SMALL)
		ft_printf("SMALL : %p : {green}%ld octets{eoc}\n", z->zone, z->size);
	else
		ft_printf("LARGE : %p : {green}%ld octets{eoc}\n", z->zone, z->size);
}

static int	show_alloc(t_zinfos *z)
{
	int		bytes;
	size_t	size;
	t_hdr	*p;

	print_zone(z);
	bytes = 0;
	p = z->zone;
	while (true)
	{
		size = (z->type == LARGE) ?  p->s.size 
			: (int)(p->s.size * sizeof(t_hdr));
		if (!p->s.free)
		{
			bytes += size;
			ft_printf("\t{red}%p = %p : %ld octets{eoc}\n"
				, p, p + p->s.size, size);
		} else 
			ft_printf("\t{cyan}%p = %p : %ld octets{eoc}\n"
				, p, p + p->s.size, size);
		p = p->s.next;
		if (p == z->zone)
			return bytes;
	}
}
void		print_debug(char *type, void *p)
{
	ft_printf("\n--- %s at %p ---\n\n", type, p);
	show_alloc(g_alloc.cur);
	ft_printf("\n----------------------\n\n");
}

void		printf_free_large(void *p)
{
	ft_printf("\n--- large block freed at %p ---\n", p);
	ft_printf("----------------------\n\n");
}


void		show_alloc_mem()
{
	int		bytes;

	if (g_alloc.tiny.zone)
		bytes = show_alloc(&g_alloc.tiny);
	if (g_alloc.small.zone)
		bytes += show_alloc(&g_alloc.small);
	if (g_alloc.large.zone)
		bytes += show_alloc(&g_alloc.large);
	ft_printf(
		"mem alloc/free/total:\n\t{red}%ld{eoc}/{cyan}%ld{eoc}/{green}%ld{eoc} bytes\n"
	, bytes, g_alloc.bytes - bytes, g_alloc.bytes);
}