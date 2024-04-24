#include "ft_printf_fd.h"

int	ft_nbrlen_base(unsigned long long nbr, char *base)
{
	int	len;

	len = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= ft_strlen(base);
		len++;
	}
	return (len);
}

int	ft_is_base_wrong(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) <= 1)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

int	print_nbrbase_fd(unsigned long long nbr, int fd, char *base)
{
	int	len;

	len = ft_nbrlen_base(nbr, base);
	if (ft_is_base_wrong(base))
		return (0);
	if (nbr / ft_strlen(base))
	{
		print_nbrbase_fd(nbr / ft_strlen(base), fd, base);
	}
	ft_putchar_fd(base[nbr % ft_strlen(base)], fd);
	return (len);
}

int	print_addr_fd(unsigned long long addr, int fd)
{
	if (addr == 0)
		return (print_str_fd("(nil)", fd));
	print_str_fd("0x", 1);
	return (print_nbrbase_fd(addr, fd, "0123456789abcdef") + 2);
}
