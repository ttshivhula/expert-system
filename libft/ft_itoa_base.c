/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:44:10 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:50:36 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					len_base(long long nb, int base)
{
	int				len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		if (base == 10)
			len++;
	}
	len++;
	nb /= base;
	while (nb)
	{
		len++;
		nb /= base;
	}
	return (len);
}

static char			*real_man_hardcode(long long n, int base)
{
	if ((n <= -9223372036854775807) && base == 10)
		return (ft_strdup("-9223372036854775808"));
	if ((n <= -9223372036854775807) && base == 16)
		return (ft_strdup("800000000000000"));
	if ((n <= -9223372036854775807) && base == 8)
		return (ft_strdup("1000000000000000000000"));
	return ("0");
}

char				*ft_itoa_base(long long n, int base)
{
	char			*ret;
	int				s;
	int				i;

	i = len_base(n, base);
	s = 0;
	if (n <= -9223372036854775807)
		return ((real_man_hardcode(n, base)));
	ret = (char *)malloc(sizeof(char) * (i + 1));
	ret[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		(base == 10) ? s = 1 : 0;
	}
	ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 87;
	n /= base;
	while (i >= 0)
	{
		if (i == 0 && s == 1)
			ret[i--] = '-';
		ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 87;
		n /= base;
	}
	return (ret);
}

char				*ft_itoa_base_cap(long long n, int base)
{
	char			*ret;
	int				s;
	int				i;

	i = len_base(n, base);
	s = 0;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (n <= -9223372036854775807)
		return ((real_man_hardcode(n, base)));
	ret[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		(base == 10) ? s = 1 : 0;
	}
	ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 55;
	n /= base;
	while (i >= 0)
	{
		if (i == 0 && s == 1)
			ret[i--] = '-';
		ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 55;
		n /= base;
	}
	return (ret);
}
