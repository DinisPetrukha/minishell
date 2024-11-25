/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:03:35 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/06 15:36:03 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	onlyredir(t_tree *tree, t_lexer *lexer)
{
	int		outfile;
	int		infile;

	outfile = 1;
	infile = 0;
	if (!tree)
		return ;
	while (tree)
	{
		if (tree->left->id == REDIR)
		{
			if (tree->left->redir_type == 2 || tree->left->redir_type == 4)
				outfile = openoutfile(tree);
			if (tree->left->redir_type == 1 || tree->left->redir_type == 3)
				infile = openinfile(tree, lexer, lexer->herelist);
			if (outfile > 2)
				close (outfile);
			if (infile > 2)
				close (infile);
		}
		tree = tree->right;
	}
}

//fd = 1 by default. If no redir found it will write in the stdout
int	openoutfile(t_tree *tree)
{
	int	fd;

	fd = 1;
	if (tree->left->redir_type == 2)
		fd = open(tree->left->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tree->left->redir_type == 4)
		fd = open(tree->left->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(tree->left->content);
		s_sts(1);
		return (-1);
	}
	return (fd);
}

// -1 error
//fd = 0 by default. If no redir found it will read from stdin
int	openinfile(t_tree *tree, t_lexer *lexer, t_herelist *herelist)
{
	int	fd;

	fd = 0;
	if (tree->left->redir_type == 1)
		fd = open(tree->left->content, O_RDONLY);
	if (tree->left->redir_type == 3)
	{
		fd = herelist->fd;
		popfirst(&herelist, lexer);
	}
	if (fd == -1)
	{
		perror(tree->left->content);
		return (-1);
	}
	return (fd);
}

//we rewrite cmd->pipe but infile and outfile stay for close
int	openfiles(t_tree *tree, t_tree *cmd, t_lexer *lexer)
{
	int	infile;
	int	outfile;
	int	fdstatus;

	infile = 0;
	outfile = 1;
	if (tree->left->redir_type == 2 || tree->left->redir_type == 4)
	{
		outfile = openoutfile(tree);
		cmd->pipefd[0] = outfile;
	}
	if (tree->left->redir_type == 1 || tree->left->redir_type == 3)
	{
		infile = openinfile(tree, lexer, lexer->herelist);
		cmd->pipefd[1] = infile;
	}
	if (infile == -1 || outfile == -1)
		return (-1);
	if (tree->right && tree->right->left->id == REDIR)
	{
		fdstatus = openfiles(left_cmd(tree->right), cmd, lexer);
		if (verify_inout(cmd, infile, outfile, fdstatus) == -1)
			return (-1);
	}
	return (0);
}
