/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:50:38 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:51:24 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_skipper(char *str)
{
	int	i;
	int	topquote;

	i = 0;
	while (str[i])
	{
		topquote = str[i];
		i++;
		while (str[i] && (str[i] != topquote))
			i++;
		if (!str[i])
			return (i);
		if (!str[i + 1] || (str[i + 1] != 39 && str[i + 1] != 34))
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	find_samequote(char *str, int i)
{
	int	quote;

	quote = str[i];
	while (str[++i] && str[i] != quote)
		;
	if (str[i])
		i++;
	return (i);
}

void	some_skipper(char *str, int *i)
{
	while (str[*i] && str[*i + 1] && (str[*i + 1] == str[*i]))
		*i += 2;
}

char	*quote_untier(char *str, t_lexer *lexer, int i)
{
	char	*untied;

	untied = "";
	while (str[i] && (str[i] == 34 || str[i] == 39))
	{
		some_skipper(str, &i);
		if (str[i] && str[i] == 34)
		{
			if (*untied)
				untied = ft_neostrjoin(untied, weak_quote(&str[i], lexer, 1),
						3);
			else
				untied = weak_quote(&str[i], lexer, 1);
			i = find_samequote(str, i);
		}
		else if (str[i] && str[i] == 39)
		{
			if (*untied)
				untied = ft_neostrjoin(untied, stro_quote(&str[i]), 3);
			else
				untied = stro_quote(&str[i]);
			i = find_samequote(str, i);
		}
	}
	return (untied);
}
