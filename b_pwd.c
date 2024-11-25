/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:44:56 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:05:53 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(void)
{
	char	*ptr;
	int		size;

	ptr = NULL;
	size = 1024;
	ptr = (char *)ft_calloc(size, sizeof(char));
	if (ptr == NULL)
		return (-1);
	ptr = getcwd(ptr, 1024);
	ft_putstr_fd(ptr, STDOUT_FILENO);
	ft_putchar_fd(10, STDOUT_FILENO);
	free(ptr);
	return (0);
}
