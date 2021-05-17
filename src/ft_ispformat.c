/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:06:13 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:38:33 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks if c is a flag.
** @param:	- [char] char to be checked
*/
int	ft_isflag(char c)
{
	return (c == '-' || c == '+'
		|| c == ' ' || c == '#' || c == '0');
}

/*
** Checks if c is width.
** @param:	- [char] char to be checked
*/
int	ft_iswidth(char c)
{
	return (c == '*' || ft_isdigit(c));
}

/*
** Checks if c is precision.
** @param:	- [char] char to be checked
*/
int	ft_isprecision(char c1)
{
	return (c1 == '.');
}

/*
** Checks if c is length.
** @param:	- [char] char to be checked
*/
int	ft_islength(char c)
{
	return (c == 'h' || c == 'l' || c == 'L');
}

/*
** Checks if c is a specifier.
** @param:	- [char] char to be checked
*/
int	ft_isspecifier(char c)
{
	c = ft_tolower(c);
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'n' || c == 'f'
		|| c == 'g' || c == 'e' || c == 'o'
		|| c == '%');
}
