/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:13:39 by ymouigui          #+#    #+#             */
/*   Updated: 2023/11/19 04:30:03 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ft_printf.h"

static int	ft_count(int n)
{
	int	i;

	i = 1;
	if (n > 0)
		i = 0;
	if (n == 0)
		return (i);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr_d(int n)
{
	if (n == -2147483648)
	{
		write (1, "-2", 2);
		ft_putnbr_d(147483648);
	}
	else if (n < 0)
	{
		write (1, "-", 1);
		n = n * -1;
		ft_putnbr_d(n);
	}
	else if (n >= 10)
	{
		ft_putnbr_d(n / 10);
		ft_putnbr_d(n % 10);
	}
	else
	{
		n = n + '0';
		write (1, &n, 1);
	}
}

int	ft_put_d(int n)
{
	int	total;

	total = 0;
	ft_putnbr_d(n);
	total = ft_count(n);
	return (total);
}
