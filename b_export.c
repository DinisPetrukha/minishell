/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:38:28 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/06 15:28:39 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	print_export(char **mat)
{
	char	**sorted_mat;
	int		i;

	sorted_mat = matcpy(mat);
	bubble_sort(sorted_mat);
	i = 0;
	while (sorted_mat[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted_mat[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free_mat(sorted_mat);
}

void	unset_env(char *key, char ***envp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while ((*envp)[i])
	{
		j = 0;
		while ((*envp)[i][j] && (*envp)[i][j] != '=')
			j++;
		if (!ft_strncmp((*envp)[i], key, j)
			&& (*envp)[i][j] == '=' && key[j] == '\0')
		{
			free((*envp)[i]);
			k = i;
			while ((*envp)[k])
			{
				(*envp)[k] = (*envp)[k + 1];
				k++;
			}
			break ;
		}
		i++;
	}
}

int	append_env(char *key_value, char ***envp)
{
	int		envp_count;
	int		i;
	char	**new_envp;

	envp_count = 0;
	while ((*envp)[envp_count])
		envp_count++;
	new_envp = (char **)malloc(sizeof(char *) * (envp_count + 2));
	if (!new_envp)
		return (0);
	i = 0;
	while (i < envp_count)
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (new_envp[i] == NULL)
			return (free_and_error(&new_envp, "Error strdup()\n"));
		i++;
	}
	new_envp[i] = ft_strdup(key_value);
	if (!new_envp[i])
		return (free_and_error(&new_envp, "Error strdup()\n"));
	new_envp[i + 1] = NULL;
	free_mat(*envp);
	*envp = new_envp;
	return (1);
}

int	export(char *key_value, char ***envp)
{
	char	**temp;
	char	*token;
	int		cheker;

	cheker = is_valid_key_value(key_value, &token);
	if (cheker == 0)
	{
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	if (cheker == 1)
		return (0);
	temp = ft_split(key_value, '=');
	if (!temp)
		return (1);
	if (is_in_env(temp[0], *envp))
		unset_env(temp[0], envp);
	if (!append_env(key_value, envp))
	{
		free_mat(temp);
		return (1);
	}
	free_mat(temp);
	return (0);
}

int	exports_loop(char	**mat, t_lexer *lexer)
{
	int	i;
	int	failed;

	i = 1;
	failed = 0;
	while (mat[i])
	{
		if (export(mat[i], &lexer->env))
			failed = 1;
		i++;
	}
	if (i == 1)
		print_export(lexer->env);
	if (failed)
	{
		s_sts(1);
		return (1);
	}
	return (0);
}
