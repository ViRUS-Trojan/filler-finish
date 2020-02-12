/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:20:37 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/09 17:22:32 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "filler_vizual.h"

/*
** idx () - Полезная функция для получения строки, значения col из сплющенного
** 2D матрица. Dim - это ширина матрицы ...
*/

int			idx(int row, int col, int dim)
{
	return (row * dim + col);
}

/*
** ft_lint - Линейная ИНТЕРПОЛЯЦИЯ между двумя точками с учетом десятичного процента
**
** Мы не делаем: (start + decimal_percent * (end - start)), потому что если
** начало и конец значительно различаются по величине, тогда мы теряем точность.
**
** Тест с: ft_lint (-16.0e30, 16.0, 1.0)
*/

double		ft_lint(double start, double end, double decimal_percent)
{
	if (start == end)
		return (start);
	return (start * (1.0 - decimal_percent) + (end * decimal_percent));
}

/*
** board_strdup ()
** Пользовательская версия ft_strdup () только для этого визуализатора
** Помимо дублирования строки, он также ищет символы 'o' и 'x'
** на текущей карте и присваивает текущую общую сумму хода
** таблица цветов игры;
*/

char		*board_strdup(t_game *game, int i, const char *s)
{
	char	*new_s;
	char	*start;
	size_t	len;
	size_t	j;

	len = ft_strlen(s);
	if ((new_s = (char *)malloc((len + 1) * sizeof(*new_s))) != NULL)
	{
		new_s[len] = '\0';
		start = new_s;
		j = 0;
		while (j < len)
		{
			*new_s = *s;
			if (*s == 'o' || *s == 'x')
				game->color_t_rt[idx(i, (int)j, game->w)] = game->gss->turn;
			new_s++;
			s++;
			j++;
		}
		return (start);
	}
	return (NULL);
}
