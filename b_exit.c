/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:46:13 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/06 15:28:22 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_number(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			return (2);
		}
		str++;
	}
	return (1);
}

int	is_valid_exit(char **mat)
{
	int		i;
	int		not_valid_num;

	i = 0;
	not_valid_num = 0;
	while (mat[i])
		i++;
	if (mat[1])
		not_valid_num = is_valid_number(mat[1]);
	if (i > 2)
	{
		if (not_valid_num != 0 && not_valid_num != 2)
		{
			if (s_sts(-1) == 0)
				s_sts(1);
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (0);
		}
	}
	if (not_valid_num == 2)
		s_sts(2);
	return (not_valid_num);
}

void	b_exit(char **mat, t_lexer *lexer, t_tree *reset)
{
	int	valid;
	int	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	valid = is_valid_exit(mat);
	if (valid == 1)
	{
		status = ft_atoi(mat[1]);
		if (status < 0 || status > 255)
			status = status % 256;
		free_mat(lexer->env);
		free_mat(mat);
		tree_free(reset);
		exit(status);
	}
	if (valid == 2)
	{
		free_mat(lexer->env);
		free_mat(mat);
		tree_free(reset);
		exit(2);
	}
}
