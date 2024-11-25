/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_free_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:17:40 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 12:49:01 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nodes(t_herelist **head)
{
	t_herelist	*tmp;

	if (!head)
		return ;
	if (!(*head))
		return ;
	while (head && (*head))
	{
		tmp = (*head);
		(*head) = (*head)->next;
		if (tmp->content)
			free(tmp->content);
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	return ;
}

void	totalfree(t_tree *reset, t_lexer *lexer, char **full)
{
	free_mat(lexer->env);
	free_mat(full);
	tree_free(reset);
	free_nodes(&(lexer->herelist));
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
	{
		free(mat[i]);
		i++;
	}
	if (mat)
		free(mat);
}

void	tree_free(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left)
		tree_free(tree->left);
	if (tree->right)
		tree_free(tree->right);
	if (tree->content && *tree->content)
		free(tree->content);
	if (tree)
		free(tree);
}

int	free_and_error(char ***envp, char *error)
{
	free_mat(*envp);
	perror(error);
	return (0);
}
