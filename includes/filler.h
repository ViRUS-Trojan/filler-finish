/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:03:08 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/09 17:06:24 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <fcntl.h>

# define SMALL_MAP_MAX_W 20
# define SMALL_MAP_MAX_H 20
# define BOARD "Plateau"
# define PIECE "Piece"

typedef struct	s_map
{
	char		value;
	float		weight;
	int			heat;
	int			border;
}				t_map;

typedef struct	s_border
{
	int			top;
	int			bottom;
	int			right;
	int			left;
}				t_border;

typedef struct	s_game
{
	char		my_coin;
	char		opp_coin;
	char		player_position;
	int			h_map;
	int			w_map;
	char		*gross_map;
	t_map		**strat_map;
	char		*piece;
	int			h_piece;
	int			w_piece;
	int			pos_x;
	int			pos_y;
	int			place_found;
	t_border	border;
	float		coef_heat;
	float		coef_border;
}				t_game;

/*
** Инструменты
*/
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_is_me(t_game game, char value);
int				ft_is_opp(t_game game, char value);
int				ft_is_empty(char value);
int				ft_is_top_player(t_game game);
int				ft_border_is_activate(t_game game);
int				ft_heat_is_activate(t_game game);
void			ft_activate_heat(t_game *game);
void			ft_activate_border(t_game *game);
void			ft_desactivate_border(t_game *game);
int				init_start_middle_end(char *line, char **start, char **middle,
																char **end);

/*
** Init
*/
int				ft_first_init(t_game *game);
int				ft_get_data(t_game *game);

/*
** Алгос - рассчитать вес карты
*/
void			ft_first_heat_calc(t_game *game);
void			ft_fill_heat_1(t_game *game);
void			ft_fill_heat_2(t_game *game);
void			ft_calc_heat_weight(t_game *game);
void			ft_border_weight_from_top(t_game *game);
void			ft_border_weight_from_bottom(t_game *game);
void			ft_border_weight_from_right(t_game *game);
void			ft_border_weight_from_left(t_game *game);
void			ft_clear_border_weight(t_game *game);
void			ft_strat_map_calc(t_game *game);

/*
** Алгос - выбери место
*/
int				ft_put_piece(t_game *game, int round);

/*
** Алгос - настроить страт
*/
int				ft_check_the_top(t_game game);
int				ft_check_the_bottom(t_game game);
int				ft_check_the_right(t_game game);
int				ft_check_the_left(t_game game);
void			ft_strat_adjustment(t_game *game);

/*
** Clear
*/
void			ft_clear_all(t_game *game);
void			ft_delete_all(t_game *game);

/*
** Debug
*/
void			ft_init_debug(t_game game);
void			ft_put_stratmap(t_game game, int round);
void			ft_put_place_score(int score, int i, int j);
void			ft_put_best_place(int i, int j);

#endif
