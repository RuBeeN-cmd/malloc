#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
#include "ft_malloc.h"
# include "libft.h"

int		ft_printf(const char *str, ...);
int		ft_treat_char(const char *str, va_list args);
int		ft_treat_type(const char c, va_list args);
int		print_addr_fd(unsigned long long addr, int fd);
int		print_str_fd(char *s, int fd);
int		print_nbr_fd(int n, int fd);
int		print_unbr_fd(unsigned int n, int fd);
int		print_nbrbase_fd(unsigned long long nbr, int fd, char *base);
int		ft_is_base_wrong(char *base);
int		ft_nbrlen_base(unsigned long long nbr, char *base);

#endif
