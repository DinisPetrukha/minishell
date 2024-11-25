/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bigis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:53:32 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:48:42 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// IS_JOB VERSÃO DINIS
int	isjob(char *str)
{
	int	jobbable;
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	jobbable = 0;
	while (str[i])
	{
		inquote = quotealternate(inquote, str[i]);
		if (str[i] == '|' && !inquote)
		{
			i++;
			while (str[i])
			{
				if (!ft_isspace(str[i]))
					jobbable = 1;
				i++;
			}
			break ;
		}
		i++;
	}
	return (jobbable);
}

//VESAO ANTIGAAA
char	*iscmd(char *str, t_lexer *lexer)
{
	int		i;
	char	*ret;

	i = 0;
	lexer->pipe_flag = pipe_in_str(str, &i);
	lexer->start = i + 1;
	lexer->end = ft_strlen(str);
	if (ft_strlen(str) == (size_t)i)
		return (NULL);
	while (--i >= 0 && ft_isspace(str[i]))
		;
	if (i == -1)
		return (NULL);
	ret = ft_calloc(i + 2, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i >= 0)
	{
		ret[i] = str[i];
		i--;
	}
	return (ret);
}

int	dollar_join(char *str, char **ret, t_lexer *lexer, int i)
{
	char	*dollar;

	dollar = dollar_sign(&str[i], lexer);
	if (addtostr(ret, &dollar) == 1)
		return (-1);
	while (str[++i] && (ft_islnu(str[i])))
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
			break ;
		}
	}
	if (lexer->sflag)
	{
		i++;
		lexer->sflag = 0;
	}
	if ((!str[i]) && !dollar)
		return (-1);
	return (i);
}

int	str_extracall(char *str, char **unt, t_lexer *lexer, int i)
{
	char	*dollar;

	if (str[i] == 34 || str[i] == 39)
	{
		if (**unt)
			*unt = ft_neostrjoin(*unt, quote_untier(&str[i], lexer, 0), 3);
		else
			*unt = quote_untier(&str[i], lexer, 0);
		i += quote_skipper(&str[i]);
	}
	else if (str[i] == '$' && lexer->in_redir != 3)
	{
		dollar = dollar_sign(&str[i], lexer);
		if (addtostr(unt, &dollar) == 1)
			return (-1);
		while (str[++i] && (ft_islnu(str[i])))
			;
		if (lexer->sflag)
			i += anulsflag(lexer);
		if (!str[i] && dollar == NULL)
			return (-1);
	}
	return (i);
}

//I and J start in 0
char	*str_untier(char *str, t_lexer *lexer, int i, int j)
{
	char	*untied;

	untied = "";
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '<' && str[i] != '>')
	{
		if ((str[i] == 34 || str[i] == 39)
			|| (str[i] == '$' && lexer->in_redir != 3))
		{
			j = str_extracall(str, &untied, lexer, i);
			if (j == -1)
				return (NULL);
			i = j;
		}
		else
		{
			untied = ft_realloc(untied, ft_strlen(untied),
					ft_strlen(untied) + 1);
			untied[ft_strlen(untied)] = str[i++];
		}
	}
	lexer->start = i;
	lexer->end = ft_strlen(str);
	return (untied);
}
