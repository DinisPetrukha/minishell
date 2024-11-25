/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_reforked_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:11:13 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:28:53 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_skipper(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	pipe_in_str(char *str, int *i)
{
	int	inquote;

	inquote = 0;
	while (str[*i])
	{
		inquote = quotealternate(inquote, str[*i]);
		if (str[*i] == '|' && !inquote)
			return (1);
		(*i)++;
	}
	return (0);
}

//cound have been made easier by just going to the right
int	pipecount(t_tree *tree)
{
	int	npipes;

	npipes = 0;
	if (tree->left)
		npipes = pipecount(tree->left);
	if (tree->right)
		npipes = pipecount(tree->right);
	if (tree->pipe_flag == 1)
		npipes++;
	return (npipes);
}

t_tree	*find_cmd(t_tree *tree)
{
	if (!tree)
		return (NULL);
	while (tree)
	{
		if (tree->left->id != REDIR)
			return (tree->left);
		tree = tree->right;
	}
	return (NULL);
}

//CASES OF PIPE, FIRST LEFT NODE IS CMD
t_tree	*left_cmd(t_tree *tree)
{
	if (!tree)
		return (NULL);
	if (tree->left->id == CMD)
		return (tree->left);
	return (tree);
}
