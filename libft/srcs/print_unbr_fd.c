#include "ft_printf_fd.h"

int	print_unbr_fd(unsigned long n, int fd)
{
	int	len;

	len = 0;
	if (n / 10)
		len += print_unbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
	return (1 + len);
}
