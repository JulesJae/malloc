#include "../includes/malloc.h"

static void		*cp_data(t_hdr *pb, void *ptr, size_t size)
{
	int		size_i;
	void	*ret;

	size_i = (pb->s.size - 1) * sizeof(t_hdr);
	free(ptr);
	show_alloc_mem();
	ret = malloc(size);
	show_alloc_mem();
	if (ret == NULL)
		return NULL;
	ft_printf("cp_data ret = %p, sizw = %d, sizedispo = %d\n", ret, size, ((t_hdr*)ret - 1)->s.size * sizeof(t_hdr));
	ft_memcpy(ret, ptr, size_i);
	return ret;
}

void			*realloc(void* ptr, size_t size)
{
	t_hdr	*pb;

	if (!ptr)
		return malloc(size);
	pb = ((t_hdr*)ptr - 1);
	ft_printf("ptr = %p, size = %d, size dispo = %d\n", ptr, size, (pb->s.size - 1) * sizeof(t_hdr));
	if (size <= (pb->s.size - 1) * sizeof(t_hdr))
		return ptr;
	return cp_data(pb, ptr, size);
}