#include "ft_printf_fd.h"

int	ft_treat_type(int fd, const char c, va_list args)
{
	char	*base;

	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		return (1);
	}
	else if (c == 's')
		return (print_str_fd(va_arg(args, char *), fd));
	else if (c == 'p')
		return (print_addr_fd(va_arg(args, unsigned long long), fd));
	else if (c == 'd' || c == 'i')
		return (print_nbr_fd(va_arg(args, int), fd));
	else if (c == 'u')
		return (print_unbr_fd(va_arg(args, unsigned int), fd));
	else if (c == 'x')
	{
		base = "0123456789abcdef";
		return (print_nbrbase_fd(va_arg(args, unsigned int), fd, base));
	}
	else if (c == 'X')
	{
		base = "0123456789ABCDEF";
		return (print_nbrbase_fd(va_arg(args, unsigned int), fd, base));
	}
	else if (c == '%')
	{
		ft_putchar_fd('%', fd);
		return (1);
	}
	return (0);
}

int	ft_treat_char(int fd, const char *str, va_list args)
{
	int	nb_char;
	int	i;

	nb_char = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i++], fd);
			nb_char++;
		}
		else
		{
			nb_char += ft_treat_type(fd, str[i + 1], args);
			i += 2;
		}
	}
	return (nb_char);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		nb_char;

	if (!str)
		return (-1);
	va_start(args, str);
	nb_char = ft_treat_char(fd, str, args);
	va_end(args);
	return (nb_char);
}