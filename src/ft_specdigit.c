/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 09:53:27 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:45:59 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_checklen_unsig(t_tag *tag, va_list *vlist)
{
	char	*str;

	if (ft_strncmp(tag->length, "h", 2) == 0)
		str = ft_uhitoa((unsigned short)va_arg(*vlist, unsigned int));
	else if (ft_strncmp(tag->length, "hh", 3) == 0)
		str = ft_uitoa((unsigned int)(
					(unsigned char)va_arg(*vlist, unsigned int)));
	else if (ft_strncmp(tag->length, "l", 2) == 0)
		str = ft_ulitoa(va_arg(*vlist, unsigned long));
	else if (ft_strncmp(tag->length, "ll", 3) == 0)
		str = ft_ullitoa(va_arg(*vlist, unsigned long long));
	else
		str = ft_uitoa(va_arg(*vlist, unsigned int));
	return (str);
}

static char	*ft_checklen_int(t_tag *tag, va_list *vlist)
{
	char	*str;

	if (ft_strncmp(tag->length, "h", 2) == 0)
		str = ft_hitoa((short)va_arg(*vlist, int));
	else if (ft_strncmp(tag->length, "hh", 3) == 0)
		str = ft_itoa((int)((char)va_arg(*vlist, int)));
	else if (ft_strncmp(tag->length, "l", 2) == 0)
		str = ft_litoa(va_arg(*vlist, long));
	else if (ft_strncmp(tag->length, "ll", 3) == 0)
		str = ft_llitoa(va_arg(*vlist, long long));
	else
		str = ft_itoa(va_arg(*vlist, int));
	return (str);
}

static void	ft_fillzeros_digits(t_tag *tag, char *str, char *sufix, int len)
{
	if (sufix && tag->flags[0] == '0' && tag->precision == -1
		&& tag->width > len)
	{
		ft_memset((void *)sufix, '0',
			(tag->width - len) * sizeof(char));
		if (ft_strchr(str, '-'))
		{
			sufix[0] = '-';
			str[0] = '0';
		}
	}
}

/*
** Converts the 'i', 'd' and 'u' specifiers to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convdigit(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	if (tag->spec == 'u')
		str = ft_checklen_unsig(tag, vlist);
	else
		str = ft_checklen_int(tag, vlist);
	pflen = ft_prefix(tag, str, prefix);
	lenstr = (int)ft_strlen(str);
	lenstr -= ft_ternint(tag->precision > lenstr - 1
			&& (int)((long long)ft_strchr(str, '-')), 1, 0);
	lenstr = ft_checkprec_dig(tag, &str, lenstr);
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	ft_fillzeros_digits(tag, str, sufix, pflen + lenstr);
	return (ft_finaljoin(tag, str, prefix, sufix));
}
