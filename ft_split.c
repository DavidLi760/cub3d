/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:55:46 by davli             #+#    #+#             */
/*   Updated: 2024/09/04 17:09:07 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (c != set[i] && set[i])
		i++;
	if (!set[i])
		return (0);
	return (1);
}

int	count_words(char *str, char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_charset(str[i], set))
			i++;
		if (!is_charset(str[i], set) && str[i])
		{
			while (!is_charset(str[i], set) && str[i])
				i++;
			count++;
		}
	}
	return (count);
}

int	count_letters(char *str, char *set, int *i)
{
	int	j;

	j = 0;
	while (!is_charset(str[*i + j], set) && str[*i + j])
		j++;
	return (j);
}

char	*make_tab(char *str, char *set, int *j)
{
	int		i;
	char	*split;

	i = 0;
	if (!str[*j])
		return (0);
	split = malloc(sizeof(char) * count_letters(str, set, j) + 1);
	while (!is_charset(str[*j], set) && str[*j])
	{
		split[i] = str[*j];
		i++;
		(*j)++;
	}
	split[i] = 0;
	return (split);
}

char	**ft_split(char *str, char *set)
{
	int		i;
	int		j;
	char	**split;

	if (count_words(str, set) < 1)
		return (0);
	split = malloc(sizeof(char *) * (count_words(str, set) + 1));
	i = -1;
	j = 0;
	while (++i < count_words(str, set))
	{
		while (is_charset(str[j], set) && str[j])
			j++;
		if (str[j])
			split[i] = make_tab(str, set, &j);
	}
	split[i] = 0;
	return (split);
}

// int	main()
// {
// 	char	*str = "         \n    ";
// 	char	*str1 = "Salut j'espere\nque\nvous allez bien  \n";
// 	char	*str2 = "    Salut j'espere\nque\nvous allez bien   ";
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split = ft_split(str1, " \n");
// 	while (split[i])
// 		printf("%s\n", split[i++]);
// 	while (i >= 0)
// 		free(split[i--]);
// 	free(split);
// 	return (0);
// }