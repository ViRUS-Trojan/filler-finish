/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:16:37 by vdelsie           #+#    #+#             */
/*   Updated: 2020/02/12 13:16:38 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
    size_t	i;
    size_t	size;

    i = 0;
    size = ft_strlen(s1);
    while (s2[i] != '\0')
    {
        s1[size + i] = s2[i];
        i++;
    }
    s1[size + i] = '\0';
    return (s1);
}
