/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_waiter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:12:22 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 12:45:19 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_status(int sts)
{
	int	sig;

	if (WIFSIGNALED(sts))
	{
		sig = WTERMSIG(sts);
		if (sig == SIGINT)
			s_sts(130);
		else if (sig == SIGQUIT)
		{
			s_sts(131);
		}
	}
	else if (WIFEXITED(sts))
		s_sts(WEXITSTATUS(sts));
	else
		s_sts(sts);
}

void	waiter(t_tree *tree, t_lexer *lexer)
{
	t_tree	*cmd;
	int		status;

	status = 0;
	while (tree && lexer->child)
	{
		cmd = find_cmd(left_cmd(tree));
		if (cmd != NULL)
		{
			waitpid(cmd->fid, &status, 0);
			s_sts(status);
			get_status(s_sts(-1));
		}
		if (tree->pipe_flag == 1)
			tree = tree->right;
		else
			break ;
	}
}
