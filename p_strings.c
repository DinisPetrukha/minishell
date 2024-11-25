/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_strings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:36:18 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:01:41 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	charnstr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	onlyspacestr(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	quotealternate(int nbr, int compare)
{
	if (compare != 34 && compare != 39)
		return (nbr);
	if (nbr == compare)
		return (0);
	else if ((nbr != compare) && (nbr != 0) && (compare != 0))
		return (nbr);
	else
		return (compare);
}

void	dolquotehandle(char *str)
{
	int		i;
	int		inquote;

	i = 0;
	inquote = 0;
	if (!str)
		return ;
	while (str[i])
	{
		inquote = quotealternate(inquote, str[i]);
		if (str[i] == '$' && !inquote)
		{
			if (str[i + 1] && (str[i + 1] == 34 || str[i + 1] == 39))
				str[i] = ' ';
			i++;
		}
		if (str[i])
			i++;
	}
	return ;
}

int	str_skipper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i == 34])
			i += quote_skipper(&str[i]);
		if (str[i] && !ft_isspace(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}
