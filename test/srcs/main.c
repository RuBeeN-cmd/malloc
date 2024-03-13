#include "ft_malloc.h"

int main()
{
	void	*ptr = malloc(1);
	ft_printf("ptr = %p\n", ptr);
	return 0;
}

/*

malloc(24) block size: 32
malloc(40) block size: 48
malloc(56) block size: 64
malloc(72) block size: 80
malloc(104) block size: 112

*/