/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:53:05 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/12 12:56:43 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	t_game	game;
	int		round;

	if (ft_first_init(&game) == -1)
		ft_exit("Ошибка чтения!", 2);
	round = 1;
	while (1)
	{
		if (ft_get_data(&game) == -1)
			break ;
		ft_strat_map_calc(&game);
		if (ft_put_piece(&game, round) == -1)
			break ;
		ft_strat_adjustment(&game);
		ft_clear_all(&game);
		round++;
	}
	ft_delete_all(&game);
	return (0);
}
