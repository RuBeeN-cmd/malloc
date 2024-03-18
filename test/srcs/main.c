#include "ft_malloc.h"

int main()
{
	void	*ptr;
	for (int i = 0; i < 200; i++)
	{
		ptr = malloc(i % 100);
	}
	
	ptr = malloc(100);
	ptr = malloc(130);
	ptr = malloc(150);
	ptr = malloc(200);
	ptr = malloc(1000);
	ptr = malloc(8000);
	ptr = malloc(12000);
	ptr = malloc(16000);
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