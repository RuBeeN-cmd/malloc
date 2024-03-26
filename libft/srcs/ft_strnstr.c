/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:19:58 by rrollin           #+#    #+#             */
/*   Updated: 2022/04/04 11:45:39 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*str;
	char	*to_find;
	int		i;

	str = (char *) big;
	to_find = (char *) little;
	if (!*to_find)
		return (str);
	while (*str && len--)
	{
		i = 0;
		if (*to_find == *str)
		{
			while (str[i] == to_find[i] && str[i] && len - i + 1)
				i++;
			if (!to_find[i])
				return (str);
			if (to_find[i] != str[i] || !str[i])
				str++;
		}
		else
			str++;
	}
	return (NULL);
}
