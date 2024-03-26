/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:09:13 by rrollin           #+#    #+#             */
/*   Updated: 2022/04/04 12:02:14 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	len;
	char	*d;
	char	*s;

	if (!dest && !src)
		return (dest);
	d = (char *) dest;
	s = (char *) src;
	if (s > d)
	{
		len = n;
		n++;
		while (--n)
			d[len - n] = s[len - n];
	}
	else
		while (n--)
			d[n] = s[n];
	return (d);
}
