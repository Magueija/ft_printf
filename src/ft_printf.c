/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:52:51 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:26:49 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks is a spec is uppercase; if yes tag.upper 
**	is set to 1 and tag.spec to lower.
** @param:	- [ct_tag *] tag structure with the spec
**			- [char] spec in uppercase
*/
void	ft_isupper_spec(t_tag *tag, char upperspec)
{
	if (tag->spec == upperspec && ft_isalpha(upperspec))
	{
		tag->spec = ft_tolower(upperspec);
		tag->upper = 1;
	}
}

/*
** Prints the string between prtf.pstart and prtf.pend 
**	and sets prtf.pstart to prtf.pend.
** @param:	- [t_printf *] structure with needed variables
**			- [size_t] format position to be added to prtf.pend
*/
static void	ft_putstr_printf(t_printf *prtf, size_t ct)
{
	size_t	len;

	if (!prtf->pstart)
		prtf->pstart = prtf->format;
	if (ct > 0 && prtf->format[ct - 1] == 0)
		prtf->pend = &(prtf->format[ct - 1]);
	else
		prtf->pend = &(prtf->format[ct]);
	len = (size_t)(prtf->pend - prtf->pstart);
	prtf->len_printed += len;
	ft_putnstr_fd(((char *)(prtf->pstart)), len, FD_STDIN);
	prtf->pstart = prtf->pend;
}

/*
** Checks if the current position is a '%', then start the 
**	convertion of a conversion specification.
** @param:	- [t_printf *] printf structure with needed variables
**			- [size_t *] current position on format
**			- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
*/
static void	ft_ispercent(t_printf *prtf, size_t *ct, t_tag *tag, va_list *vlist)
{
	if (prtf->format[*ct] == '%'
		&& (prtf->format[*ct + 1] == '%' || prtf->format[*ct + 1] == '\0'))
	{
		ft_putstr_printf(prtf, *ct);
		ft_putchar_fd(prtf->format[(*ct)++], FD_STDIN);
		(prtf->len_printed)++;
		prtf->pstart = prtf->format + *ct
			+ ft_ternint((int)(prtf->format[*ct]), 1, 0);
	}
	else if (prtf->format[*ct] == '%')
	{
		ft_putstr_printf(prtf, *ct);
		*ct += ft_printformat(prtf, tag, vlist);
		prtf->pstart = prtf->pend;
		ft_cleartag(tag);
		if (prtf->pstart != prtf->pend)
			prtf->pstart = prtf->format + *ct;
	}
}

/*
** Cleans a tag structure; that is sets it to zero and 
**	 tag.width && tag.precision to the start value (-1).
** @param:	- [ct_tag *] structure to be cleaned
*/
void	ft_cleartag(t_tag *tag)
{
	ft_bzero(tag, sizeof(t_tag));
	tag->width = -1;
	tag->precision = -1;
}

/*
** Takes a format string and optional arguments and produce 
**	a formatted sequence of characters for output. The format 
**	string contains zero or more directives, which are either 
**	literal characters for output or encoded conversion 
**	specifications that describe how to format an argument in the output. 
**	A conversion specification consists of optional and required 
**	fields in this form: %[flags][width][.precision][length]specifier
** @param:	- [const char *] this is the string that 
**				contains the text to be written to stdout. 
**				It can optionally contain embedded format 
**				tags that are replaced by the values specified 
**				in subsequent additional arguments and 
**				formatted as requested. Format tags prototype 
**				is %[flags][width][.precision][length]specifier.
**			- [...] additional arguments − depending on the 
**				format string, the function may expect a 
**				sequence of additional arguments, each containing 
**				one value to be inserted instead of each %-tag 
**				specified in the format parameter (if any). 
**				There should be the same number of these arguments 
**				as the number of %-tags that expect a value.
** @return: [int] returns the number of characters printed 
**				(excluding the null byte used to end 
**				output to strings).
*/
int	ft_printf(const char *format, ...)
{
	t_printf	prtf;
	t_tag		tag;
	va_list		vlist;
	size_t		ct;

	ft_bzero(&prtf, sizeof(t_printf));
	prtf.format = format;
	ft_cleartag(&tag);
	va_start(vlist, format);
	ct = 0;
	while (prtf.format[ct])
	{
		ft_ispercent(&prtf, &ct, &tag, &vlist);
		if (!prtf.format[ct])
			break ;
		ct++;
	}
	va_end(vlist);
	ft_putstr_printf(&prtf, ct);
	return ((int)prtf.len_printed);
}
