/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 08:23:28 by qmanamel          #+#    #+#             */
/*   Updated: 2017/05/30 08:23:30 by qmanamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned int len;

	len = ft_strlen(str);
	while (len != 0 && str[len] != (char)c)
		len--;
	while (str[len] == (char)c)
		return ((char *)&str[len]);
	return (NULL);
}
