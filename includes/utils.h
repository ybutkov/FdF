/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:59:35 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/21 16:03:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_str_capitalise(char *str);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		ft_toupper(int c);
int		ft_putstr(char *str);
long	ft_abs(long value);
int		ft_sign(int x);
long	base_to_long(char *nbr, char *base_from);
void	error_and_exit(void);

#endif