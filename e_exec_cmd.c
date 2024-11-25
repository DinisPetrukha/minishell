/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:04:39 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:57:51 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*set_command(char *str)
{
	int		len;
	int		len_cmd;
	int		i;
	char	*cmd;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = len;
	while (i > 0 && str[i - 1] != '/')
		i--;
	len_cmd = len - i;
	cmd = malloc(len_cmd + 1);
	if (cmd == NULL)
		return (NULL);
	cmd[len_cmd] = '\0';
	while (len_cmd > 0)
		cmd[--len_cmd] = str[--len];
	return (cmd);
}

char	**join_tokens(t_tree *tree, int n_tokens)
{
	char	**mat;
	int		i;

	while (tree && tree->left->id == REDIR)
		tree = tree->right;
	if (!tree)
		return (NULL);
	if (tree->right)
		n_tokens += find_nid(tree->right, TOKEN);
	mat = ft_calloc(sizeof(char *), (n_tokens + 1));
	if (mat == NULL)
		return (perror("Error. Malloc() join_tokens()\n"), NULL);
	mat[0] = set_command(tree->left->content);
	if (tree->right)
	{
		i = 1;
		while (i < n_tokens)
		{
			tree = tree->right;
			mat[i++] = ft_strdup(tree->left->content);
		}
	}
	return (mat);
}
