#include "ft_malloc.h"

t_page	*g_page = NULL;

void	free(void *ptr)
{
	munmap(ptr, 0);
}

void	*malloc(size_t size)
{
	if (!g_page)
		preload_page();
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, 0x20 | MAP_PRIVATE, -1, 0);
	return (ptr);
}