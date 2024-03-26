/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:00:56 by rrollin           #+#    #+#             */
/*   Updated: 2022/04/04 13:53:27 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contain(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	left;
	int	right;
	int	len;

	if (!s1 || !set)
		return (NULL);
	left = 0;
	right = 0;
	len = ft_strlen(s1);
	while (ft_contain(set, s1[left]))
		left++;
	while (ft_contain(set, s1[len - right - 1]))
		right++;
	if (left == len)
		right = 0;
	return (ft_substr(s1, left, len - left - right));
}
