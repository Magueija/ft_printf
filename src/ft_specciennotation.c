/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specciennotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:38:31 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:45:39 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_checklen_cn(t_tag *tag, va_list *vlist)
{
	char		*str;

	if (ft_strncmp(tag->length, "l", 2) == 0)
	{
		str = ft_etoa(va_arg(*vlist, long double), (unsigned int)
				ft_ternint(tag->precision != -1, tag->precision, 6));
	}
	else
	{
		str = ft_etoa((long double)va_arg(*vlist, double), (unsigned int)
				ft_ternint(tag->precision != -1, tag->precision, 6));
	}
	return (str);
}

static char	*ft_checkcardinal(t_tag *tag, char *str)
{
	char	*temp;
	size_t	dot_pos;
	size_t	str_len;
	size_t	ct_str;
	size_t	ct_temp;

	if (!ft_strchr(str, 'n') && tag->flags[2] && !ft_strchr(str, '.'))
	{
		str_len = ft_strlen(str);
		temp = (char *)malloc((str_len + 2) * sizeof(char));
		temp[str_len + 1] = 0;
		dot_pos = ft_strchr(str, 'e') - str;
		ct_str = 0;
		ct_temp = 0;
		while (str[ct_str])
		{
			temp[ct_temp++] = str[ct_str++];
			if (ct_temp == dot_pos)
				temp[ct_temp++] = '.';
		}
		ft_swap((void **)&str, (void **)&temp, 1);
	}
	return (str);
}

static void	ft_fillzeros_cn(t_tag *tag, char *str, char *sufix, int len)
{
	if (sufix && !ft_strchr(str, 'n') && tag->flags[0] == '0'
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
** Converts the 'e' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convciennotation(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	str = ft_checklen_cn(tag, vlist);
	if (tag->spec == 'g')
		ft_removerightzeros_ge(str, tag);
	str = ft_checkcardinal(tag, str);
	lenstr = (int)ft_strlen(str);
	pflen = ft_prefix(tag, str, prefix);
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	ft_fillzeros_cn(tag, str, sufix, pflen + lenstr);
	return (ft_finaljoin(tag, str, prefix, sufix));
}
