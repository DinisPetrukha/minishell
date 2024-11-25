/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_built_ins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:35:08 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:32:01 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	print_env(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (-1);
	while (env[i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	built_comparison(char **mat, t_lexer *lexer, t_tree *reset)
{
	if (!ft_strncmp(*mat, "exit", 4))
		b_exit(mat, lexer, reset);
	if (!ft_strncmp(*mat, "cd", 3))
		return (b_cd(mat, 0, lexer));
	else if (!ft_strncmp(*mat, "pwd", 4))
		return (b_pwd());
	else if (!ft_strncmp(*mat, "env", 4))
		return (print_env(lexer->env));
	else if (!ft_strncmp(*mat, "echo", 5))
		return (b_echo(mat));
	else if (!ft_strncmp(*mat, "export", 7))
		return (exports_loop(mat, lexer));
	else if (!ft_strncmp(*mat, "unset", 6))
		return (unset_loop(mat, lexer));
	return (2);
}

void	builtins(t_tree *reset, char **mat, t_lexer *lexer, int pipenbr)
{
	int	value;

	if (!mat)
		return ;
	value = built_comparison(mat, lexer, reset);
	if (value != 2)
	{
		if (lexer->child)
		{
			free_mat(lexer->env);
			free_mat(mat);
			tree_free(reset);
			lexer->tree = NULL;
			if (pipenbr > 2)
				close(pipenbr);
			free_nodes(&(lexer->herelist));
			exit(value);
		}
	}
	return ;
}
