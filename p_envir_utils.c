/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_envir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:56:59 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:34:31 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_free(char **str, char **mat)
{
	free(*str);
	if (mat)
		free_mat(mat);
	return (NULL);
}

void	increment_shlvl(char **envp)
{
	char	**key_value;
	char	*str_sh;
	int		sh_value;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
		{
			key_value = ft_split(envp[i], '=');
			free(envp[i]);
			sh_value = ft_atoi(key_value[1]) + 1;
			if (key_value)
				free_mat(key_value);
			str_sh = ft_itoa(sh_value);
			envp[i] = ft_strjoin("SHLVL=", str_sh);
			free(str_sh);
		}
		i++;
	}
}

char	**ft_enviroment(char **envp)
{
	char	**artificial_envp;

	if (envp[0])
		return (matcpy(envp));
	artificial_envp = (char **) malloc(sizeof(char *) * 3);
	if (!artificial_envp)
		error_return("env: error malloc allocation", 1);
	artificial_envp[0] = ft_strjoin("PATH=", get_cur_directory(NULL, 0));
	artificial_envp[1] = ft_strdup("SHLVL=1");
	artificial_envp[2] = 0;
	return (artificial_envp);
}

char	*ft_getenv(char **envir, char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	if (!str)
		return (NULL);
	while (envir[i])
	{
		j = 0;
		while (envir[i][j] && str[j] && envir[i][j] != '=' &&
			envir[i][j] == str[j])
			j++;
		if (!str[j] && envir[i][j] == '=')
		{
			ret = ft_substr(envir[i], j + 1, ft_strlen(envir[i]) - j - 1);
			return (ret);
		}
		i++;
	}
	return (NULL);
}
