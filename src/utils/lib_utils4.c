/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:29 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_split_strndup(const char *s, char c)
{
	char	*src;
	char	*dest;
	int		size;

	size = 0;
	while (s[size])
	{
		if (s[size] == c)
			break ;
		size++;
	}
	if (s == NULL)
		return (NULL);
	src = (char *)s;
	dest = ft_calloc(size + 1, 1);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, size + 1);
	dest = ft_memcpy(dest, src, size);
	return (dest);
}

void	*free_all(char **strs, int count)
{
	int	ind;

	ind = -1;
	while (++ind < count)
		free(strs[ind]);
	free(strs);
	return (NULL);
}

char	**alloc_mem(int str_count)
{
	char	**ret;

	ret = malloc((str_count + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	ret[str_count] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	*str;
	int		str_count;
	int		indv;

	if (s == NULL)
		return (NULL);
	indv = 0;
	str = (char *)s;
	str_count = ft_str_count(str, c);
	ret = alloc_mem(str_count);
	if (ret == NULL)
		return (NULL);
	while (str_count-- > 0)
	{
		while (*str == c && *str)
			str++;
		ret[indv] = ft_split_strndup(str, c);
		if (ret[indv] == NULL && indv != str_count)
			return (free_all(ret, indv));
		indv++;
		while (*str != c && *str)
			str++;
	}
	return (ret);
}

char	*ft_dtoa_fixed(double v)
{
	char	*a;
	char	*b;
	char	*tmp;
	int		iv;
	int		frac;

	iv = (int)v;
	frac = (int)((v - iv) * 1000);
	if (frac < 0)
		frac = -frac;
	a = ft_itoa(iv);
	b = ft_itoa(frac);
	tmp = ft_strjoin(a, ".");
	free(a);
	a = ft_strjoin(tmp, b);
	free(tmp);
	free(b);
	return (a);
}
