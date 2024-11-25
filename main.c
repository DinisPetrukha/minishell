/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:11:39 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 12:24:09 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// void	tree_reader(t_tree *tree, int n)
// {
// 	printf("[%i]------------------------------------\n", n);
// 	printf("ID: %d ", tree->id); if (tree->id == NL)
// 		printf("[NULL]\n");
// 	else if (tree->id == JOB)
// 		printf("[JOB]\n");
// 	else if (tree->id == CMD)
// 		printf("[CMD]\n");
// 	else if (tree->id == REDIR)
// 		printf("[REDIR]\n");
// 	else if (tree->id == NAME)
// 		printf("[NAME]\n");
// 	else if (tree->id == TOKEN)
// 		printf("[TOKEN]\n");
// 	printf("tree->content:%s\n", tree->content);
// 	printf("pipe_flag: %i\n", tree->pipe_flag);
// 	printf("pipe_fd[0]: %i pipe_fd[1]: %i\n", tree->pipefd[0], tree->pipefd[1]);
// 	printf("redir type: %d\n", tree->redir_type);
// 	if(tree->left)
// 	{
// 		printf("\033[0;33mVAI PARA ESQ\033[0m\n");
// 		tree_reader(tree->left, n + 1);
// 	}
// 	if(tree->right)
// 	{
// 		printf("\033[0;31mVAI PARA DIR\033[0m\n");
// 		tree_reader(tree->right, n + 1);
// 	}
// }

int	error_heredoc(t_herelist **head, char *redir, char *str, int level)
{
	if (level == 1)
	{
		free(redir);
		free(str);
		ft_putstr_fd("Error: Malloc()\n", 2);
		s_sts(4);
	}
	if (level == 2)
	{
		if (head)
			free_nodes(head);
	}
	return (-1);
}

int	s_here(int new_status)
{
	static int	status;

	if (new_status != -1)
		status = new_status;
	return (status);
}

int	s_sts(int new_status)
{
	static int	status;

	if (new_status != -1)
		status = new_status;
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer		lexer;
	t_herelist	herelist;

	argc++;
	argv[0] = NULL;
	lexer.report = 0;
	lexer.start = 0;
	lexer.end = 0;
	lexer.in_redir = 0;
	lexer.status = 0;
	lexer.willexpand = 1;
	lexer.child = 0;
	herelist.fd = 0;
	lexer.herelist = NULL;
	s_sts(0);
	lexer.env = ft_enviroment(envp);
	if (envp[0])
		increment_shlvl(lexer.env);
	read_loop(&lexer, &herelist);
	free_mat(lexer.env);
}
