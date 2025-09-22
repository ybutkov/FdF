/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:23:07 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/19 13:23:27 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = dst;
	source = src;
	if (src - dst > 0)
		while (len--)
			*dest++ = *source++;
	else
		while (len--)
			dest[len] = source[len];
	return (dst);
}
