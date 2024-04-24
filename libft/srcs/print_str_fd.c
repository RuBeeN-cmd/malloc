#include "ft_printf_fd.h"

int	print_str_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
