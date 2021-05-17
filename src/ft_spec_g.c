/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_g.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:12:33 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:42:42 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_checkneg2(long double *n, int *exp, int neg)
{
	if (neg == 2)
		*n += 1.0L;
	if (*n >= 10.0L)
		*exp += 1;
}

static void	ft_roundprec(long double n_original,
				long double *n, unsigned short prec, int *exp)
{
	long double	n_copy;
	long double	prec_pow;

	if ((int)*n == 9 || (int)((unsigned long long)n_original % 2ULL) == 0)
	{
		n_copy = *n;
		prec_pow = ft_powld(10.0L, prec);
		if ((int)*n == 9 && (int)
			((unsigned long long)(*n * (prec_pow * 10.0L)) % 10ULL) >= 5)
		{
			n_copy += 1.0L / prec_pow;
			if ((int)n_copy == 10)
			{
				*n += 1.0L / prec_pow;
				*n /= 10.0L;
				*exp += 1;
			}
		}
	}
}

static int	ft_getexp(long double n, unsigned short prec, int neg)
{
	int			exp;
	long double	n_original;

	n_original = n;
	exp = 0;
	if (n > 1.0L)
	{
		while (n >= 10.0L)
		{
			n /= 10.0L;
			exp += 1;
		}
	}
	else if (n < 1.0L && n > 0.0L)
	{
		while (n < 1.0L)
		{
			n *= 10.0L;
			exp -= 1;
		}
	}
	ft_checkneg2(&n, &exp, neg);
	ft_roundprec(n_original, &n, prec, &exp);
	return (exp);
}

static char	*ft_chooseconvertion(t_tag *tag, va_list *vlist, int exp)
{
	char		*str;

	if (tag->precision > exp && exp >= -4)
	{
		tag->precision -= exp + 1;
		str = ft_convfloat(tag, vlist);
	}
	else
	{
		tag->precision -= 1;
		str = ft_convciennotation(tag, vlist);
	}
	return (str);
}

/*
** Converts the 'g' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convg(t_tag *tag, va_list *vlist)
{
	va_list		vlist_cp;
	char		*str;
	long double	nb;
	int			neg;
	int			exp;

	va_copy(vlist_cp, *vlist);
	if (ft_strncmp(tag->length, "l", 2) == 0)
		nb = va_arg(vlist_cp, long double);
	else
		nb = (long double)va_arg(vlist_cp, double);
	neg = ft_isnegative_float((void *)&nb);
	tag->precision = ft_ternint(tag->precision != -1,
			ft_ternint(tag->precision != 0, tag->precision, 1), 6);
	if (ft_isnan(nb) || ft_isinf(nb) || ft_isninf(nb))
		exp = tag->precision - 1;
	else
		exp = ft_getexp(nb, tag->precision - 1, neg);
	str = ft_chooseconvertion(tag, vlist, exp);
	va_end(vlist_cp);
	return (str);
}
