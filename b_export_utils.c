/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:33:32 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:03:17 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	bubble_sort(char **mat)
{
	char	*place_holder;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (mat[i + 1])
	{
		j = i;
		while (mat[j + 1])
		{
			k = 0;
			while (mat[j][k] && mat[j + 1][k] && mat[j][k] == mat[j + 1][k])
				k++;
			if (mat[j][k] > mat[j + 1][k])
			{
				place_holder = mat[j];
				mat[j] = mat[j + 1];
				mat[j + 1] = place_holder;
			}
			j++;
		}
		i++;
	}
	return ;
}

int	no_equal(char *key_value)
{
	int	i;

	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	is_in_env(char *key, char **envp)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (!ft_strncmp(key, envp[i], key_len) && envp[i][key_len] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_key_value(char *arg, char **token)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	*token = &arg[i];
	if (!ft_isalpha(arg[i]))
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			equal = 1;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			if (equal == 0)
				return (0);
		i++;
	}
	if (!equal)
		return (1);
	return (2);
}
