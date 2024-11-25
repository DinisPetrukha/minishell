/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:37:57 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 12:04:52 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return one for incrementation
int	anulsflag(t_lexer *lexer)
{
	lexer->sflag = 0;
	return (1);
}

int	ifexist(char *str, int i)
{
	if (str[i])
		return (1);
	return (0);
}

void	root_tree_init(t_tree **tree, t_lexer *lexer, char *str)
{
	int	i;

	i = 0;
	(*tree)->id = JOB;
	(*tree)->redir_type = 0;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	(*tree)->pipe_flag = 0;
	(*tree)->pipefd[0] = 1;
	(*tree)->pipefd[1] = 0;
	(*tree)->fid = 0;
	lexer->tree = *tree;
	lexer->sflag = 0;
	(*tree)->pipe_flag = pipe_in_str(str, &i);
}

//STARTING POINT OF THE TREE
int	tree_init(t_tree **tree, t_lexer *lexer, char *str)
{
	*tree = malloc(sizeof(t_tree));
	if (!tree)
	{
		free(str);
		free_mat(lexer->env);
		directexit("Cannot allocate memory\n", 4);
	}
	if (tree)
		(*tree)->content = emptyclean(ft_strdup(str), lexer, 0);
	if (!(*tree)->content)
	{
		free(*tree);
		return (0);
	}
	if (emptystring((*tree)->content))
	{
		free((*tree)->content);
		free(*tree);
		return (0);
	}
	root_tree_init(tree, lexer, str);
	return (1);
}
