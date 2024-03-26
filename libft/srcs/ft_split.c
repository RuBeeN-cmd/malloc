/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrollin <rrollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:21:42 by rrollin           #+#    #+#             */
/*   Updated: 2022/04/05 17:47:26 by rrollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_nb_split(char const *s, char c)
{
	int	i;
	int	n;

	if (!s[0])
		return (0);
	i = 1;
	n = 0;
	while (s[i])
		if (s[i++] == c && s[i - 2] != c)
			n++;
	if (!s[i] && s[i - 1] != c)
		n++;
	return (n);
}

static char	*ft_get_substr(char *str, char c)
{
	char	*c_ptr;

	c_ptr = ft_memchr(str, c, ft_strlen(str));
	if (c_ptr)
		return (ft_substr(str, 0, c_ptr - str));
	else
		return (ft_substr(str, 0, ft_strlen(str)));
}

static void	*ft_free_all(char **tab, int i)
{
	while (i + 1)
		free(tab[i--]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		nb_tab;
	int		i;
	char	**tab;
	char	*str;

	if (!s)
		return (NULL);
	nb_tab = ft_get_nb_split(s, c);
	tab = malloc(sizeof(char *) * (nb_tab + 1));
	if (!tab)
		return (NULL);
	i = 0;
	str = (char *) s;
	while (i < nb_tab)
	{
		while (str && *str == c)
			str++;
		tab[i] = ft_get_substr(str, c);
		if (!tab[i])
			return (ft_free_all(tab, i - 1));
		str = ft_memchr(str, c, ft_strlen(str));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
