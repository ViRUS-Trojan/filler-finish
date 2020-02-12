/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_lst_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:18:33 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/09 17:18:34 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	*ft_new_arglst(t_arg **alst)
{
	t_arg	*tmp;

	if (alst == NULL)
		return (NULL);
	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = ft_memalloc(sizeof(t_arg));
		return (*alst);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_arg));
		return (tmp->next);
	}
}
