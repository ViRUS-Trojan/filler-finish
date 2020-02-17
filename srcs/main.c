/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:53:05 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/14 19:36:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		free_strsplit(char **split)
{
	int i;

	i = -1;
	if (!split)
		return (-1);
	while (split[++i])
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
	return (-1);
}

int		check_huevaya_karta(char *line, t_game *game)
{
	char	**split;
	int		i;
	int		len;

	i = -1;
	if (ft_strequ(line, ""))
		return (-1);
	if (!(split = ft_strsplit(line, ' ')))
		return (-1);
	if (!split[1])
		return (free_strsplit(split));
	if ((int)ft_strlen(split[1]) != game->w_map)
		return (free_strsplit(split));
	len = ft_strlen(split[1]);
	while (++i < len)
	{
		if (split[1][i] == '.' || split[1][i] == 'X' || split[1][i] == 'x'
			|| split[1][i] == 'O' || split[1][i] == 'o')
			continue;
		else
			return (free_strsplit(split));
	}
	free_strsplit(split);
	return (0);
}

int		main(void)
{
	t_game	*game;
	int		round;

	if (!(game = ft_first_init()))
		return (0);
	round = 1;
	while (1)
	{
		if (ft_get_data(game) == -1)
			break ;
		ft_strat_map_calc(game);
		if (ft_put_piece(game, round) == -1)
			break ;
		ft_strat_adjustment(game);
		ft_clear_all(game);
		round++;
	}
	ft_delete_all(game);
	return (0);
}
