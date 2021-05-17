/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:53:12 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:43:52 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_negwidth(t_tag *tag)
{
	if (tag->width < 0)
	{
		tag->flags[0] = '-';
		tag->width = -(tag->width);
	}
}

static const char
	*ft_getlast(t_printf *prtf, size_t *ct, t_tag *tag, va_list *vlist)
{
	short	sort;

	sort = 0;
	while (prtf->pstart[++(*ct)])
	{
		if (ft_isflag(prtf->pstart[*ct]) && sort == 0)
			ft_fillflag(tag, prtf->pstart[*ct]);
		else if (ft_iswidth(prtf->pstart[*ct]) && sort <= 1)
		{
			tag->width = ft_fillwidth(prtf, ct, vlist, &sort);
			ft_negwidth(tag);
		}
		else if (ft_isprecision(prtf->pstart[*ct]) && sort <= 2)
			tag->precision = ft_fillprecision(prtf, ct, vlist, &sort);
		else if (ft_islength(prtf->pstart[*ct]) && sort <= 3)
			ft_filllength(tag, prtf->pstart[*ct], &sort);
		else if (ft_isspecifier(prtf->pstart[*ct]) && sort < 4)
			ft_fillspecifier(tag, prtf->pstart[*ct], &sort);
		else
			break ;
	}
	if (sort == 4)
		return (prtf->pstart + (*ct)--);
	return (NULL);
}

static void	ft_convspecifier_bonus(t_printf *prtf, t_tag *tag, va_list *vlist)
{
	if (tag->spec == 'f')
		prtf->toprint = ft_convfloat(tag, vlist);
	else if (tag->spec == 'e')
		prtf->toprint = ft_convciennotation(tag, vlist);
	else if (tag->spec == 'g')
		prtf->toprint = ft_convg(tag, vlist);
	else if (tag->spec == 'o')
		prtf->toprint = ft_convoctal(tag, vlist);
	else if (tag->spec == 'n')
		ft_convn(prtf, tag, vlist);
}

static void	ft_convspecifier(t_printf *prtf, t_tag *tag, va_list *vlist)
{
	if (tag->spec == 'c')
		prtf->toprint = ft_convchar(prtf, tag, vlist);
	else if (tag->spec == 's')
		prtf->toprint = ft_convstr(tag, vlist);
	else if (tag->spec == 'p')
		prtf->toprint = ft_convpt(tag, vlist);
	else if (tag->spec == 'd' || tag->spec == 'i'
		|| tag->spec == 'u')
		prtf->toprint = ft_convdigit(tag, vlist);
	else if (tag->spec == 'x')
		prtf->toprint = ft_convhex(tag, vlist);
	else if (tag->spec == '%')
		prtf->toprint = ft_convpercent(tag);
	else
		ft_convspecifier_bonus(prtf, tag, vlist);
	if (tag->upper == 1)
		ft_strconvchar(prtf->toprint, &ft_toupper);
}

/*
** Checks if a conversion specification is valid, if it is, 
**	then convert it and print it to stdin.
** @param:	- [t_printf *] printf structure with the conversion specification
**			- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [size_t] returns the new format positon; that is 
**				the position next to the conversion specification
*/
size_t	ft_printformat(t_printf *prtf, t_tag *tag, va_list *vlist)
{
	size_t	ct;

	ct = 0;
	prtf->pend = ft_getlast(prtf, &ct, tag, vlist);
	if (!prtf->pend)
		return (ct);
	ft_convspecifier(prtf, tag, vlist);
	if (prtf->toprint)
	{
		ct = ft_strlen(prtf->toprint);
		ft_putfstr_fd(prtf->toprint, ct, FD_STDIN);
		if (tag->spec == 'c')
		{
			ct += ft_ternint(prtf->toprint[ft_ternint(tag->width > 1,
						tag->width - 1, 0)] == '\0', 1, 0);
			if (tag->flags[0] == '-')
				prtf->len_printed += ft_ternint(tag->width > 1, tag->width, ct);
			else
				prtf->len_printed += ct;
		}
		else
			prtf->len_printed += ct;
		ft_free((void **)(&(prtf->toprint)));
	}
	return (prtf->pend - prtf->pstart - 1);
}
