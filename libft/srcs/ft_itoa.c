/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:25:02 by rrollin           #+#    #+#             */
/*   Updated: 2022/04/02 15:13:09 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nbr_len(long long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	else if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = n;
	str = malloc(sizeof(char) * (get_nbr_len(nbr) + 1));
	if (!str)
		return (NULL);
	i = get_nbr_len(nbr);
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
	}
	else if (!nbr)
		str[0] = '0';
	str[i] = 0;
	while (nbr)
	{
		str[--i] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (str);
}
