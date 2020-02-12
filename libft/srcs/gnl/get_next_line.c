/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:10:55 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/09 17:12:38 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** ft_create_elem и ft_find_or_create:
** Узнайте, существует ли ссылка, содержащая fd,
** в противном случае создайте ссылку и добавьте ее в конец списка.
** Также проверьте, что fd является sup. в ноль.
*/

t_file	*ft_create_elem(int fd)
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(*new))))
		ft_exit("молочная ошибка!", 1);
	new->fd = fd;
	if (!(new->buff = ft_strnew(BUFF_SIZE)))
		return (NULL);
	new->next = NULL;
	return (new);
}

t_file	*ft_find_or_create(t_file **begin, int fd)
{
	t_file	*current;

	if (fd < 0)
		return (NULL);
	if (*begin == NULL)
	{
		*begin = ft_create_elem(fd);
		return (*begin);
	}
	current = *begin;
	while (current && fd != current->fd)
		current = current->next;
	if (current == NULL)
	{
		current = *begin;
		while (current->next)
			current = current->next;
		current->next = ft_create_elem(fd);
		return (current->next);
	}
	return (current);
}

/*
** ft_remove_file:
** В конце чтения. Удалить ссылку, содержащую FD.
*/

void	ft_remove_file(t_file **begin, int fd)
{
	t_file	*current;
	t_file	*supp;

	current = *begin;
	if (current->fd == fd)
	{
		ft_strdel(&(current->buff));
		current->fd = -1;
		*begin = (*begin)->next;
		free(current);
	}
	else
	{
		while (current->next && current->next->fd != fd)
			current = current->next;
		supp = current->next;
		current->next = current->next->next;
		ft_strdel(&(supp->buff));
		supp->fd = -1;
		supp->next = NULL;
		free(supp);
	}
}

/*
** ft_work_with_buff:
** В зависимости от содержимого баффа заполните строку, а затем измените бафф.
** Возвращает 1, если '\ n' найден, 0 в противном случае.
*/

int		ft_work_with_buff(char *buff, char **line)
{
	int		i;
	int		start;
	char	*tmp_sub;
	char	*tmp_line;

	i = -1;
	start = 0;
	while (++i < BUFF_SIZE && *(buff) != '\n')
		if (*(buff++) == '\0' && *(buff))
			start = i + 1;
	tmp_sub = ft_strsub(buff - i, start, i - start);
	tmp_line = *line;
	*line = ft_strjoin(tmp_line, tmp_sub);
	ft_strdel(&tmp_line);
	ft_strdel(&tmp_sub);
	if (*buff == '\n')
	{
		ft_bzero(buff - i, i + 1);
		return (1);
	}
	if (**line == '\0')
		ft_strdel(line);
	ft_bzero(buff - i, BUFF_SIZE);
	return (0);
}

/*
** get_next_line:
** Возвращает 1, если строка была заполнена в строке, 0, если файл завершен
** для чтения и -1 в случае ошибки.
**
** Проверка BUFF_SIZE не выполняется первой, поэтому строка
** возможность повторной инициализации => позволяет избежать двойных ошибок
** в основной и мульти фд.
**
** Последняя проверка "* line! = NULL" позволяет не возвращать 0 сразу
** если файл заканчивается строкой без '\ n'.
*/

int		get_next_line(const int fd, char **line)
{
	static t_file	*file;
	t_file			*current;
	int				ret;

	if (!line)
		return (-1);
	*line = NULL;
	if (BUFF_SIZE < 0)
		return (-1);
	if (!(current = ft_find_or_create(&file, fd)))
		return (-1);
	if (ft_work_with_buff(current->buff, line) == 1)
		return (1);
	while ((ret = read(current->fd, current->buff, BUFF_SIZE)) > 0)
	{
		if (ft_work_with_buff(current->buff, line) == 1)
			return (1);
	}
	if (ret < 0)
		return (-1);
	if (*line != NULL)
		return (1);
	ft_remove_file(&file, fd);
	return (0);
}
