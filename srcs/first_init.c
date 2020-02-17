/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:57:55 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/16 19:46:56 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	ft_get_coin(t_game *game)
{
	char	*line;

	if (get_next_line(0, &line) == -1)
		return (-1);
	if (line[10] == '1')
	{
		game->my_coin = 'o';
		game->opp_coin = 'x';
	}
	else
	{
		game->my_coin = 'x';
		game->opp_coin = 'o';
	}
	ft_strdel(&line);
	return (0);
}

static int	ft_get_map_size(t_game *game)
{
	char	*start;
	char	*middle;
	char	*end;
	char	*nbr;
	char	*line;

	if (get_next_line(0, &line) == -1 || !line || ft_strncmp(line, BOARD, 7))
	{
		ft_strdel(&line);
		return (-1);
	}
	if (init_start_middle_end(line, &start, &middle, &end) == -1)
	{
		ft_strdel(&line);
		return (-1);
	}
	nbr = ft_strsub(start + 1, 0, middle - start + 1);
	game->h_map = ft_atoi(nbr);
	ft_strdel(&nbr);
	nbr = ft_strsub(middle + 1, 0, end - middle + 1);
	game->w_map = ft_atoi(nbr);
	ft_strdel(&nbr);
	ft_strdel(&line);
	return (0);
}

static void	ft_first_init_strat_map(t_game *game)
{
	int		i;

	game->strat_map = ft_memalloc(sizeof(*game->strat_map) * game->h_map);
	i = 0;
	while (i < game->h_map)
	{
		game->strat_map[i] = ft_memalloc(sizeof(**game->strat_map)
											* game->w_map);
		i++;
	}
}

t_game		*ft_first_init(void)
{
	t_game	*game;

	if (!(game = ft_memalloc(sizeof(t_game))))
		return (NULL);
	if (ft_get_coin(game) == -1)
	{
		free(game);
		return (NULL);
	}
	if (ft_get_map_size(game) == -1)
	{
		free(game);
		return (NULL);
	}
	game->gross_map = ft_memalloc(sizeof(*game->gross_map) *
				(game->h_map * game->w_map + game->h_map + 1));
	ft_first_init_strat_map(game);
	ft_init_debug(game);
	return (game);
}
