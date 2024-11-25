/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_checksyntax_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:36:27 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:20:48 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntaxquotes(char *str, char quote, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
			return (0);
		(*i)++;
	}
	return (1);
}

//SYNTAX_REDIR
int	sr(char *str, char symbol, char **token)
{
	int		i;

	i = 1;
	if (!ft_strchr("><", str[0]) || !str[0])
		return (0);
	if (str[i] == symbol)
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && !ft_strchr("|<>", str[i]))
		return (0);
	*token = symbols_ret(&str[i]);
	return (1);
}

int	syntaxpipe(char *str, int before_pipe, char **syntax)
{
	int	i;

	i = 1;
	if (before_pipe == 0)
	{
		*syntax = &str[0];
		if (str[1] == '|')
			str[2] = '\0';
		else
			str[1] = '\0';
		return (1);
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && !ft_strchr("|\n", str[i]))
		return (0);
	*syntax = &str[i - 1];
	if (str[i] == '|')
		str[i + 1] = '\0';
	else
		str[i] = '\0';
	return (1);
}
