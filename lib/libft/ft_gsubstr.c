/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gsubstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:05:20 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/10 15:07:13 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gsubstr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	new = o_malloc(sizeof(char) * (len - start + 1), 0);
	while (start + i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	return (new[i] = '\0', new);
}
