/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:03:08 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/10 17:48:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	unsigned char	*ch;

	value = (unsigned char)c;
	ch = b;
	while (len--)
		*ch++ = value;
	return (b);
}
