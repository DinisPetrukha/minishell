/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_error_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:14:16 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:00:30 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_exec(t_tree *reset, t_tree *tree, t_lexer *lexer, char **full)
{
	t_tree	*cmd;
	int		value;

	value = 1;
	cmd = find_cmd(left_cmd(tree));
	if (cmd->id == TOKEN)
	{
		ft_putstr_fd(cmd->content, 2);
		if ((tree->left->content[0] != '/')
			&& (tree->left->content[ft_strlen(tree->left->content) - 1] != '/')
			&& (ft_strncmp(tree->left->content, "./", 2)))
			value = error_return(": command not found\n", 127);
		else if (access(tree->left->content, F_OK) != -1)
		{
			if (access(tree->left->content, R_OK | X_OK) != -1)
				value = error_return(": Is a directory\n", 126);
			else
				value = error_return(": Permission denied\n", 126);
		}
		else
			value = error_return(": No such file or directory\n", 127);
	}
	totalfree(reset, lexer, full);
	exit(value);
}

int	error_return(char *str, int exit_status)
{
	if (!str)
		return (exit_status);
	ft_putstr_fd(str, 2);
	return (exit_status);
}

int	free_return(t_tree *reset, t_lexer *lexer, char **full, int value)
{
	totalfree(reset, lexer, full);
	return (value);
}

void	directexit(char *str, int status)
{
	if (*str)
		ft_putstr_fd(str, 2);
	exit(status);
}

void	checkreport(t_tree *tree, t_lexer *lexer, char *line, int force)
{
	if (force == -1 && lexer->report == 0)
		return ;
	tree_free(tree);
	free_mat(lexer->env);
	free(line);
	if (force == 0)
		directexit("", 0);
	if (force == 4 || lexer->report == 4)
		directexit("Cannot allocate memory\n", 4);
}
