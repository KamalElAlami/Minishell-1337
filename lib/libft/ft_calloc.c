/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:26:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/08 22:20:15 by kael-ala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total_case;

	if (count > 0 && SIZE_MAX / count < size)
		return (NULL);
	total_case = count * size;
	ptr = o_malloc(total_case, 0);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_case);
	return (ptr);
}
