/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:55:55 by ymouigui          #+#    #+#             */
/*   Updated: 2023/11/18 22:05:50 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ft_printf.h"

static int	len(unsigned long long str)
{
	int	len;

	len = 0;
	if (str == 0)
		return (1);
	while (str)
	{
		len++;
		str = str / 16;
	}
	return (len);
}

int	ft_put_p(unsigned long long str)
{
	int	total;

	total = len(str);
	if (str >= 16)
	{
		ft_put_p(str / 16);
		ft_put_p(str % 16);
	}
	else if (str < 16)
	{
		if (str <= 9)
			ft_put_c((str + '0'));
		else
			ft_put_c((str - 10 + 'a'));
	}
	return (total);
}
