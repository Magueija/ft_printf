/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:23:54 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 16:45:22 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t
	ft_printblanck_c(t_tag *tag, char **dest, char *strflag, size_t len_strflag)
{
	if (len_strflag && tag->flags[0] == '-')
		ft_memcpy(&((*dest)[1]), strflag, len_strflag * sizeof(char));
	else if (len_strflag)
		ft_memcpy(*dest, strflag, len_strflag * sizeof(char));
	if (tag->flags[0] == '-')
		(*dest)[0] = 0;
	else
		(*dest)[len_strflag] = 0;
	(*dest)[len_strflag + 1] = 0;
	ft_putfstr_fd(*dest, len_strflag + 1, FD_STDIN);
	ft_free((void **)dest);
	return (len_strflag + 1);
}

static int	ft_precisiondeal_str(char **str, int precision)
{
	char	*temp;

	temp = ft_substr((const char *)*str, 0, precision);
	ft_free((void **)str);
	*str = temp;
	temp = NULL;
	return (precision);
}

static char	*ft_checkminus(t_printf *prtf, t_tag *tag, char *str, char *strflag)
{
	char	*dest;
	size_t	len_strflag;

	if (tag->spec == 'c' && str[0] == 0)
	{
		len_strflag = ft_strlen(strflag);
		dest = (char *)malloc((len_strflag + 2) * sizeof(char));
		if (dest)
			prtf->len_printed += ft_printblanck_c(tag,
					&dest, strflag, len_strflag);
	}
	else if (tag->flags[0] == '-')
		dest = ft_strjoin(str, strflag);
	else
		dest = ft_strjoin(strflag, str);
	ft_free((void **)&strflag);
	if (str[0] == 0 && !dest)
		return (NULL);
	else if (dest)
		return (dest);
	else
		return (ft_strdup("(null)"));
}

/*
** Converts the 'c' specifier to a string to be printed.
** @param:	- [t_printf *] printf structure for when '\\0' is printed
**			- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed 
**				if c isn't '\\0'
*/
char	*ft_convchar(t_printf *prtf, t_tag *tag, va_list *vlist)
{
	char	*str;
	char	*strflag;
	char	*dest;

	if (ft_strncmp(tag->length, "l", 2) == 0)
		str = ft_wctostr(va_arg(*vlist, wchar_t));
	else
		str = (char [2]){(va_arg(*vlist, int)), '\0'};
	if (tag->width > 1)
		strflag = (char *)ft_malloc(tag->width, sizeof(char));
	else
		strflag = (char *)ft_calloc(1, sizeof(char));
	dest = ft_checkminus(prtf, tag, str, strflag);
	if (ft_strncmp(tag->length, "l", 2) == 0)
		ft_free((void **)&str);
	return (dest);
}

/*
** Converts the 's' specifier to a string to be printed.
** @param:	- [t_tag *] tag structure for the conversions 
**			- [va_list *] va_list with the varibles needed for convertion
** @return: [char *] returns the string converted and ready to be printed
*/
char	*ft_convstr(t_tag *tag, va_list *vlist)
{
	char	*str;
	int		len;
	char	*strflag;
	char	*dest;

	if (ft_strncmp(tag->length, "l", 2) == 0)
		str = ft_strwctostr(va_arg(*vlist, wchar_t *));
	else
		str = va_arg(*vlist, char *);
	if (!str)
		str = ft_strdup("(null)");
	else if (ft_strncmp(tag->length, "l", 2) != 0)
		str = ft_strdup(str);
	len = (int)ft_strlen(str);
	if (tag->precision != -1 && tag->precision <= len)
		len = ft_precisiondeal_str((char **)&str, tag->precision);
	if (tag->width > len)
		strflag = (char *)ft_malloc(tag->width - len + 1, sizeof(char));
	else
		strflag = (char *)ft_calloc(1, sizeof(char));
	dest = ft_checkminus(NULL, tag, str, strflag);
	ft_free((void **)&str);
	return (dest);
}
