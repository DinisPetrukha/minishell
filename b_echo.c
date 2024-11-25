/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 09:49:59 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 09:51:30 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	valid_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	b_echo(char **mat)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (mat[i])
	{
		if (valid_n(mat[i]))
			i++;
		else
			break ;
	}
	if (i > 1)
		nl = !nl;
	while (mat[i])
	{
		ft_putstr_fd(mat[i], STDOUT_FILENO);
		i++;
		if (mat[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (nl)
		ft_putchar_fd(10, STDOUT_FILENO);
	return (0);
}
