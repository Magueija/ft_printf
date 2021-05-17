/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specspecial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:21:04 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:49:00 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Converts the 'p' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convpt(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	str = ft_uitoh((unsigned long long)va_arg(*vlist, void *), 0);
	lenstr = (int)ft_strlen(str);
	pflen = ft_prefix(tag, str, prefix);
	if (lenstr == 1 && tag->precision != -1 && tag->precision <= lenstr)
	{
		str[tag->precision] = 0;
		lenstr = tag->precision;
	}
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	if (sufix && tag->flags[0] == '0' && tag->width > pflen + lenstr)
		ft_memset((void *)sufix, '0',
			(tag->width - (pflen + lenstr)) * sizeof(char));
	return (ft_finaljoin(tag, str, prefix, sufix));
}

static short	ft_convn_short(t_printf *prtf, t_tag *tag, va_list *vlist)
{
	short		*pth;
	char		*pthh;

	if (ft_strncmp(tag->length, "h", 2) == 0)
	{
		pth = (short *)va_arg(*vlist, void *);
		if (pth)
			*pth = (short)prtf->len_printed;
		return (1);
	}
	else if (ft_strncmp(tag->length, "hh", 3) == 0)
	{
		pthh = (char *)va_arg(*vlist, void *);
		if (pthh)
			*pthh = (char)prtf->len_printed;
		return (1);
	}
	return (0);
}

/*
** Sets the value of the given int to the length already printed.
** @param:	- [t_printf *] printf structure with the lenght printed
**			- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varible needed
*/
void	ft_convn(t_printf *prtf, t_tag *tag, va_list *vlist)
{
	int			*pti;
	long		*ptl;
	long long	*ptll;

	if (ft_convn_short(prtf, tag, vlist))
		;
	else if (ft_strncmp(tag->length, "l", 2) == 0)
	{
		ptl = (long *)va_arg(*vlist, void *);
		if (ptl)
			*ptl = (long)prtf->len_printed;
	}
	else if (ft_strncmp(tag->length, "ll", 3) == 0)
	{
		ptll = (long long *)va_arg(*vlist, void *);
		if (ptll)
			*ptll = (long long)prtf->len_printed;
	}
	else
	{
		pti = (int *)va_arg(*vlist, void *);
		if (pti)
			*pti = (int)prtf->len_printed;
	}
}

/*
** Converts the '%' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convpercent(t_tag *tag)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	str = ft_strdup("%");
	lenstr = 1;
	pflen = ft_prefix(tag, str, prefix);
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	if (sufix && tag->flags[0] == '0' && tag->width > pflen + lenstr)
		ft_memset((void *)sufix, '0',
			(tag->width - (pflen + lenstr)) * sizeof(char));
	return (ft_finaljoin(tag, str, prefix, sufix));
}
