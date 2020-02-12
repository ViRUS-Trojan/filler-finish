/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_and_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:12:06 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/01 14:12:09 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_delete_all(t_game *game)
{
	int		i;

	ft_strdel(&game->piece);
	ft_strdel(&game->gross_map);
	i = 0;
	while (i < game->h_map)
	{
		free(game->strat_map[i]);
		game->strat_map[i] = NULL;
		i++;
	}
	free(game->strat_map);
	ft_bzero(game, sizeof(*game));
}

static void	ft_clear_strat_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->h_map)
	{
		j = 0;
		while (j < game->w_map)
		{
			game->strat_map[i][j].value = 0;
			game->strat_map[i][j].weight = 0;
			game->strat_map[i][j].heat = 0;
			j++;
		}
		i++;
	}
}

void		ft_clear_all(t_game *game)
{
	ft_strdel(&game->piece);
	game->place_found = 0;
	game->pos_x = 0;
	game->pos_y = 0;
	game->h_piece = 0;
	game->w_piece = 0;
	ft_bzero(game->gross_map, ft_strlen(game->gross_map));
	ft_clear_strat_map(game);
}
