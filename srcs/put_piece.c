/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:53:45 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/07 17:53:46 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_move(t_game *game, int *i, int *j, int init_j)
{
	if (*game->piece == '\n')
	{
		*j = init_j;
		(*i)++;
	}
	else
		(*j)++;
	(game->piece)++;
}

static float	ft_calc_score(t_game game, int i, int j)
{
	float	score;
	int		my_coin;
	int		init_j;

	score = 0;
	my_coin = 0;
	init_j = j;
	while (*game.piece)
	{
		if (*game.piece == '*')
		{
			if (j >= game.w_map || i >= game.h_map || j < 0 || i < 0)
				return (0);
			if (ft_is_me(game, game.strat_map[i][j].value) && my_coin == 0)
				my_coin = 1;
			else if (ft_is_me(game, game.strat_map[i][j].value) && my_coin == 1)
				return (0);
			else if (ft_is_opp(game, game.strat_map[i][j].value))
				return (0);
			else if (ft_is_empty(game.strat_map[i][j].value))
				score += game.strat_map[i][j].weight;
		}
		ft_move(&game, &i, &j, init_j);
	}
	return (my_coin == 1 ? score : 0);
}

static int		ft_is_better_place(float tmp, float best_score, t_game game)
{
	if (ft_is_top_player(game))
		return (tmp >= best_score);
	else
		return (tmp > best_score);
}

static void		ft_get_place(t_game *game)
{
	int		i;
	int		j;
	float	best_score;
	float	tmp;

	best_score = 0;
	i = 0 - game->h_piece;
	while (i < game->h_map)
	{
		j = 0 - game->w_piece;
		while (j < game->w_map)
		{
			tmp = ft_calc_score(*game, i, j);
			(tmp != 0) ? ft_put_place_score(tmp, i, j) : 0;
			if (tmp && ft_is_better_place(tmp, best_score, *game))
			{
				best_score = tmp;
				game->pos_x = i;
				game->pos_y = j;
				game->place_found = 1;
			}
			j++;
		}
		i++;
	}
}

int				ft_put_piece(t_game *game, int round)
{
	ft_put_stratmap(*game, round);
	ft_get_place(game);
	ft_printf("%d %d\n", game->pos_x, game->pos_y);
	ft_put_best_place(game->pos_x, game->pos_y);
	if (game->place_found == 0)
		return (-1);
	return (0);
}
