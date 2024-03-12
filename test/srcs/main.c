#include "ft_malloc.h"

int main()
{
	void	*ptr = malloc(1);
	ft_printf("%p\n", ptr);
	free(ptr);
	return 0;
}
