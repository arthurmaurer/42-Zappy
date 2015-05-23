/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 02:48:00 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/23 00:33:32 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

size_t	dlist_index(t_dlist *node)
{
	size_t	i;
	t_dlist	*iter;

	i = 0;
	iter = dlist_first(node);
	while (iter)
	{
		if (iter == node)
			return (i);
		iter = iter->next;
		i++;
	}
	return (DLIST_NOINDEX);
}