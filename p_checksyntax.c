/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_checksyntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:14:10 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/06 15:36:41 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*symbols_ret(char *str)
{
	char	*ret_str;
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return ("newline");
	ret_str = str;
	if (str[i] && str[i + 1] && str[i + 1] == str[i])
		i++;
	if (str[++i])
		str[i] = '\0';
	return (ret_str);
}

int	print_syntaxerror(char *str_error, char *token, int dir)
{
	if (str_error)
		ft_putstr_fd(str_error, STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	if (token && !dir)
		ft_putchar_fd('\'', STDERR_FILENO);
	if (dir)
		ft_putstr_fd(": Is a directory", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (2);
}

int	checksyntax(char *str, int i, int nb)
{
	int		bfpipe;
	char	*token;

	bfpipe = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]) && !ft_strchr("|./", str[i]) && !nb)
			bfpipe = 1;
		if (ft_strchr("\"\'", str[i]) && syntaxquotes(str, str[i], &i) && !nb)
			nb = print_syntaxerror(SYN_ERROR1, NULL, 0);
		else if ((str[i] == '|') && syntaxpipe(&str[i], bfpipe, &token) && !nb)
			nb = print_syntaxerror(SYN_ERROR2, token, 0);
		else if (ft_strchr("><", str[i]) && sr(&str[i], str[i], &token) && !nb)
			nb = print_syntaxerror(SYN_ERROR3, token, 0);
		else if (str[i] && ft_strchr("&;", str[i]) && !nb)
			nb = print_syntaxerror(SYN_ERROR3, symbols_ret(&str[i]), 0);
		if (str[i])
			i++;
	}
	if (nb)
	{
		s_sts(nb);
		return (1);
	}
	return (0);
}
