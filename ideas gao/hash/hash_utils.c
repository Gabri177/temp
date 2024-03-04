/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:30:52 by yugao             #+#    #+#             */
/*   Updated: 2024/03/03 02:02:23 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hash.h"

int		ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*new;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen ((char *)str);
	new = (char *) malloc (sizeof (char) * (len + 1));
	if (!new)
		return (0);
	while (i < len)
	{
		new[i] = str[i];
		i ++;
	}
	new[i] = '\0';
	return (new);
}

t_bool	is_strsame(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (FALSE);
		s1 ++;
		s2 ++;
	}
	return (*s1 == *s2);
}

int	hash_func(char *key)
{
	unsigned int	hash_val;
	int				i;

	hash_val = 0;
	i = 0;
	while (i < ft_strlen (key))
	{
		hash_val += key[i];
		i ++;
	}
	return (hash_val % HASH_SIZE);
}
