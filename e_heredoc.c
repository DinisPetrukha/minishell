/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:11:35 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 13:37:09 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_childprocess(int piper[2], char *eof, t_lexer *lexer)
{
	char	*gnl;

	while (1)
	{
		gnl = readline(">");
		if (gnl == NULL)
			break ;
		if (ft_strlen(gnl) == (ft_strlen(eof))
			&& (ft_strncmp(gnl, eof, ft_strlen(eof)) == 0))
			break ;
		if (!lexer->willexpand)
			ft_putstr_fd(gnl, piper[1]);
		else
		{
			gnl = hereexpander(gnl, lexer, lexer->willexpand, 0);
			if (*gnl)
				ft_putstr_fd(gnl, piper[1]);
		}
		ft_putstr_fd("\n", piper[1]);
		if (*gnl)
			free(gnl);
	}
}

int	read_heredoc(int piper[2], char *eof, t_lexer *lexer, t_herelist **head)
{
	int		status;
	int		pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (perror("Error heredoc fork()\n"), -1);
	if (pid == 0)
	{
		setup_signal_handlers(HEREDOC);
		close(piper[0]);
		heredoc_childprocess(piper, eof, lexer);
		close(piper[1]);
		free_mat(lexer->env);
		free_nodes(head);
		exit(s_here(-1));
	}
	waitpid(pid, &status, 0);
	get_status(status);
	return (pid);
}

int	ft_heredoc(char *eof, t_lexer *lexer, t_herelist **head)
{
	int		piper[2];
	int		child;

	if (pipe(piper) == -1)
	{
		perror("Pipe error\n");
		return (-1);
	}
	setup_signal_handlers(IGNORE);
	child = read_heredoc(piper, eof, lexer, head);
	if (child == -1 || s_sts(-1) == 130)
		return (-1);
	close(piper[1]);
	return (piper[0]);
	return (-1);
}

int	pre_heredoc(char *str, int i)
{
	if (str[i + 1] && (str[i + 1] == 34 || str[i + 1] == 39))
	{
		str[i] = ' ';
		return (1);
	}
	i = i - 1;
	while (i >= 0)
	{
		if (str[i] == '<')
		{
			if ((i - 1 >= 0) && str[i - 1] == '<')
				return (1);
		}
		if (ft_isspace(str[i]))
			i--;
		else
			break ;
	}
	return (0);
}

int	init_heredoc(t_herelist **head, char *str, t_lexer *lexer, int i)
{
	int		fd;
	char	*redir;

	redir = NULL;
	i = findheredir(str);
	if (i > -1)
	{
		s_here(0);
		redir = isredir(&str[i], lexer, 1);
		if (redir)
		{
			if (new_node(head, redir, str, 0) != 0)
				return (error_heredoc(head, redir, str, 1));
			lexer->herelist = *head;
			fd = ft_heredoc(redir, lexer, head);
			if (fd == -1)
				return (error_heredoc(head, redir, str, 2));
			changelast_node(head, fd);
		}
		if (init_heredoc(head, remain(&str[i], lexer), lexer, 0) == -1)
			return (error_heredoc(head, redir, str, 2));
	}
	if (!redir)
		free(str);
	return (0);
}
