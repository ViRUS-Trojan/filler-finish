/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:24:24 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/10 18:24:48 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <libft.h>
#include "filler_vizual.h"
#define IS_P1(x) ((x)=='O'||(x)=='o')
#define IS_P2(y) ((y)=='X'||(y)=='x')

/*
** заголовок vm имеет длину 9 строк
** строка 5 содержит заполнитель p1 (например: «запущен ./players/player1.filler»)
** строка 7 содержит наполнитель p2
** Если мы просто возьмем все после '/', у нас будет имя заполнителя!
*/

int			read_header(t_game *game, int fd, ssize_t *ret, char *line)
{
	size_t	i;
	char	*pname;

	i = -1;
	while (++i < 9 && ((*ret = get_next_line(fd, &line)) == 1))
	{
		if (i == 5 || i == 7)
		{
			if ((pname = ft_strrchr(line, '/')) != NULL)
			{
				pname++;
				if (i == 5)
					game->p1 = ft_strsub(pname, 0, ft_strlen(pname) - 7);
				else
					game->p2 = ft_strsub(pname, 0, ft_strlen(pname) - 7);
			}
			else
				disp_info(1);
		}
		free(line);
	}
	if (*ret > 0)
		return (0);
	else
		return (1);
}

/*
** read_board ()
** 1) Если строка, полученная в функции read_turn (), была "Плато" (8 символов)
** тогда за ним последуют два числа, разделенные знаком ''
** высота и ширина игрового поля. Легко получается с помощью ft_atoi
** и ft_strchr.
** 2) Затем мы добавляем новую ссылку в наш список связанных состояний игры.
** 3) Затем мы копируем текущее состояние доски в наше текущее состояние игры
*/

void		read_board(t_game *game, int fd, ssize_t *ret, char *line)
{
	int	i;

	game->h = ft_atoi(line + 8);
	game->w = ft_atoi(ft_strchr(line + 8, ' '));
	free(line);
	gs_lstadd(&(game->gss), gs_lstnew(game, 0));
	if (game->first == NULL)
		game->first = game->gss;
	if (game->color_t_rt == NULL)
	{
		game->color_t_rt = (short *)malloc((game->h * game->w) * sizeof(short));
		ft_bzero(game->color_t_rt, (game->h * game->w) * sizeof(short));
	}
	game->gss->turn = game->turn_rt++;
	i = -1;
	while (i++ < game->h && (*ret = get_next_line(fd, &line)) == 1)
	{
		if (i != 0)
			game->gss->board[i - 1] = board_strdup(game, (i - 1), line + 4);
		free(line);
	}
	ft_memcpy(game->gss->color_tab, game->color_t_rt,
		(game->h * game->w) * sizeof(short));
}

/*
** read_next_piece ()
** 1) Если строка, полученная в read_turn (), была "Piece" (6 символов)
** 2) Сначала мы должны проверить, не поместил ли игрок фигуру на нашу
** текущий ход. Если это так, значит, игрок дал неверную координату.
** Нам нужно отменить их точку зрения, а затем добавить новый элемент списка состояний игры, чтобы
** что мы можем следить за тем, что * другой * игрок получает как часть.
** Примечание: новый элемент состояния игры, если игроки «переключаются»
** не будет содержать копию игрового поля.
** 3) Затем мы читаем высоту и ширину фигуры в наше текущее состояние игры
** 4) Затем мы копируем текущий кусок в наше текущее состояние игры
*/

void		read_next_piece(t_game *game, int fd, ssize_t *ret, char *line)
{
	int		i;
	t_gslst *gss;

	gss = game->gss;
	if (gss->flags & PLACED)
	{
		(gss->flags & P1_PLACED) ? (game->p1_rt)-- : (game->p2_rt)--;
		gs_lstadd(&(game->gss), gs_lstnew(game, 1));
		gss = game->gss;
	}
	gss->piece_h = ft_atoi(line + 6);
	gss->piece_w = ft_atoi(ft_strchr(line + 6, ' '));
	free(line);
	gss->piece = (char **)malloc((gss->piece_h + 1) * sizeof(char *));
	i = 0;
	while (i < gss->piece_h && (*ret = get_next_line(fd, &line)) == 1)
	{
		gss->piece[i++] = ft_strdup(line);
		free(line);
	}
}

