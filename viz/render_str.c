/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:27:47 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/11 14:24:38 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "filler_vizual.h"

void	render_scoreboard(t_envars *e, t_gslst *gs)
{
	int		p1_end;
	int		p2_end;
	char	*p1;
	char	*p2;

	p1_end = (ft_strlen(e->g->p1) + 1) * e->b_glen;
	p2_end = (ft_strlen(e->g->p2) + 1) * e->b_glen;
	p1 = ft_itoa(gs->p1_pts);
	p2 = ft_itoa(gs->p2_pts);
	mlx_string_put(e->mlx, e->win, e->b_lpad, 10, 0x18FF0A, e->g->p1);  ///зеленый 
	mlx_string_put(e->mlx, e->win, e->b_lpad + p1_end, 10, 0x18FF0A, p1);  //// зеленый
	mlx_string_put(e->mlx, e->win, e->b_lpad, 30, 0xFE1537, e->g->p2);  ///красный
	mlx_string_put(e->mlx, e->win, e->b_lpad + p2_end, 30, 0xFE1537, p2);  /// красный
	free(p1);
	free(p2);
}

void	render_piece_pos(t_envars *e, t_gslst *gs)
{
	int		x_start;
	char	*x;
	char	*y;
	char	*p_str;
	int		p_len;

	x_start = e->b_lpad + (e->g->w + 1) * e->b_glen;
	if (gs->prev)
	{
		x = ft_itoa(gs->prev->piece_x);
		y = ft_itoa(gs->prev->piece_y);
		p_len = ft_strlen(x) + ft_strlen(y) + ft_strlen("Placed at: , ");
		p_str = (char *)malloc(p_len + 1);
		p_str = ft_strcat(ft_strcat(ft_strcat(p_str, "Placed at: "), x), ", ");
		p_str = ft_strcat(ft_strcat(p_str, y), "\0");
		if (gs->prev->flags & P1_PLACED)
			mlx_string_put(e->mlx, e->win, x_start, 10, 0x18FF0A, p_str); ////// зеленый
		else
			mlx_string_put(e->mlx, e->win, x_start, 10, 0xFE1537, p_str); ///// красный
		free(x);
		free(y);
		free(p_str);
	}
	mlx_string_put(e->mlx, e->win, x_start, 30, 0xFFFFFF, "Next Piece"); /// белый
}
