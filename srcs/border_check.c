/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:46:54 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/07 16:46:55 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_check_the_top(t_game game)
{
	int		j;
	int		opp_coin;

	j = 0;
	opp_coin = 0;
	while (j < game.w_map)
	{
		if (ft_is_opp(game, game.strat_map[0][j].value))
			opp_coin++;
		if (ft_is_me(game, game.strat_map[0][j].value))
			return (1);
		j++;
	}
	if (opp_coin >= (game.w_map / 2 + 2))
		return (-1);
	return (0);
}

int		ft_check_the_bottom(t_game game)
{
	int		j;
	int		opp_coin;

	j = 0;
	opp_coin = 0;
	while (j < game.w_map)
	{
		if (ft_is_opp(game, game.strat_map[game.h_map - 1][j].value))
			opp_coin++;
		if (ft_is_me(game, game.strat_map[game.h_map - 1][j].value))
			return (1);
		j++;
	}
	if (opp_coin >= (game.w_map / 2 + 2))
		return (-1);
	return (0);
}

int		ft_check_the_right(t_game game)
{
	int		i;
	int		opp_coin;

	i = 0;
	opp_coin = 0;
	while (i < game.h_map)
	{
		if (ft_is_opp(game, game.strat_map[i][game.w_map - 1].value))
			opp_coin++;
		if (ft_is_me(game, game.strat_map[i][game.w_map - 1].value))
			return (1);
		i++;
	}
	if (opp_coin >= (game.h_map / 2 + 2))
		return (-1);
	return (0);
}

int		ft_check_the_left(t_game game)
{
	int		i;
	int		opp_coin;

	i = 0;
	opp_coin = 0;
	while (i < game.h_map)
	{
		if (ft_is_opp(game, game.strat_map[i][0].value))
			opp_coin++;
		if (ft_is_me(game, game.strat_map[i][0].value))
			return (1);
		i++;
	}
	if (opp_coin >= (game.h_map / 2 + 2))
		return (-1);
	return (0);
}
