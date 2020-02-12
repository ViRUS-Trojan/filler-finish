/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:06:30 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/12 18:14:17 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 42

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct		s_file
{
	int				fd;
	char			*buff;
	struct s_file	*next;
}					t_file;

t_file				*ft_create_elem(int fd);
t_file				*ft_find_or_create(t_file **begin, int fd);
void				ft_remove_file(t_file **begin, int fd);
int					ft_work_with_buff(char *buff, char **line);
int					get_next_line(const int fd, char **line);

#endif
