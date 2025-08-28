/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:55:22 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/28 14:43:33 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

// String utilities
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		isstrequal(const char *s1, const char *s2);

// Character utilities
int		ft_isalpha(const char c);
int		ft_isspace(const char c);
int		ft_isschar(const char c);
int		ft_isalnum(const char c);

// Conversion utilities
long long		ft_atoll(const char *str, int *overflow);

// Output utilities
void	ft_printstderr(const char *str);

// Array utilities
void	sort_string_array(char **arr, int size);

// Token utilities

#endif