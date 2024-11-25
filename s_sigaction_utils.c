/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_sigaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:05:01 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/07 13:05:28 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		s_sts(130);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_heredoc(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		s_here(130);
		s_sts(130);
		close(STDIN_FILENO);
	}
}

void	signal_main(struct sigaction sa)
{
	sa.sa_sigaction = handle_sigint;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction (SIGINT, &sa, NULL);
	sig_ignore(&sa, SIGQUIT);
}

void	signal_child(struct sigaction sa)
{
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	s_sts(130);
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_heredoc(struct sigaction sa)
{
	sa.sa_sigaction = handle_heredoc;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	sig_ignore(&sa, SIGQUIT);
}
