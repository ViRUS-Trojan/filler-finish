/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:22:23 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/16 20:02:04 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	ft_fill_map(t_game *game)
{
	char	*line;
	int		i;

	if (get_next_line(0, &line) == -1 || !line)
		return (-1);
	if (line[0] == 'P')
	{
		ft_strdel(&line);
		if (get_next_line(0, &line) == -1)
			return (-1);
	}
	ft_strdel(&line);
	i = -1;
	while (++i < game->h_map)
	{
		if (get_next_line(0, &line) == -1 || !line)
			return (-1);
		ft_strcat(game->gross_map, ft_strchr(line, ' ') + 1);
		ft_strcat(game->gross_map, "\n");
		ft_strdel(&line);
	}
	return (0);
}

static int	ft_get_piece_size(t_game *game)
{
	char	*start;
	char	*middle;
	char	*end;
	char	*nbr;
	char	*line;

	if (get_next_line(0, &line) == -1 || !line || ft_strncmp(line, PIECE, 5))
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
	game->h_piece = ft_atoi(nbr);
	ft_strdel(&nbr);
	nbr = ft_strsub(middle + 1, 0, end - middle + 1);
	game->w_piece = ft_atoi(nbr);
	ft_strdel(&nbr);
	ft_strdel(&line);
	return (0);
}

static int	ft_get_piece(t_game *game)
{
	char	*line;
	int		i;

	game->piece = ft_memalloc(sizeof(*game->piece) *
				(game->h_piece * game->w_piece + game->h_piece + 1));
	if (!game->piece)
		return (-1);
	i = 0;
	while (i < game->h_piece)
	{
		if (get_next_line(0, &line) == -1)
			return (-1);
		if (!line)
			return (-1);
		ft_strcat(game->piece, line);
		ft_strcat(game->piece, "\n");
		ft_strdel(&line);
		i++;
	}
	return (0);
}

static void	ft_init_strat_map(t_game *game, char *gross_map)
{
	int		i;
	int		j;

	i = 0;
	while (*gross_map && i < game->h_map)
	{
		j = 0;
		while (*gross_map && j < game->w_map)
		{
			game->strat_map[i][j].value = *gross_map;
			gross_map++;
			j++;
		}
		if (*gross_map)
			gross_map++;
		i++;
	}
}

int			ft_get_data(t_game *game)
{
	if (ft_fill_map(game) == -1)
		return (-1);
	if (ft_get_piece_size(game) == -1)
		return (-1);
	if (ft_get_piece(game) == -1)
		return (-1);
	if (check_huevaya_karta(line, game) == -1)
	{
		ft_strdel(&line);
		return (-1);
	}
	ft_init_strat_map(game, game->gross_map);
	return (0);
}
