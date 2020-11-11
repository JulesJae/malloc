#include "../includes/malloc.h"

static void		*cp_data(t_hdr *pb, void *ptr, size_t size)
{
	int		size_i;
	void	*ret;

	size_i = (pb->s.size - 1) * sizeof(t_hdr);
	if (size < SMALL)
		free(ptr);
	ret = malloc(size);
	if (ret == NULL)
		return NULL;
	if (size > SMALL)
	{
		ft_memcpy(ret, ptr, pb->s.size);
		free(ptr);
	} else
		ft_memcpy(ret, ptr, size_i);
	return ret;
}

void			*realloc(void* ptr, size_t size)
{
	t_hdr	*pb;
	t_hdr	*ret;

	if (!ptr)
		return malloc(size);
	pthread_mutex_lock(&g_alloc.memory_mutex);
	pb = (t_hdr*)ptr - 1;
	select_current_zone((pb->s.size - 1) * sizeof(t_hdr));
	if (!is_block(pb))
		return NULL;
	if (size <= (pb->s.size - 1) * sizeof(t_hdr) && size <= SMALL)
		return ptr;
	ret = cp_data(pb, ptr, size);
	pthread_mutex_unlock(&g_alloc.memory_mutex);
	return ret;
}
