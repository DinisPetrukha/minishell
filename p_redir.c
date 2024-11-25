/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:22:08 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:23:49 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	redir_type_34(char *str, int *i, t_lexer *lexer)
{
	if (str[*i] == '<' && lexer->in_redir == 1)
		lexer->in_redir = 3;
	else if (str[*i] == '>' && lexer->in_redir == 2)
		lexer->in_redir = 4;
	else if (str[*i] == '>' || str[*i] == '<')
		lexer->in_redir = 0;
}

int	set_redir(char *str, t_lexer *lexer, int i, int inquote)
{
	lexer->in_redir = 0;
	while (str[i])
	{
		inquote = quotealternate(inquote, str[i]);
		if ((str[i] == '<' || str[i] == '>') && !inquote)
		{
			lexer->start = i;
			if (str[i] == '<')
				lexer->in_redir = 1;
			else if (str[i] == '>')
				lexer->in_redir = 2;
			if ((str[++i] == '<' || str[i] == '>') && !inquote)
			{
				redir_type_34(str, &i, lexer);
				i++;
			}
			break ;
		}
		i++;
	}
	i += space_skipper(&str[i]);
	return (i);
}

int	findheredir(char *str)
{
	int		i;
	int		inquote;

	i = 0;
	inquote = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		inquote = quotealternate(inquote, str[i]);
		if ((str[i] == '<') && !inquote)
		{
			if (str[i + 1] && str[i + 1] == '<')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	if_expand(t_lexer *lexer, char *str, int *i)
{
	while (str[*i] && ft_islnudsq(str[*i]))
	{
		if (str[*i] == 34 || str[*i] == 39)
		{
			lexer->willexpand = 0;
			*i += quote_skipper(&str[*i]);
		}
		else
		{
			lexer->willexpand = 1;
			(*i)++;
		}
	}
}

char	*isredir(char *str, t_lexer *lexer, int hereactive)
{
	int		i;
	int		tmp_start;
	char	*file;

	i = set_redir(str, lexer, 0, 0);
	tmp_start = lexer->start;
	if (lexer->in_redir == 0 || (!str[i]) || ft_islnudsq(str[i]) == 0)
		return (NULL);
	file = str_untier(&str[i], lexer, 0, 0);
	if_expand(lexer, str, &i);
	lexer->end = i - 1;
	lexer->start = tmp_start;
	if (hereactive && lexer->in_redir != 3)
	{
		if (file)
			free (file);
		return (NULL);
	}
	return (file);
}
