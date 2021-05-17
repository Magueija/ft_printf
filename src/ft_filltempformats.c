/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filltempformats.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:19:30 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:38:04 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks if c is a flag, if it is, add it to tag.
** @param:	- [t_tag *] tag structure 
**			- [char] char to be checked
*/
void	ft_fillflag(t_tag *tag, char c)
{
	if (c == '-' || c == '0')
	{
		if (c == '0' && tag->flags[0] != '-')
			tag->flags[0] = '0';
		else
			tag->flags[0] = '-';
	}
	else if (c == '+' || c == ' ')
	{
		if (c == ' ' && tag->flags[1] != '+')
			tag->flags[1] = ' ';
		else
			tag->flags[1] = '+';
	}
	else if (c == '#')
		tag->flags[2] = '#';
}

/*
** Checks if c is width, if it is, add it to tag.
** @param:	- [t_tag *] tag structure 
**			- [char] char to be checked
**			- [short *] positon of the spec, needed for 
**				the verification of a valid conversion specification
*/
int	ft_fillwidth(t_printf *prtf, size_t *ct, va_list *vlist, short *sort)
{
	int		n;

	*sort = 1;
	if (ft_isdigit(prtf->pstart[*ct]))
	{
		n = ft_atoi((const char *)&prtf->pstart[*ct]);
		while (prtf->pstart[*ct] && ft_isdigit(prtf->pstart[*ct]))
			*ct = *ct + 1;
		(*ct)--;
		return (n);
	}
	else
		return (va_arg(*vlist, int));
}

/*
** Checks if c is precision, if it is, add it to tag.
** @param:	- [t_tag *] tag structure 
**			- [char] char to be checked
**			- [short *] positon of the spec, needed for 
**				the verification of a valid conversion specification
*/
int	ft_fillprecision(t_printf *prtf, size_t *ct, va_list *vlist, short *sort)
{
	int		n;

	*sort = 2;
	if (ft_isdigit(prtf->pstart[*ct + 1]))
	{
		n = ft_atoi((const char *)&prtf->pstart[++(*ct)]);
		while (prtf->pstart[*ct] && ft_isdigit(prtf->pstart[*ct]))
			*ct = *ct + 1;
		(*ct)--;
		return (n);
	}
	else if (prtf->pstart[*ct + 1] == '*')
	{
		*ct = *ct + 1;
		n = va_arg(*vlist, int);
		return (ft_ternint(n >= 0, n, -1));
	}
	else
		return (0);
}

/*
** Checks if c is length, if it is, add it to tag.
** @param:	- [t_tag *] tag structure 
**			- [char] char to be checked
**			- [short *] positon of the spec, needed for 
**				the verification of a valid conversion specification
*/
void	ft_filllength(t_tag *tag, char c, short *sort)
{
	*sort = 3;
	if (tag->length[0])
		tag->length[1] = c;
	else
		tag->length[0] = c;
}

/*
** Checks if c is a specifier, if it is, add it to tag.
** @param:	- [t_tag *] tag structure 
**			- [char] char to be checked
**			- [short *] positon of the spec, needed for 
**				the verification of a valid conversion specification
*/
void	ft_fillspecifier(t_tag *tag, char c, short *sort)
{
	*sort = 4;
	tag->spec = c;
	ft_isupper_spec(tag, ft_toupper(tag->spec));
}
