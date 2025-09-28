/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubletostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:09:39 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 20:05:58 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>
#include <stdio.h> // For debugging, can be removed later

char	*ft_doubletostr(double n, int precision)
{
	char	*str;
	char	*res;
	int		nbr;
	size_t	len;
	int		i;

	float abs_n = fabs(n);
	str = ft_lltoa((long)(abs_n));
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	str = ft_realloc(str, len + 1, len + precision + 2);
	if (str == NULL)
		return (NULL);
	str[len++] = '.';
	i = 0;
	nbr = 0;
	while (++i <= precision)
	{
		nbr = (abs_n - (long)abs_n) * powl(10, i) - nbr * powl(10, i - 1);
		str[len + i - 1] = '0' + nbr;
	}
	str[len + i - 1] = '\0';
	if (n < 0)
	{
		res = ft_strjoin("-", str);
		free(str);
		return (res);
	}
	return (str);
}
