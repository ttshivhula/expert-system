/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:51:07 by qmanamel          #+#    #+#             */
/*   Updated: 2017/06/01 16:51:09 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	if (!s || !f)
	{
		return (NULL);
	}
	str = (char *)ft_memalloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (s)
		while (s[i])
		{
			str[i] = f(i, (char)s[i]);
			i++;
		}
	return (str);
}
