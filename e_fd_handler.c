/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_fd_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:41 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:34:07 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_inout(t_tree *cmd, int infile, int outfile, int fdstatus)
{
	if (infile != cmd->pipefd[1])
	{
		closeclean(infile, -1);
		return (-1);
	}
	if (outfile != cmd->pipefd[0])
	{
		closeclean(outfile, -1);
		return (-1);
	}
	if (fdstatus == -1)
	{
		closeclean(cmd->pipefd[1], -1);
		closeclean(cmd->pipefd[0], -1);
		return (-1);
	}
	return (0);
}

//in case of problem we cannot exit, just hold the value.
int	setfds(t_tree *tree, t_tree *cmd, int prevpipe, t_lexer *lexer)
{
	int	piper[2];

	if (!cmd)
		return (0);
	openfiles(left_cmd(tree), cmd, lexer);
	if (cmd->pipefd[1] == 0 && prevpipe)
		cmd->pipefd[1] = prevpipe;
	else if (cmd->pipefd[1] != 0 && prevpipe)
		close(prevpipe);
	if (!(pipecount(tree)))
		return (0);
	if (pipe(piper) == -1)
		return (error_return("PIPE ERROR\n", -1));
	if (cmd->pipefd[0] == 1)
		cmd->pipefd[0] = piper[1];
	else if (cmd->pipefd[0] != 1)
		close(piper[1]);
	return (piper[0]);
}

int	closeclean(int fd, int force)
{
	if (fd > 2)
		close(fd);
	return (force);
}

void	closeall_fd(t_tree *tree)
{
	if (tree->id)
	{
		if (tree->pipefd[0] > 2)
			close(tree->pipefd[0]);
		if (tree->pipefd[1] > 2)
			close(tree->pipefd[1]);
	}
	if (tree->left)
		closeall_fd(tree->left);
	if (tree->right)
		closeall_fd(tree->right);
}

void	closenodefds(t_tree *tree)
{
	if (tree->pipefd[1] > 2)
		close(tree->pipefd[1]);
	if (tree->pipefd[0] > 2)
		close(tree->pipefd[0]);
}
