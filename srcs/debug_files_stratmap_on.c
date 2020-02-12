/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_files_stratmap_on.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:46:44 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/01 14:46:45 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	ft_put_border_target(t_game game, int fd)
{
	ft_putstr_fd("Border target : ", fd);
	if (game.border.top == 1)
		ft_putstr_fd("TOP", fd);
	else if (game.border.bottom == 1)
		ft_putstr_fd("BOTTOM", fd);
	else if (game.border.right == 1)
		ft_putstr_fd("RIGHT", fd);
	else
		ft_putstr_fd("NONE", fd);
	ft_putstr_fd("\n", fd);
}

static void	ft_put_stratmap_weight(t_game game, int fd)
{
	int		i;
	int		j;

	ft_putendl_fd("WEIGHT: ", fd);
	i = 0;
	while (i < game.h_map)
	{
		j = 0;
		while (j < game.w_map)
		{
			if (ft_is_me(game, game.strat_map[i][j].value)
				|| ft_is_opp(game, game.strat_map[i][j].value))
				ft_putchar_fd(game.strat_map[i][j].value, fd);
			else
				ft_putnbr_fd(game.strat_map[i][j].weight, fd);
			ft_putchar_fd('\t', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

static void	ft_put_stratmap_border(t_game game, int fd)
{
	int		i;
	int		j;

	ft_putendl_fd("BORDER: ", fd);
	i = 0;
	while (i < game.h_map)
	{
		j = 0;
		while (j < game.w_map)
		{
			if (ft_is_opp(game, game.strat_map[i][j].value)
				|| ft_is_me(game, game.strat_map[i][j].value))
				ft_putchar_fd(game.strat_map[i][j].value, fd);
			else
				ft_putnbr_fd(game.strat_map[i][j].border, fd);
			ft_putchar_fd('\t', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

static void	ft_put_stratmap_heat(t_game game, int fd)
{
	int		i;
	int		j;

	ft_putendl_fd("HEAT: ", fd);
	i = 0;
	while (i < game.h_map)
	{
		j = 0;
		while (j < game.w_map)
		{
			if (ft_is_opp(game, game.strat_map[i][j].value)
				|| ft_is_me(game, game.strat_map[i][j].value))
				ft_putchar_fd(game.strat_map[i][j].value, fd);
			else
				ft_putnbr_fd(game.strat_map[i][j].heat, fd);
			ft_putchar_fd('\t', fd);
			j++;
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void		ft_put_stratmap(t_game game, int round)
{
	int		fd;

	if (round == 1)
		fd = open("debug_strat_map", O_RDWR | O_CREAT | O_TRUNC, 0666);
	else
		fd = open("debug_strat_map", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		return ;
	ft_putstr_fd("\n-------------------------\n\nROUND: ", fd);
	ft_putnbr_fd(round, fd);
	ft_putendl_fd("\n", fd);
	ft_put_stratmap_heat(game, fd);
	ft_put_border_target(game, fd);
	ft_put_stratmap_border(game, fd);
	ft_put_stratmap_weight(game, fd);
	ft_putendl_fd("PIECE: ", fd);
	ft_putstr_fd("h = ", fd);
	ft_putnbr_fd(game.h_piece, fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("w = ", fd);
	ft_putnbr_fd(game.w_piece, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd(game.piece, fd);
	ft_putendl_fd("VALID PLACES WITH SCORES : ", fd);
	close(fd);
}
