#include "ft_printf.h"

int	print_nbr_fd(int n, int fd)
{
	long	nbr;
	int		len;

	nbr = n;
	len = 0;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		len++;
		nbr = -nbr;
	}
	if (nbr / 10)
		len += print_nbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
	return (1 + len);
}
