/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_calc_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:48:21 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/07 17:48:22 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_calc_heat_weight(t_game *game)
{
	ft_first_heat_calc(game);
	ft_fill_heat_1(game);
	ft_fill_heat_2(game);
}
