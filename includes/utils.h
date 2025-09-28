/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:59:35 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 15:31:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_str_capitalise(char *str);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_toupper(int c);
int			ft_putstr(char *str);
long		ft_abs(long value);
int			ft_sign(int x);
long		base_to_long(char *nbr, char *base_from);
char		*ft_ultoa(unsigned long n);
char		*ft_lltoa(long long n);
char		*ft_doubletostr(double n, int precision);
void		error_and_exit(void);
long int	get_time_in_milliseconds(void);
int			between(long long value, long long left, long long right);
int			in_set(char ch, char *set);

#endif