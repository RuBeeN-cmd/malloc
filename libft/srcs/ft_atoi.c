/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:33:19 by rrollin           #+#    #+#             */
/*   Updated: 2022/04/04 13:45:22 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long long		nb;
	int				coef;
	char			*str;

	nb = 0;
	coef = 1;
	str = (char *) nptr;
	while (*str == ' ' || (*str <= '\r' && *str >= '\t'))
		str++;
	if (*str == '-')
	{
		str++;
		coef = -coef;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (nb > (nb + *str - '0') * 10)
			return (-(coef > 0));
		nb *= 10;
		nb += *str++ - '0';
	}
	return (nb * coef);
}
