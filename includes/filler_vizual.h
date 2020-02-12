/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_vizual.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:55:54 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/10 18:22:53 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VIZUAL_H
# define FILLER_VIZUAL_H
# include <stddef.h>
# include "libft.h"
# define TURN_SWITCH	1
# define PLACED			2
# define P1_PLACED		4

/*
** t_gslst - 'список состояний игры'
**	Содержит:
**
** - текущая ширина куска
** - текущая высота куска
** - Позиция х, где игрок хочет разместить фигуру
** - позиция y, где игрок хочет разместить фигуру
**
** - переменная флага:
**
** TURN_SWITCH: указывает, что игрок испортил в предыдущем состоянии
** P1_PLACED: указывает, поместил ли p1 кусок (иначе p2 поместил его)
** РАЗМЕЩЕНО: была ли часть уже помещена в текущее состояние
**
** - Текущий счетчик оборотов
** - Количество точек, которые p1 имеет в текущем состоянии
** - количество баллов, которые p2 имеет в текущем состоянии
** - Двойной указатель платы для сохранения состояния платы
** - Двойной указатель фигуры для хранения фигуры
** - указатель на предыдущее состояние игры
** - указатель на следующее состояние игры
*/

typedef struct		s_gslst
{
	short			piece_w;
	short			piece_h;
	short			piece_x;
	short			piece_y;
	short			flags;
	int				turn;
	int				p1_pts;
	int				p2_pts;
	char			**board;
	short			*color_tab;
	char			**piece;
	struct s_gslst	*prev;
	struct s_gslst	*next;
}					t_gslst;

/*
** t_game
**	Содержит:
**
** - Имя игрока 1
** - Имя игрока 2
** - общее количество ходов в игре
** - высота игрового поля
** - ширина игрового поля
** - Общая сумма очков игрока 1
** - Общая сумма очков игрока 2
** - указатель на наш список состояний игры
** - указатель на самый первый элемент списка состояний игры
** - указатель на самый последний элемент списка состояний игры
*/

typedef struct		s_game
{
	char			*p1;
	char			*p2;
	int				turn_rt;
	int				h;
	int				w;
	int				p1_rt;
	int				p2_rt;
	short			*color_t_rt;
	t_gslst			*gss;
	t_gslst			*first;
	t_gslst			*last;
}					t_game;

/*
** t_image
** структура для хранения переменных, относящихся к изображениям mlx
*/

typedef struct		s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				line_s;
	int				endian;
}					t_image;

typedef struct		s_envars
{
	void			*mlx;
	void			*win;
	int				w;
	int				h;
	int				size;
	int				fd;
	int				p1_l;
	int				p2_l;
	int				b_glen;
	int				b_lpad;
	int				b_tpad;
	int				b_row_space;
	int				b_col_space;
	int				prev_turn;
	t_game			*g;
	t_gslst			*curr_gs;
	t_image			image;
}					t_envars;

/*
**	general_utils.c
*/
int					idx(int row, int col, int dim);
double				ft_lint(double start, double end, double decimal_percent);
char				*board_strdup(t_game *game, int i, const char *s);

/*
**	color.c
*/
int					choose_board_color(t_envars *e, int row, int col);
int					choose_piece_color(t_envars *e, int row, int col);

/*
**	main.c
*/
void				disp_info(int mode);
void				setup_env(t_envars *env);

/*
**	image.c
*/
int					idx(int row, int col, int dim);
void				init_img(t_envars *env);
void				img_pixel_put(t_envars *env, double x, double y, int color);
void				clear_img(t_envars *env);

/*
**	key_hooks.c
*/
int					keydown_hook(int key, t_envars *env);
int					key_pressed_hook(int key, t_envars *env);

/*
**	game_state_list_utils.c
*/
t_gslst				*gs_lstnew(t_game *game, int turn_switch);
void				gs_lstadd(t_gslst **gsts, t_gslst *new);

/*
**	read_utils.c
*/
int					read_game(t_game *game, int fd, int argc, char *fpath);

/*
**	render_str.c
*/
void				render_scoreboard(t_envars *e, t_gslst *gs);
void				render_piece_pos(t_envars *e, t_gslst *gs);

/*
**	render.c
*/
void				render(t_envars *env);

/*
**	sound.c
*/
int					play_sound(char *fpath);
void				choose_sound(t_envars *e, t_gslst *gs);

#endif
