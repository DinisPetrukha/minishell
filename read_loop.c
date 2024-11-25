/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:15:19 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 12:19:35 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_directory(t_lexer *lexer, int dollar)
{
	char	*cwd;
	char	*tmp;

	cwd = malloc(PATH_MAX * sizeof(char));
	if (cwd == NULL)
	{
		if (lexer->env)
			free_mat(lexer->env);
		directexit("Cannot allocate memory\n", 4);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		free(cwd);
		tmp = ft_getenv(lexer->env, "PWD");
		tmp = ft_neostrjoin(tmp, "$ ", 1);
		return (tmp);
	}
	if (dollar)
		ft_strlcat(cwd, "$ ", PATH_MAX);
	return (cwd);
}

void	tree_sorter(t_tree *tree, t_lexer *lexer, char *line,
		t_herelist *herelist)
{
	lexer->in_redir = 0;
	lexer->herelist = herelist;
	parser(tree, lexer, 0);
	checkreport(tree, lexer, line, -1);
	if (executive(tree, tree, lexer, 0) == -1)
		s_sts(1);
	tree_free(tree);
	free_nodes(&(lexer->herelist));
}

char	*input_line(t_lexer *lexer)
{
	char	*cur_dir;
	char	*line;

	setup_signal_handlers(MAIN);
	cur_dir = get_cur_directory(lexer, 1);
	line = readline(cur_dir);
	free(cur_dir);
	return (line);
}

void	shell_machine(char *line, t_herelist *herelist, t_lexer *lexer)
{
	t_tree	*tree;

	tree = NULL;
	add_history(line);
	dolquotehandle(line);
	if (!checksyntax(line, 0, 0))
	{
		if ((init_heredoc(&herelist, ft_strdup(line), lexer, 0) != -1)
			&& (tree_init(&tree, lexer, line)))
			tree_sorter(tree, lexer, line, herelist);
	}
	free(line);
}

void	read_loop(t_lexer *lexer, t_herelist *herelist)
{
	char	*line;

	while (!lexer->report)
	{
		herelist = NULL;
		line = input_line(lexer);
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		else if (*line)
		{
			if ((ft_strncmp(line, "exit", ft_strlen(line)) == 0)
				|| (ft_strncmp(line, "exit ", 6) == 0))
			{
				ft_putstr_fd("exit\n", 2);
				free (line);
				break ;
			}
			shell_machine(line, herelist, lexer);
		}
	}
	rl_clear_history();
	return (free_mat(lexer->env), exit(lexer->report));
}
