#include "../includes/malloc.h"

t_hdr			*create_block(size_t size, bool large)
{
	void	*pa;
	t_hdr	*pb;

	size = calcul_size(size, large);
	pa = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE
		, -1, 0);
	if (pa == (void*)-1)
		return NULL;
	g_alloc.bytes += size;
	g_alloc.cur->size += size;
	pb = (t_hdr*)pa;
	pb->s.free = (large) ? false : true;
	pb->s.size = (large) ? size : size / sizeof(t_hdr);
	pb->s.next = pb;
	return pb;
}