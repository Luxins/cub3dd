/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:17:01 by raweber           #+#    #+#             */
/*   Updated: 2022/10/17 15:30:11 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		strlen;

	if (!s1)
		return (NULL);
	strlen = ft_strlen(s1);
	dest = malloc(strlen + 1);
	if (dest == 0)
		return (0);
	ft_strcpy(dest, s1);
	return (dest);
}
