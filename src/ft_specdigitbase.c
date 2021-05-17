/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specdigitbase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 09:53:23 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:46:22 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_checklen_hex(t_tag *tag, va_list *vlist)
{
	char	*str;

	if (ft_strncmp(tag->length, "h", 2) == 0)
		str = ft_uitoh((unsigned long long)
				((unsigned short)va_arg(*vlist, unsigned int)), 0);
	else if (ft_strncmp(tag->length, "hh", 3) == 0)
		str = ft_uitoh((unsigned long long)
				((unsigned char)va_arg(*vlist, unsigned int)), 0);
	else if (ft_strncmp(tag->length, "l", 2) == 0)
		str = ft_uitoh((unsigned long long)va_arg(*vlist, unsigned long), 0);
	else if (ft_strncmp(tag->length, "ll", 3) == 0)
		str = ft_uitoh(va_arg(*vlist, unsigned long long), 0);
	else
		str = ft_uitoh((unsigned long long)va_arg(*vlist, unsigned int), 0);
	return (str);
}

static char	*ft_checklen_octal(t_tag *tag, va_list *vlist)
{
	char	*str;

	if (ft_strncmp(tag->length, "h", 2) == 0)
		str = ft_uitoo((unsigned long long)
				((unsigned short)va_arg(*vlist, unsigned int)), 0);
	else if (ft_strncmp(tag->length, "hh", 3) == 0)
		str = ft_uitoo((unsigned long long)
				((unsigned char)va_arg(*vlist, unsigned int)), 0);
	else if (ft_strncmp(tag->length, "l", 2) == 0)
		str = ft_uitoo((unsigned long long)va_arg(*vlist, unsigned long), 0);
	else if (ft_strncmp(tag->length, "ll", 3) == 0)
		str = ft_uitoo(va_arg(*vlist, unsigned long long), 0);
	else
		str = ft_uitoo((unsigned long long)va_arg(*vlist, unsigned int), 0);
	return (str);
}

/*
** Converts the 'x' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convhex(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	str = ft_checklen_hex(tag, vlist);
	lenstr = (int)ft_strlen(str);
	pflen = ft_prefix(tag, str, prefix);
	lenstr = ft_checkprec_dig(tag, &str, lenstr);
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	if (sufix && tag->flags[0] == '0' && tag->precision == -1
		&& tag->width > pflen + lenstr)
		ft_memset((void *)sufix, '0',
			(tag->width - (pflen + lenstr)) * sizeof(char));
	return (ft_finaljoin(tag, str, prefix, sufix));
}

/*
** Converts the 'o' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convoctal(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	str = ft_checklen_octal(tag, vlist);
	lenstr = (int)ft_strlen(str);
	pflen = ft_prefix(tag, str, prefix);
	lenstr = ft_checkprec_dig(tag, &str, lenstr);
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	if (sufix && tag->flags[0] == '0' && tag->precision == -1
		&& tag->width > pflen + lenstr)
		ft_memset((void *)sufix, '0',
			(tag->width - (pflen + lenstr)) * sizeof(char));
	return (ft_finaljoin(tag, str, prefix, sufix));
}
