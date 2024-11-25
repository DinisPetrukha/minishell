/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_nodes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:10:41 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 12:03:52 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	skip_lnudsqi(char *str, int i)
{
	while (str[i] && ft_islnudsqi(str[i]))
		i++;
	return (i);
}

char	*hereexpander(char *new, t_lexer *lexer, int dolexpand, int i)
{
	char	*str;
	char	*dollar;

	str = "";
	while (new[i])
	{
		if (new[i] == '$' && dolexpand)
		{
			dollar = dollar_sign(&new[i++], lexer);
			if (!dollar)
				i = skip_lnudsqi(new, i);
			else
			{
				str = ft_neostrjoin(str, dollar, 3);
				skip_question(&i, new);
			}
		}
		else
		{
			str = ft_realloc(str, ft_strlen(str), ft_strlen(str) + 1);
			str[ft_strlen(str)] = new[i++];
		}
	}
	return (free(new), str);
}

char	*expanddollar(char *new, t_lexer *lexer, int i, int inquote)
{
	char	*str;
	char	*ret;

	ret = "";
	while (new[i])
	{
		inquote = quotealternate(inquote, new[i]);
		if (new[i] == '$' && (!inquote && (pre_heredoc(new, i) == 0)))
		{
			str = dollar_sign(&new[i], lexer);
			ret = ft_neostrjoin(ret, str, 3);
			i++;
			if (new[i] && new[i] == '?')
				i++;
			else
				i = skip_lnu(new, i);
		}
		else
		{
			ret = ft_realloc(ret, ft_strlen(ret), ft_strlen(ret) + 1);
			ret[ft_strlen(ret)] = new[i++];
		}
	}
	return (free(new), ret);
}

char	*emptyclean(char *new, t_lexer *lexer, int i)
{
	char	*dollar;

	if (!new)
		return (NULL);
	while (new[i])
	{
		if (new[i] == 34 || new[i] == 39)
			i = find_samequote(new, i);
		if (new[i] == '$' && (pre_heredoc(new, i) == 0))
		{
			dollar = dollar_sign(&new[i], lexer);
			if (dollar && (*dollar))
				free(dollar);
			else
			{
				if (dollar)
					free(dollar);
				new[i++] = ' ';
				if (!cleandollar(new, &i))
					break ;
			}
		}
		i += ifexist(new, i);
	}
	return (expanddollar(new, lexer, 0, 0));
}

t_tree	*renode(t_tree *node, t_lexer *lexer)
{
	char	*new;

	new = remain(node->content, lexer);
	if (node->content)
		free(node->content);
	if (!new)
		return (NULL);
	node->content = new;
	return (node);
}
