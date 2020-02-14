/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:21:56 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/12 14:21:57 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*mem;

	if (!(mem = malloc(size)))
		ft_exit("молочная ошибка!", 1);
//	while (size--)
//		mem[size] = 0;
ft_bzero(mem, size);
	return ((void *)mem);
}
