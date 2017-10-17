/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:45:29 by qmanamel          #+#    #+#             */
/*   Updated: 2017/05/29 11:53:59 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s1, int c, size_t n)
{
	char		tmp;
	char		*tmp2;

	tmp = (unsigned char)c;
	tmp2 = (char*)s1;
	while (n--)
	{
		if (*tmp2 == tmp)
			return (tmp2);
		tmp2++;
	}
	return (NULL);
}
