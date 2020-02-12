/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:15:00 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/10 18:53:54 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <libft.h>
#include "filler_vizual.h"

void		emancipate(t_envars *env)
{
	int		i;
	t_gslst	*curr;
	t_gslst	*next;

	curr = env->g->first;
	while (curr)
	{
		i = 0;
		if (!(curr->flags & TURN_SWITCH))
		{
			while (i < env->g->h)
				free(curr->board[i++]);
			free(curr->board);
		}
		i = 0;
		while (i < curr->piece_h)
			free(curr->piece[i++]);
		free(curr->piece);
		free(curr->color_tab);
		next = curr->next;
		free(curr);
		curr = next;
	}
}

static void	cleanup_env(t_envars *env)
{
	emancipate(env);
	free(env->g->p1);
	free(env->g->p2);
	free(env->g->color_t_rt);
	mlx_destroy_image(env->mlx, (&env->image)->image);
	mlx_destroy_window(env->mlx, env->win);
}

void		print_current_gs(t_envars *env)
{
	int i;
	int p;

	p = ((env->curr_gs->flags & P1_PLACED)) ? 1 : 2;
	if (p == 1)
		ft_printf("\n$$$ exec p%d : [./%s.filler]\n", p, env->g->p1);
	else if (p == 2)
		ft_printf("\n$$$ exec p%d : [./%s.filler]\n", p, env->g->p2);
	ft_printf("Plateau %d %d:\n", env->g->h, env->g->w);
	ft_printf("    ");
	i = -1;
	while (++i < env->g->w)
		ft_printf("%d", i % 10);
	ft_printf("\n");
	i = -1;
	while (++i < env->g->h)
		ft_printf("%03d %s\n", i, env->curr_gs->board[i]);
	ft_printf("Piece %d %d:\n", env->curr_gs->piece_h, env->curr_gs->piece_w);
	i = -1;
	while (++i < env->curr_gs->piece_h)
		ft_printf("%s\n", env->curr_gs->piece[i]);
	ft_printf("\n");
}

/*
** keydown_hook - аналогичен key_pressed_hook, но вызывается только когда
** клавиша была нажата И отпущена.
**
** Следующий ключ сопоставлен:
** 'esc' (53) = выйти из программы
** 'p' (35) = печатать игрока, игровое поле и фигуру для текущего игрового хода
** 'f' (3) = перевести игровое состояние в ход 0
** 'l' (37) = перенести игровое состояние на последний ход
*/

int			keydown_hook(int key, t_envars *env)
{
	if (key == 53)
	{
		cleanup_env(env);
		exit(0);
	}
	if (key == 35)
	{
		print_current_gs(env);
	}
	if (key == 3)
	{
		env->curr_gs = env->g->first;
		render(env);
	}
	if (key == 37)
	{
		env->curr_gs = env->g->last;
		render(env);
	}
	return (0);
}

/*
** key_pressed_hook - любая из клавиш со стрелками на клавиатуре
** удерживая, сдвиньте карту в этом направлении.
**
** ← (123) = вернуться на один оборот
** → (124) = двигаться вперед на один оборот
** ↓ (125) = двигаться вперед 9x
** ↑ (126) = двигаться назад 9x
*/

int			key_pressed_hook(int key, t_envars *e)
{
	int i;

	i = -1;
	if (key == 124)
		e->curr_gs = (e->curr_gs->next) ? e->curr_gs->next : e->curr_gs;
	if (key == 123)
		e->curr_gs = (e->curr_gs->prev) ? e->curr_gs->prev : e->curr_gs;
	if (key == 125)
		while (++i < 9)
			e->curr_gs = (e->curr_gs->next) ? e->curr_gs->next : e->curr_gs;
	if (key == 126)
		while (++i < 9)
			e->curr_gs = (e->curr_gs->prev) ? e->curr_gs->prev : e->curr_gs;
	if (!(key == 53 || key == 3 || key == 35 || key == 37))
		render(e);
	return (0);
}
