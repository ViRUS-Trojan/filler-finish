/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:22:23 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/14 20:01:57 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			free_strsplit(char **split)
{
	int i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
}

static int         check_huevaya_karta(char *line, t_game *game)
{
    char **split;
    int i = 0;
    int len;

    if (!line)
        return (-1);
    if (ft_strequ(line, ""))
        return (-1);
    split = ft_strsplit(line, ' ');
    if (!split)
        return (-1);
    if (!split[1])
	{
		free_strsplit(split);
		return (-1);
	}
    if ((int)ft_strlen(split[1]) != game->w_map)
	{
    	free_strsplit(split);
		return(-1);
	}
	len = ft_strlen(split[1]);
    while (i < len)
    {
        if (split[1][i] == '.' || split[1][i] == 'X' || split[1][i] == 'x' || split[1][i] == 'O' || split[1][i] == 'o')
            i++;
        else
		{
        	free_strsplit(split);
			return (-1);
		}
    }
	free_strsplit(split);
    return (0);
}


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
	i = 0;
	while (i < game->h_map)
	{
		if (get_next_line(0, &line) == -1 || !line)
			return (-1);
		if (check_huevaya_karta(line, game) == -1)
		{
			ft_strdel(&line);
			return (-1);
		}

		ft_strcat(game->gross_map, ft_strchr(line, ' ') + 1);
		ft_strcat(game->gross_map, "\n");
		ft_strdel(&line);
		i++;
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
	//////защитить маллок
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
	ft_init_strat_map(game, game->gross_map);
	return (0);
}
