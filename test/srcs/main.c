#include "ft_malloc.h"

int main()
{
	void	*ptr;
	ptr = malloc(100);
	ft_printf("ptr = %p\n", ptr);
	show_alloc_mem();
	free(ptr);
	ft_printf("\n\n\n");
	show_alloc_mem();
	return 0;
}