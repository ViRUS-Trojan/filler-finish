/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:13:18 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/04 14:14:09 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include "filler_vizual.h"

/*
** init_img - используйте функции mlx для инициализации нашего изображения, которым мы будем
** рисуя наши карты!
**
** Начальные биты на пиксель (bpp), которые возвращает функция mlx_get_data_addr
** составляет 32 бита.
**
** Хотелось бы поработать с байтами, так как это то, что остальные наши
** программа работает в.
**
** Пример 1: наши цвета - это целые числа в байтах.
** Пример 2: наши функции ft_bzero и ft_memset ожидают размер в байтах
**
** Поскольку 8 бит = 1 байт, мы просто берем наш bpp и делим на 8, чтобы получить
** байт на пиксель
**
** ДАВАЙТЕ ОБЪЯВИТЬ ЗДЕСЬ, ЧТО img-> bpp HENCEFORCE ВЫСТУПАЕТ ДЛЯ БАЙТОВ НА ПИКСЕЛЬ!
*/

void		init_img(t_envars *env)
{
	t_image	*img;

	img = &env->image;
	img->image = mlx_new_image(env->mlx, env->w, env->h);
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->line_s,
								&img->endian);
	img->bpp /= 8;
}

void		img_pixel_put(t_envars *env, double x, double y, int color)
{
	t_image *img;

	img = &(env->image);
	if (x >= 0 && x < env->w && y >= 0 && y < env->h)
		*(int *)(img->ptr + (int)(idx(y, x, env->w) * img->bpp)) = color;
}

/*
** Наше изображение имеет размер WIN_W * WIN_H * 32 бита на пиксель.
** Наши функции ft_bzero и ft_memset имеют размер в байтах, хотя ...
*/

void		clear_img(t_envars *env)
{
	t_image *img;

	img = &(env->image);
	ft_bzero(img->ptr, env->size * img->bpp);
}
