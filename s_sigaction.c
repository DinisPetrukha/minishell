/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_sigaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:39:27 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:37:03 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_ignore(struct sigaction *sa, int signal)
{
	struct sigaction	sa_origin;

	sa->sa_handler = SIG_IGN;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(signal, sa, &sa_origin);
}

void	setup_signal_handlers(t_signals sig)
{
	static struct sigaction	sa;

	if (sig == MAIN)
		signal_main(sa);
	if (sig == CHILD)
		signal_child(sa);
	else if (sig == HEREDOC)
		signal_heredoc(sa);
	else if (sig == IGNORE)
	{
		sig_ignore(&sa, SIGINT);
		sig_ignore(&sa, SIGQUIT);
	}
}
