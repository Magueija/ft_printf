/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removerightzeros_g.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:02:07 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:40:14 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static short	ft_isinnbr(int c)
{
	if (c == '.' || ft_isdigit(c))
		return (1);
	return (0);
}

static void	ft_removerightzeros_ge__2(char **str, t_tag *tag, char **zeros)
{
	while (1)
	{
		*zeros = &(*str)[*zeros - *str - 1];
		if (*zeros && *zeros != *str
			&& (*(*zeros + 1) == 'e' || *(*zeros + 1) == ' ')
			&& (*(*zeros) == '0' || *(*zeros) == '.')
			&& ft_isinnbr((*str)[*zeros - *str - 1]))
		{
			if (*(*zeros) == '.')
			{
				*(*zeros) = ' ';
				tag->precision -= 1;
				break ;
			}
			else
				*(*zeros) = ' ';
			tag->precision -= 1;
		}
		if (!*zeros || *(*zeros) != ' '
			|| (*(*zeros + 1) != 'e' && *(*zeros + 1) != ' ')
			|| *zeros == *str || !ft_isinnbr((*str)[*zeros - *str - 1]))
			break ;
	}
}

static void	ft_removerightzeros_gf__2(char **str, t_tag *tag, char **zeros)
{
	while (1)
	{
		*zeros = &((*str)[*zeros - *str - 1]);
		if (*zeros && *zeros != *str && *(*zeros + 1) == 0
			&& (*(*zeros) == '0' || *(*zeros) == '.')
			&& ft_isinnbr((*str)[*zeros - *str - 1]))
		{
			if (*(*zeros) == '.')
			{
				*(*zeros) = 0;
				tag->precision -= 1;
				break ;
			}
			else
				*(*zeros) = 0;
			tag->precision -= 1;
		}
		if (!*zeros || **zeros != 0 || *(*zeros + 1) != 0
			|| *zeros == *str || !ft_isinnbr((*str)[*zeros - *str - 1]))
			break ;
	}
}

/*
* Removes right zeros in %g if %e is more suitable.
*/
void	ft_removerightzeros_ge(char *str, t_tag *tag)
{
	char	*zeros;
	char	*e_notation;

	tag->spec = 'e';
	if (!str || tag->flags[2] == '#'
		|| !ft_strrchr(str, '.'))
		return ;
	e_notation = ft_strrchr(str, 'e');
	zeros = e_notation;
	ft_removerightzeros_ge__2(&str, tag, &zeros);
	if (zeros)
		ft_memcpy((void *)ft_ternpt(*zeros == ' ', (void *)zeros,
				(void *)(zeros + 1), 0), (const void *)e_notation,
			(ft_strlen(e_notation) + 1) * sizeof(char));
}

/*
* Removes right zeros in %g if %f is more suitable.
*/
void	ft_removerightzeros_gf(char *str, t_tag *tag)
{
	char	*zeros;

	tag->spec = 'f';
	if (!str || tag->flags[2] == '#'
		|| !ft_strrchr(str, '.'))
		return ;
	zeros = ft_strrchr(str, '0');
	zeros += 1;
	ft_removerightzeros_gf__2(&str, tag, &zeros);
}
