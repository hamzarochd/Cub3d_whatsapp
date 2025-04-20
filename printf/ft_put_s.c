/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:55:57 by ymouigui          #+#    #+#             */
/*   Updated: 2023/11/19 04:19:59 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ft_printf.h"

int	ft_put_s(char *str)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	if (str == NULL)
	{
		total += ft_put_s("(null)");
		return (total);
	}
	while (str[i])
	{
		total += ft_put_c(str[i]);
		i++;
	}
	return (total);
}
