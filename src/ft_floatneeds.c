/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatneeds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:40:25 by tosilva           #+#    #+#             */
/*   Updated: 2021/04/21 11:49:18 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_checklen_float(t_tag *tag, va_list *vlist)
{
	char		*str;
	long double	nb;

	if (ft_strncmp(tag->length, "l", 2) == 0)
	{
		nb = va_arg(*vlist, long double);
		str = ft_ldtoa(nb, (unsigned int)
				ft_ternint(tag->precision != -1, tag->precision, 6));
	}
	else
	{
		nb = (long double)va_arg(*vlist, double);
		str = ft_dtoa(nb, (unsigned int)
				ft_ternint(tag->precision != -1, tag->precision, 6));
	}
	return (str);
}
