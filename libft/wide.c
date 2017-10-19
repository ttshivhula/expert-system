/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 08:48:59 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:47:45 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_putc1(wchar_t wc)
{
	ft_putchar((unsigned int)wc);
	return (1);
}

static	int		ft_putc2(wchar_t wc)
{
	unsigned int ud;

	ud = (unsigned int)wc;
	ft_putchar(192 | (ud >> 6 & 63));
	ft_putchar(128 | (ud & 63));
	return (2);
}

static	int		ft_putc3(wchar_t wc)
{
	unsigned int ud;

	ud = (unsigned int)wc;
	ft_putchar(224 | (ud >> 12 & 63));
	ft_putchar(128 | (ud >> 6 & 63));
	ft_putchar(128 | (ud & 63));
	return (3);
}

static	int		ft_putc4(wchar_t wc)
{
	unsigned int ud;

	ud = (unsigned int)wc;
	ft_putchar(240 | ((ud >> 18) & 63));
	ft_putchar(128 | ((ud >> 12) & 63));
	ft_putchar(128 | ((ud >> 6) & 63));
	ft_putchar(128 | (ud & 63));
	return (4);
}

int				ft_putwchar(wchar_t wc)
{
	unsigned int ud;

	ud = (unsigned int)wc;
	if (ud <= 127)
		return (ft_putc1(wc));
	else if (ud <= 2047)
		return (ft_putc2(wc));
	else if (ud <= 65535)
		return (ft_putc3(wc));
	else
		return (ft_putc4(wc));
}
