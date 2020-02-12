/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:22:49 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/10 18:40:30 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "filler_vizual.h"

void			disp_info(int mode)
{
	if (mode == 0)
	{
		write(2, "\nUsage: ./filler_vizual [filler_vm_output] ", 40);
		write(2, "\nOR\nfiller_vm [vm_options] | ./filler_vizual\n\n", 43);
		exit(1);
	}
	else if (mode == 1)
	{
		write(2, "An error occurred reading the file or input.", 44);
		write(2, " Is it valid?\n", 14);
		exit(1);
	}
	else if (mode == 2)
	{
		ft_printf("\n			Filler Vizual 21!!\n\
	стрелка влево (←): переместиться на один оборот назад \n\
	стрелка вправо (→): двигаться вперед на один оборот \n\
	стрелка вниз (↓): двигаться вперед 9x  \n\
	стрелка вверх (↑): переместиться назад на 9x \n\
	p: Печать текущего игрока, доски и фигуры на консоли \n\
	f: переместить состояние игры на первый ход \n\
	l: переместить состояние игры в последний ход \n\
	esc: Выход: (\n\n ");
	}
}

void			setup_game(t_game *game)
{
	game->p1 = NULL;
	game->p2 = NULL;
	game->turn_rt = 0;
	game->h = 0;
	game->w = 0;
	game->p1_rt = 0;
	game->p2_rt = 0;
	game->color_t_rt = NULL;
	game->gss = NULL;
	game->first = NULL;
	game->last = NULL;
}

void			setup_env(t_envars *e)
{
	e->b_glen = 12;
	e->b_lpad = e->b_glen;
	e->b_tpad = 70;
	e->b_row_space = 1;
	e->b_col_space = 1;
	e->w = ((e->g->w + 1) * e->b_glen + e->b_lpad) * 2;
	e->h = (e->g->h + 1) * e->b_glen + e->b_tpad;
	e->size = e->w * e->h;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->w, e->h, "Filler Viz 21");
	e->prev_turn = -1;
	init_img(e);
	mlx_key_hook(e->win, keydown_hook, e);
	mlx_hook(e->win, 2, 0, key_pressed_hook, e);
}

/*
** main - функция, с которой мы начинаем нашу сессию mlx
** Есть дополнительные крючки, которые можно найти!
** См .: https://github.com/qst0/ft_libgfx.
** Особый интерес представляют крючки для нажатия, отпускания и перемещения мыши
** которые сопоставлены с 4, 5 и 6 соответственно.
*/

int				main(int argc, const char *argv[])
{
	t_envars	env;
	t_game		game;

	if (argc == 1 || argc == 2)
	{
		setup_game(&game);
		if (read_game(&game, env.fd, argc, (char *)argv[1]) == 0)
		{
			disp_info(2);
			env.g = &game;
			env.curr_gs = game.first;
			setup_env(&env);
			render(&env);
			mlx_loop(env.mlx);
			return (0);
		}
		else
			disp_info(1);
	}
	disp_info(0);
}
