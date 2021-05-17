/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:53:09 by tosilva           #+#    #+#             */
/*   Updated: 2021/05/17 15:57:44 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

/*
** Printf structure to print
** @param:	- [const char *] format
**			- [const char *] start of format to print
**			- [const char *] end of format to print
**			- [char *] flag ready to print (%...)
**			- [size_t] lenght printed
*/
typedef struct s_printf
{
	const char	*format;
	const char	*pstart;
	const char	*pend;
	char		*toprint;
	size_t		len_printed;
}				t_printf;

/*
** Tags structure for %...
** @param:	- [char] flags[0]: '-' or '0' 
**				flags[1]: '+' or ' ' 
**				flags[2]: '#'
**			- [int] width
**			- [int] precision
**			- [char] length
**			- [char] specifier
**			- [short] 1 if spec is uppercase, 0 if not
*/
typedef struct s_tag
{
	char	flags[3];
	int		width;
	int		precision;
	char	length[3];
	char	spec;
	short	upper;
}				t_tag;

int		ft_printf(const char *format, ...);
size_t	ft_printformat(t_printf *prtf, t_tag *tag, va_list *vlist);

int		ft_isflag(char c);
int		ft_iswidth(char c);
int		ft_isprecision(char c1);
int		ft_islength(char c);
int		ft_isspecifier(char c);

void	ft_fillflag(t_tag *tag, char c);
int		ft_fillwidth(t_printf *prtf, size_t *ct, va_list *vlist, short *sort);
int		ft_fillprecision(t_printf *prtf, size_t *ct,
			va_list *vlist, short *sort);
void	ft_filllength(t_tag *tag, char c, short *sort);
void	ft_fillspecifier(t_tag *tag, char c, short *sort);

void	ft_cleartag(t_tag *tag);
void	ft_isupper_spec(t_tag *tag, char upperspec);
int		ft_prefix(t_tag *tag, char *str, char *prefix);
int		ft_checkprec_dig(t_tag *tag, char **str, int strlen);
char	*ft_finaljoin(t_tag *tag, char *str, char *prefix, char *sufix);

char	*ft_checklen_float(t_tag *tag, va_list *vlist);
void	ft_removerightzeros_gf(char *str, t_tag *tag);
void	ft_removerightzeros_ge(char *str, t_tag *tag);

char	*ft_convchar(t_printf *prtf, t_tag *tag, va_list *vlist);
char	*ft_convstr(t_tag *tag, va_list *vlist);
char	*ft_convdigit(t_tag *tag, va_list *vlist);
char	*ft_convfloat(t_tag *tag, va_list *vlist);
char	*ft_convciennotation(t_tag *tag, va_list *vlist);
char	*ft_convg(t_tag *tag, va_list *vlist);
char	*ft_convhex(t_tag *tag, va_list *vlist);
char	*ft_convoctal(t_tag *tag, va_list *vlist);
char	*ft_convpt(t_tag *tag, va_list *vlist);
char	*ft_convpercent(t_tag *tag);
void	ft_convn(t_printf *prtf, t_tag *tag, va_list *vlist);

#endif