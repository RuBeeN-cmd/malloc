#include "ft_malloc.h"

void	test_size_malloc(size_t begin, size_t end)
{
	void	**ptr;

	ptr = malloc(end - begin);
	for (size_t i = begin; i < end; i += 1)
		ptr[i - begin] = malloc(i);
	for (size_t i = begin; i < end; i += 1)
		ft_printf("ptr[%d] = %p\n", i - begin, ptr[i - begin]);
	ft_printf("-------------------------\n");
	show_alloc_mem();
	for (size_t i = begin; i < end; i += 1)
		free(ptr[i - begin]);
	free(ptr);
	ft_printf("-------------------------\n");
	show_alloc_mem();
}

void	test_malloc()
{
	test_size_malloc(0, TINY_BLOCK_SIZE);
}

int main()
{
	test_malloc();
	// test_free();
	// test_realloc();
	return (0);
}