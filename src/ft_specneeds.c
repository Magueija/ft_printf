/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specneeds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:54:34 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:57:40 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Fills the prefix depending on the 
**	conversion specification and on the flags  
** @param:	- [t_tag *] tag structure with the flags
**			- [char *] converted string
**			- [char *] prefix
** @return: [char *] returns the prefix lenght
*/
int	ft_prefix(t_tag *tag, char *str, char *prefix)
{
	size_t	ct;

	ct = 0;
	if (tag->flags[1] && str[0] != '-'
		&& (tag->spec != 'u' && tag->spec != 'o'
			&& tag->spec != 'x' && tag->spec != '%'))
		if ((tag->spec != 'f' && tag->spec != 'e')
			|| ((tag->spec == 'f' || tag->spec == 'e')
				&& ft_strncmp(str, "nan", 4) != 0))
			prefix[ct++] = tag->flags[1];
	if (tag->spec == 'p'
		|| (tag->flags[2] && ft_strncmp(str, "0", 2) != 0 && tag->spec == 'x'))
	{
		prefix[ct++] = '0';
		prefix[ct++] = 'x';
	}
	else if (tag->flags[2] && tag->spec == 'o'
		&& (ft_strncmp(str, "0", 2) != 0 || tag->precision == 0))
	{
		prefix[ct++] = '0';
		if (tag->precision > 0)
			tag->precision -= 1;
	}
	prefix[ct] = 0;
	return ((int)ft_strlen(prefix));
}

/*
** Checks if the precision has impact on the converted string 
**	and if it has, then the converted string is changed as needed.
** @param:	- [t_tag *] tag structure with the flags
**			- [char **] pointer to the converted string
**			- [int] converted string lenght
** @return: [char *] returns the new converted string 
**				lenght if modified
*/
int	ft_checkprec_dig(t_tag *tag, char **str, int lenstr)
{
	char	*temp;
	char	*joined;
	int		ct;

	if (tag->precision > lenstr)
	{
		temp = ft_malloc(tag->precision - lenstr + 1, sizeof(char));
		joined = ft_strjoin(temp, *str);
		ft_free((void **)&temp);
		ct = 0;
		if (ft_strchr(*str, '-'))
			joined[ct++] = '-';
		ft_memset((void *)&joined[ct], '0',
			(tag->precision - lenstr) * sizeof(char));
		ft_swap((void **)str, (void **)&joined, 1);
		return (tag->precision + ft_ternint(ct, 1, 0));
	}
	else if (tag->precision == 0 && ft_strncmp(*str, "0", 2) == 0)
	{
		ft_free((void **)str);
		*str = ft_strdup("");
		return (tag->precision);
	}
	return (lenstr);
}

static void	ft_final_freept(char *str, char *sufix, char *temp)
{
	ft_free((void **)&str);
	ft_free((void **)&sufix);
	ft_free((void **)&temp);
}

/*
** Depending on the conversion specification and on the flags 
**	joins the converted string with its prefix and sufix.
** @param:	- [t_tag *] tag structure with the flags
**			- [char *] converted string
**			- [char *] prefix
**			- [char *] sufix
** @return: [char *] returns the converted string with 
**				its prefix and sufix - ready to be printed
*/
char	*ft_finaljoin(t_tag *tag, char *str, char *prefix, char *sufix)
{
	char	*temp;
	char	*dest;

	if ((!str || !prefix || !sufix) && tag->spec == 's')
	{
		ft_free((void **)&str);
		ft_free((void **)&sufix);
		return (ft_strdup("(null)"));
	}
	if (tag->flags[0] == '-')
		temp = (char *)ft_strjoin(prefix, str);
	else if ((((tag->flags[0] && tag->precision == -1)
				|| (tag->flags[0] && tag->spec == 'f')) && (tag->spec != 'c'
				&& tag->spec != 's')) || (tag->spec == 'c' || tag->spec == 's'))
		temp = (char *)ft_strjoin(prefix, sufix);
	else
		temp = (char *)ft_strjoin(sufix, prefix);
	if (tag->flags[0] == '-')
		dest = (char *)ft_strjoin(temp, sufix);
	else
		dest = (char *)ft_strjoin(temp, str);
	ft_final_freept(str, sufix, temp);
	if (dest)
		return (dest);
	return (NULL);
}
