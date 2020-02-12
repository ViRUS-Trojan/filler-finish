/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:02:40 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/12 14:03:46 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countchars(char const *s, char c)
{
	int		cpt;

	cpt = 0;
	while (s[cpt] && s[cpt] != c)
		cpt++;
	return (cpt);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tmp;
	int		i;
	int		nb_words;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_countwords(s, c);
	if (!(tmp = (char **)malloc(sizeof(*tmp) * (nb_words + 1))))
		ft_exit("молочная ошибочка!)", 1);
	tmp[nb_words] = 0;
	while (i < nb_words)
	{
		while (*s && *s == c)
			s++;
		tmp[i] = ft_strsub(s, 0, ft_countchars(s, c));
		while (*s && *s != c)
			s++;
		i++;
	}
	return (tmp);
}
