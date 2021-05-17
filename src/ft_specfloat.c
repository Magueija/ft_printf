/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specfloat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:25:02 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:46:34 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fillzeros_float(t_tag *tag, char *str, char *sufix, int len)
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
** Converts the 'f' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convfloat(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		lenstr;
	char	prefix[4];
	int		pflen;
	char	*sufix;

	str = ft_checklen_float(tag, vlist);
	if (tag->spec == 'g')
		ft_removerightzeros_gf(str, tag);
	if (!ft_strchr(str, 'n') && tag->flags[2] && !ft_strchr(str, '.'))
	{
		sufix = ft_strjoin(str, ".");
		ft_swap((void **)&str, (void **)&sufix, 1);
	}
	lenstr = (int)ft_strlen(str);
	pflen = ft_prefix(tag, str, prefix);
	if (tag->width > pflen + lenstr)
		sufix = (char *)ft_malloc(tag->width - (pflen + lenstr)
				+ 1, sizeof(char));
	else
		sufix = (char *)ft_calloc(1, sizeof(char));
	ft_fillzeros_float(tag, str, sufix, pflen + lenstr);
	return (ft_finaljoin(tag, str, prefix, sufix));
}
