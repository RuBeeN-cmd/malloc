#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int		ft_printf_fd(int fd, const char *str, ...);
int		ft_treat_char(int fd, const char *str, va_list args);
int		ft_treat_type(int fd, const char c, va_list args);
int		print_addr_fd(unsigned long long addr, int fd);
int		print_str_fd(char *s, int fd);
int		print_nbr_fd(int n, int fd);
int		print_unbr_fd(unsigned int n, int fd);
int		print_nbrbase_fd(unsigned long long nbr, int fd, char *base);
int		ft_is_base_wrong(char *base);
int		ft_nbrlen_base(unsigned long long nbr, char *base);

#endif
