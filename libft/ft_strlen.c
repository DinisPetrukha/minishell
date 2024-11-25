/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:11:40 by sephilip          #+#    #+#             */
/*   Updated: 2024/10/04 10:20:17 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//updated
size_t	ft_strlen(const char *s)
{
	unsigned int	size;

	size = 0;
	if (!(*s))
		return (0);
	while (s[size])
		size++;
	return (size);
}
/*
int	main()
{
	char	str[] = "abcdefghij \n10012";

	//printf"%d\n", ft_strlen(str));
	//printf"%d\n", strlen(str));
	return (0);
}*/
