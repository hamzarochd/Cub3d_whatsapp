/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:56:03 by ymouigui          #+#    #+#             */
/*   Updated: 2023/11/19 04:23:31 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ft_printf.h"

static int	len(unsigned int str)
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

int	ft_put_x(unsigned int str, char c)
{
	int	total;

	total = len(str);
	if (str >= 16)
	{
		ft_put_x(str / 16, c);
		ft_put_x(str % 16, c);
	}
	else if (str < 16)
	{
		if (str <= 9)
			ft_put_c((str + '0'));
		else
		{
			if (c == 'x')
				ft_put_c((str - 10 + 'a'));
			if (c == 'X')
				ft_put_c((str - 10 + 'A'));
		}
	}
	return (total);
}
