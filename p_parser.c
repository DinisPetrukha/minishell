/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:34:28 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:05:06 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_left(t_tree *tree, t_lexer *lexer, char *str, int id)
{
	t_tree	*new;

	if (str == NULL)
		return (1);
	new = (malloc(sizeof(t_tree)));
	if (new == NULL)
	{
		lexer->report = 4;
		return (4);
	}
	if (lexer->in_redir)
		new->redir_type = lexer->in_redir;
	else
		new->redir_type = 0;
	new->pipe_flag = 0;
	new->pipefd[0] = 1;
	new->pipefd[1] = 0;
	new->fid = 0;
	new->id = id;
	new->content = str;
	new->right = NULL;
	new->left = NULL;
	tree->left = new;
	return (0);
}

void	add_right(t_tree *tree, t_lexer *lexer, char *str, int id)
{
	t_tree	*new;

	lexer->start = 0;
	lexer->end = 0;
	if (str == NULL)
		return ;
	new = (malloc(sizeof(t_tree)));
	if (new == NULL)
	{
		lexer->report = 4;
		return ;
	}
	new->pipe_flag = 0;
	new->pipefd[0] = 1;
	new->pipefd[1] = 0;
	new->fid = 0;
	if (lexer->pipe_flag == 1)
		new->pipe_flag = 1;
	new->redir_type = 0;
	new->id = id;
	new->content = str;
	new->left = NULL;
	new->right = NULL;
	tree->right = new;
	return ;
}

//RETURN VALUE IS NOT USED YET
void	parser(t_tree *node, t_lexer *lexer, int cmd_found)
{
	if (lexer->report)
		return ;
	if (node->id == JOB && !(isjob(node->content)))
		node->id = CMD;
	if (add_left(node, lexer, iscmd(node->content, lexer), CMD) == 0)
		add_right(node, lexer, remain(node->content, lexer), JOB);
	else if (add_left(node, lexer,
			isredir(node->content, lexer, 0), REDIR) == 0)
		add_right(node, lexer, remain(node->content, lexer), CMD);
	else if (cmd_found == 0
		&& add_left(node, lexer, isname(node->content, lexer), NAME) == 0)
	{
		add_right(node, lexer, remain(node->content, lexer), CMD);
		cmd_found = 1;
	}
	else if (add_left(node, lexer,
			str_untier(node->content, lexer, 0, 0), TOKEN) == 0)
		add_right(node, lexer, remain(node->content, lexer), CMD);
	else
		return ;
	if (node->left && (node->left->id == CMD))
		parser(node->left, lexer, cmd_found);
	if (node->right && (node->right->id == CMD || node->right->id == JOB))
		parser(node->right, lexer, cmd_found);
	return ;
}
