/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:37:14 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/23 18:12:41 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *str)
{
	int	x;

	x = 0;
	if (!str)
		return (x);
	while (str[x] != '\0')
		x++;
	return (x);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	x;

	x = 0;
	if (!s1 || !s2)
		return (x);
	while ((s1[x] || s2[x]) && s1[x] == s2[x])
		x++;
	return (s1[x] - s2[x]);
}

int	ft_strchr2(char *str, char *set)
{
	int	i;

	if (!str || !set)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_strchr(str, set[0]) && ft_strchr(str, set[1]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strrmv(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_strdup(const char *s1)
{
	size_t	x;
	size_t	i;
	char	*dest;

	if (!s1)
		return (NULL);
	x = 0;
	while (s1[x])
		x++;
	x++;
	dest = (char *)malloc(sizeof(char) * x);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
