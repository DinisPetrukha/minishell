/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_nodes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:39:41 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/06 15:37:16 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*isname(char *str, t_lexer *lexer)
{
	char	*name;
	char	*return_state;

	name = str_untier(str, lexer, 0, 0);
	lexer->pipe_flag = 0;
	return_state = cmd_path(name, set_pather(lexer->env), 0);
	return (return_state);
}

char	*dollar_sign(char *str, t_lexer *lexer)
{
	int		i;
	char	*ret;
	char	*path;

	i = 1;
	path = NULL;
	ret = NULL;
	if (str[i] && str[i] == '?')
	{
		lexer->sflag = 1;
		return (ft_itoa(s_sts(-1)));
	}
	while (str[i] && (ft_islnu(str[i])))
		i++;
	ret = (char *)ft_calloc(i + 1, sizeof(char));
	if (i == 1)
	{
		ft_strlcpy(ret, &str[0], 2);
		return (ret);
	}
	ft_strlcpy(ret, &str[1], i);
	path = ft_getenv(lexer->env, ret);
	free(ret);
	return (path);
}

int	cleandollar(char *new, int *i)
{
	while (new[*i] && ft_islnu(new[*i]))
	{
		if (new[*i] >= '0' && new[*i] <= '9')
		{
			new[*i] = ' ';
			return (0);
		}
		new[*i] = ' ';
		(*i)++;
	}
	return (1);
}

void	skip_question(int *i, char *new)
{
	if (new[*i] && new[*i] == '?')
		(*i)++;
	else
		*i = skip_lnu(new, *i);
}

int	skip_lnu(char *str, int i)
{
	while (str[i] && ft_islnu(str[i]))
		i++;
	return (i);
}
