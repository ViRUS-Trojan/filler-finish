/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttab_ascii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:16:43 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/12 13:17:22 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Возьмите в качестве параметра табуляцию ** char, заканчивающийся указателем NULL
** Сортировка этой вкладки по лексикографическому порядку = по порядку ascii.
*/

void	ft_sorttab_ascii(char **tab)
{
	char	*tmp;
	int		i;

	if (ft_tablen(tab) == 0 || ft_tablen(tab) == 1)
		return ;
	tmp = NULL;
	i = 0;
	while (tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}