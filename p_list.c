/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:24:58 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 10:26:37 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	changelast_node(t_herelist **head, int newfd)
{
	t_herelist	*tmp;

	if (!head)
		return ;
	if (!(*head))
		return ;
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->fd = newfd;
}

int	new_node(t_herelist **head, char *content, char *str, int fd)
{
	t_herelist	*new;
	t_herelist	*tmp;

	if (!content || !str)
		return (0);
	new = malloc(sizeof(t_herelist));
	if (!new)
		return (-1);
	new->content = content;
	new->str = str;
	new->fd = fd;
	new->next = NULL;
	if (!(*head))
	{
		*head = new;
		return (0);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	popfirst(t_herelist **head, t_lexer *lexer)
{
	t_herelist	*tmp;

	if (!head)
		return ;
	if (!(*head))
		return ;
	tmp = (*head);
	(*head) = (*head)->next;
	free(tmp->content);
	free(tmp->str);
	free(tmp);
	lexer->herelist = (*head);
}

// void	printlist(t_herelist *head)
// {
// 	fprintf(stderr, "......................................\n");
// 	if (!head)
// 		return ;
// 	while (head)
// 	{
// 		fprintf(stderr, "CONTENT: %s\n", head->content);
// 		fprintf(stderr, "STR: %s\n", head->str);
// 		fprintf(stderr, "FD: %d\n", head->fd);
// 		head = head->next;
// 	}
// 	fprintf(stderr, ".....................................\n");
// }
