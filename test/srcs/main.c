#include "ft_malloc.h"

void	test_size_malloc(size_t begin, size_t end, size_t step)
{
	void	**ptr;

	ptr = malloc((end - begin + 1) / step * sizeof(void *));
	for (size_t i = begin; i <= end; i += step)
		ptr[(i - begin) / step] = malloc(i);
	ft_printf("-------------------------\n");
	show_alloc_mem();
	for (size_t i = begin; i <= end; i += step)
		free(ptr[(i - begin) / step]);
	free(ptr);
	ft_printf("-------------------------\n");
	show_alloc_mem();
}

void	test_malloc()
{
	test_size_malloc(1, TINY_BLOCK_SIZE, 5);
	test_size_malloc(TINY_BLOCK_SIZE + 1, SMALL_BLOCK_SIZE, 20);
}

void	test_realloc()
{
	void	*ptr;

	ptr = malloc(1);
	ft_printf("-------------------------\n");
	show_alloc_mem();
	ptr = realloc(ptr, 10);
	ft_printf("-------------------------\n");
	show_alloc_mem();
	ptr = realloc(ptr, 1000);
	ft_printf("-------------------------\n");
	show_alloc_mem();
	ptr = realloc(ptr, 10000);
	ft_printf("-------------------------\n");
	show_alloc_mem();
	ptr = realloc(ptr, 0);
	ft_printf("-------------------------\n");
	show_alloc_mem();
}

int main()
{
	// test_malloc();
	test_realloc();
	return (0);
}