/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:32:21 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/20 17:47:00 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	value;
	char	*str;

	value = (char)c;
	str = (char *)s;
	while (*str)
	{
		if (*str == value)
			return (str);
		str += 1;
	}
	if (value == '\0')
		return (str);
	return (NULL);
}
