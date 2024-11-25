/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_reforked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:10:19 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 12:08:56 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_nid(t_tree *tree, int id)
{
	int		i;

	i = 0;
	if (tree->left)
		i += find_nid(tree->left, id);
	if (tree->right)
		i += find_nid(tree->right, id);
	if (tree->id == id)
		i++;
	return (i);
}

int	ischildneeded(t_tree *cmd, t_tree *reset, t_lexer *lexer, char **full)
{
	if (!pipecount(reset))
	{
		if (!ft_strncmp(cmd->content, "export", 6)
			|| !ft_strncmp(cmd->content, "cd", 3)
			|| !ft_strncmp(cmd->content, "unset", 5)
			|| !ft_strncmp(cmd->content, "exit", 4))
		{
			lexer->child = 0;
			builtins(reset, full, lexer, 0);
			free_mat(full);
			return (0);
		}
	}
	lexer->child = 1;
	return (1);
}

int	defaultbehavior(t_tree *cmd, t_tree *tree, t_lexer *lexer, int	*retpipe)
{
	if (!cmd)
	{
		onlyredir(left_cmd(tree), lexer);
		closeclean(*retpipe, 0);
	}
	else if ((cmd->pipefd[1] == -1 || cmd->pipefd[0] == -1))
	{
		lexer->child = 1;
		cmd->fid = fork();
		if (cmd->fid <= 0)
		{
			closeall_fd(lexer->tree);
			free_mat(lexer->env);
			tree_free(lexer->tree);
			closeclean(*retpipe, 0);
			free_nodes(&(lexer->herelist));
			exit(1);
		}
		if (cmd->pipefd[1] > 2)
			close(cmd->pipefd[1]);
		if (cmd->pipefd[0] > 2)
			close(cmd->pipefd[0]);
		return (0);
	}
	return (1);
}

int	forkindustry(t_tree *tree, t_lexer *lexer, char **full, int retpipe)
{
	t_tree	*cmd;

	cmd = find_cmd(left_cmd(tree));
	setup_signal_handlers(IGNORE);
	cmd->fid = fork();
	if (cmd->fid < 0)
		exit(free_return(lexer->tree, lexer, full, 1));
	if (cmd->fid == 0)
	{
		setup_signal_handlers(CHILD);
		dup2(cmd->pipefd[1], STDIN_FILENO);
		dup2(cmd->pipefd[0], STDOUT_FILENO);
		closeall_fd(lexer->tree);
		builtins(lexer->tree, full, lexer, retpipe);
		if (execve(cmd->content, full, lexer->env) == -1)
			exit_exec(lexer->tree, tree, lexer, full);
	}
	if (cmd->pipefd[1] > 2)
		close(cmd->pipefd[1]);
	if (cmd->pipefd[0] > 2)
		close(cmd->pipefd[0]);
	free_mat(full);
	return (0);
}

int	executive(t_tree *tree, t_tree *reset, t_lexer *lexer, int retpipe)
{
	t_tree	*cmd;
	char	**full;

	while (tree)
	{
		cmd = find_cmd(left_cmd(tree));
		retpipe = setfds(tree, cmd, retpipe, lexer);
		if (retpipe == -1)
			return (-1);
		if (defaultbehavior(cmd, tree, lexer, &retpipe))
		{
			full = join_tokens(left_cmd(tree), 1);
			if (full && !ischildneeded(cmd, reset, lexer, full))
				break ;
			if (full && forkindustry(tree, lexer, full, retpipe) == -1)
				return (-1);
		}
		if (tree->pipe_flag == 1)
			tree = tree->right;
		else
			break ;
	}
	waiter(reset, lexer);
	return (0);
}
