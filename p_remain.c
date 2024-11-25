/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_remain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:26:57 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:29:37 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strnotstr(char *dst, char *src, int start, int end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (i >= start && i <= end)
			i++;
		else
		{
			dst[j] = src[i];
			i++;
			j++;
		}
	}
}

int	emptystring(char *str)
{
	int	i;
	int	isempty;

	isempty = 1;
	i = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			isempty = 0;
		i++;
	}
	return (isempty);
}

char	*remain(char *str, t_lexer *lexer)
{
	char	*ret;

	ret = remain_calc(str, lexer, 0);
	if (ret == NULL)
	{
		lexer->in_redir = 0;
		return (NULL);
	}
	return (ret);
}

char	*remain_calc(char *str, t_lexer *lexer, int j)
{
	char	*ret;

	ret = NULL;
	if ((lexer->start >= lexer->end) || !str)
		return (NULL);
	if (lexer->in_redir == 0)
	{
		ret = ft_calloc(ft_strlen(str) - lexer->start + 2, sizeof(char));
		if (ret == NULL)
			return (NULL);
		ft_strlcpy(ret, &str[lexer->start], lexer->end);
	}
	else
	{
		ret = ft_calloc(ft_strlen(str) - (lexer->end - lexer->start + 1) + 1,
				sizeof(char));
		if (ret == NULL)
			return (NULL);
		strnotstr(ret, str, lexer->start, lexer->end);
	}
	if (emptystring(ret))
		return (ret_free(&ret, NULL));
	lexer->pipe_flag = pipe_in_str(&ret[j], &j);
	lexer->in_redir = 0;
	return (ret);
}
