#include "ft_malloc.h"

int main()
{
	void	*ptr;
	ptr = malloc(100);
	ft_printf("ptr = %p\n", ptr);
	free(ptr);
	return 0;
}