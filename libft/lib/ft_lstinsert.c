/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:54:49 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/04 15:12:48 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_list *lst, t_list *cell)
{
	cell->next = lst->next;
	lst->next = cell;
}
