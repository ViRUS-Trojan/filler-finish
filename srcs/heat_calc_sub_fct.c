/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_calc_sub_fct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:50:17 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/07 17:50:19 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	ft_has_opp_side(t_game game, int i, int j)
{
	if (i != 0 && ft_is_opp(game, game.strat_map[i - 1][j].value))
		return (1);
	if (j != 0 && ft_is_opp(game, game.strat_map[i][j - 1].value))
		return (1);
	if (i != game.h_map - 1
		&& ft_is_opp(game, game.strat_map[i + 1][j].value))
		return (1);
	if (j != game.w_map - 1
		&& ft_is_opp(game, game.strat_map[i][j + 1].value))
		return (1);
	return (0);
}

void		ft_first_heat_calc(t_game *game)
{
	int		i;
	int		j;
	int		max_val;

	max_val = ft_max(game->h_map, game->w_map) * 4;
	i = 0;
	while (i < game->h_map)
	{
		j = 0;
		while (j < game->w_map)
		{
			if (!ft_is_opp(*game, game->strat_map[i][j].value)
				&& ft_has_opp_side(*game, i, j))
				game->strat_map[i][j].heat = max_val;
			j++;
		}
		i++;
	}
}

static int	ft_get_side_val(t_game *game, int i, int j)
{
	int		max;

	max = 0;
	if (i != 0 && game->strat_map[i - 1][j].heat > max)
		max = game->strat_map[i - 1][j].heat;
	if (j != 0 && game->strat_map[i][j - 1].heat > max)
		max = game->strat_map[i][j - 1].heat;
	if (i != game->h_map - 1 && game->strat_map[i + 1][j].heat > max)
		max = game->strat_map[i + 1][j].heat;
	if (j != game->w_map - 1 && game->strat_map[i][j + 1].heat > max)
		max = game->strat_map[i][j + 1].heat;
	return (max);
}

void		ft_fill_heat_1(t_game *game)
{
	int		i;
	int		j;
	int		side_val;

	i = 0;
	while (i < game->h_map)
	{
		j = 0;
		while (j < game->w_map)
		{
			if (game->strat_map[i][j].heat == 0
				&& !ft_is_opp(*game, game->strat_map[i][j].value))
			{
				if ((side_val = ft_get_side_val(game, i, j)) > 0)
					game->strat_map[i][j].heat = side_val - 1;
			}
			j++;
		}
		i++;
	}
}

void		ft_fill_heat_2(t_game *game)
{
	int		i;
	int		j;
	int		side_val;

	i = game->h_map - 1;
	while (i >= 0)
	{
		j = game->w_map - 1;
		while (j >= 0)
		{
			if (!ft_is_opp(*game, game->strat_map[i][j].value))
			{
				if (game->strat_map[i][j].heat == 0
					&& (side_val = ft_get_side_val(game, i, j)) > 0)
					game->strat_map[i][j].heat = side_val - 1;
			}
			j--;
		}
		i--;
	}
}
