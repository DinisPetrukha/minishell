/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:08:46 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:22:51 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	addtostr(char **ret, char **from)
{
	if (*from == NULL)
		return (0);
	*ret = ft_realloc(*ret, ft_strlen(*ret),
			ft_strlen(*from) + ft_strlen(*ret));
	if (*ret == NULL)
	{
		if (ft_strlen(*from) == 1 && **from == '$')
			free(*from);
		return (1);
	}
	ft_strlcat(*ret, *from, ft_strlen(*from) + ft_strlen(*ret) + 1);
	free(*from);
	return (0);
}

char	**matcpy(char **mat)
{
	char	**full;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!mat)
		return (NULL);
	while (mat[i])
		i++;
	full = ft_calloc((i + 1), sizeof(char *));
	if (!full)
		directexit("Cannot allocate memory\n", 4);
	while (j < i)
	{
		full[j] = ft_substr(mat[j], 0, ft_strlen(mat[j]));
		if (!full[j])
		{
			free_mat(full);
			directexit("Cannot allocate memory\n", 4);
		}
		j++;
	}
	full[j] = 0;
	return (full);
}

char	*weak_quote(char *str, t_lexer *lexer, int i)
{
	int		j;
	char	*ret;

	ret = "";
	if (str[i] && str[i] == 34)
		return (NULL);
	while (str[i] && str[i] != 34)
	{
		if (str[i] == '$' && lexer->in_redir != 3)
		{
			j = dollar_join(str, &ret, lexer, i);
			if (j == -1)
				return (NULL);
			i = j;
		}
		else
		{
			ret = ft_realloc(ret, ft_strlen(ret),
					ft_strlen(ret) + 1);
			ret[ft_strlen(ret)] = str[i++];
		}
	}
	return (ret);
}

char	*stro_quote(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 1;
	j = 0;
	if (str[i] && str[i] == 39)
		return (NULL);
	while (str[i] && str[i] != 39)
		i++;
	ret = (char *)ft_calloc(i, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (j < i - 1)
	{
		ret[j] = str[j + 1];
		j++;
	}
	return (ret);
}