/*
** read_turn ()
** Получим 1 строку (после прочтения в шапке)
** 1) Если он содержит «конец», мы закончили!
** 2) Если он содержит «Плато», мы собираемся получить доску
** 3) Если он содержит «кусок», мы собираемся получить кусок
** а) После части будет одна строка, описывающая, какой игрок
** помещает кусок и где они хотят разместить его.
** ВАЖНОЕ ПРИМЕЧАНИЕ: нам нужно переназначить gss = game-> gss, потому что если
** был поворотный переключатель, тогда gane-> gss будет указывать на
** предыдущее состояние игры и не самое текущее состояние.
*/

int			read_turn(t_game *game, int fd, ssize_t *ret, char *line)
{
	t_gslst *gss;

	gss = game->gss;
	*ret = get_next_line(fd, &line);
	if (ft_strstr(line, "fin"))
	{
		(gss->flags & P1_PLACED) ? (game->p1_rt)-- : (game->p2_rt)--;
		free(line);
		return (1);
	}
	else if (ft_strstr(line, "Plateau "))
		read_board(game, fd, ret, line);
	else if (ft_strstr(line, "Piece "))
	{
		read_next_piece(game, fd, ret, line);
		gss = game->gss;
		*ret = get_next_line(fd, &line);
		gss->flags |= (ft_strchr(line, 'O')) ? P1_PLACED : 0;
		(gss->flags & P1_PLACED) ? (game->p1_rt)++ : (game->p2_rt)++;
		gss->piece_y = ft_atoi(line + 11);
		gss->piece_x = ft_atoi(ft_strchr(line + 11, ' '));
		gss->flags |= PLACED;
		free(line);
	}
	return (0);
}

/*
** test()
** Полезная функция проверки, чтобы убедиться, что карты читаются правильно
** Запустите `test (game);` после прочтения вывода vm, чтобы получить много полезной информации
*/

/*
**#include <stdio.h>
**
**void	test(t_game *game)
**{
**	t_gslst	*curr_state;
**	int		i;
**
**	printf("%s vs. %s\n", game->p1, game->p2);
**	curr_state = game->first;
**	while (curr_state)
**	{
**		if ((curr_state->flags & TURN_SWITCH) == 0)
**		{
**			printf("Turn: %d\n", curr_state->turn);
**			i = 0;
**			while (i < game->h)
**			{
**				printf("board: |%s| %d\n", curr_state->board[i], i);
**				i++;
**			}
**		}
**		i = 0;
**		printf("placer: %s\n",
**					(curr_state->flags & P1_PLACED) ? "P1" : "P2");
**		printf("pw: %d, ph: %d, px: %d, py: %d\n",
**			curr_state->piece_w, curr_state->piece_h,
**			curr_state->piece_x, curr_state->piece_y);
**		while (i < curr_state->piece_h)
**		{
**			printf("piece: |%s| %d\n", curr_state->piece[i], i);
**			i++;
**		}
**		printf("flags: %d\n", curr_state->flags);
**		printf("p1: %d, p2: %d\n", curr_state->p1_pts, curr_state->p2_pts);
**		curr_state = curr_state->next;
**	}
**	printf("total turns: %d\n", game->turn_rt);
**}
*/

/*
** read_game ()
** Функция вождения, чтобы прочитать игру, которая выводится наполнителем VM
*/

int			read_game(t_game *game, int fd, int argc, char *fpath)
{
	ssize_t	ret;
	char	*line;

	line = NULL;
	if ((fd = (argc == 1) ? 0 : open(fpath, O_RDONLY)) != -1)
	{
		if (read_header(game, fd, &ret, line) == 1)
			disp_info(0);
		while (1)
		{
			if (read_turn(game, fd, &ret, line) == 1)
				break ;
		}
		close(fd);
		if (game->last == NULL)
			game->last = game->gss;
		return (0);
	}
	else
		return (1);
}
