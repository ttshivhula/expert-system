/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:20:25 by qmanamel          #+#    #+#             */
/*   Updated: 2017/05/29 14:20:27 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*d;
	size_t	i;

	d = dest;
	i = 0;
	while (*dest)
		dest++;
	while (*src && i < n)
	{
		*dest++ = *src++;
		i++;
	}
	*dest = '\0';
	return (d);
}
