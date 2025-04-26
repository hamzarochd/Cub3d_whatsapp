/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:13:39 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/26 16:03:23 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr_u(unsigned int n)
{
	if (n >= 10)
	{
		ft_putnbr_u(n / 10);
		ft_putnbr_u(n % 10);
	}
	else
	{
		n = n + '0';
		write (1, &n, 1);
	}
}

int	ft_put_u(unsigned int n)
{
	int	total;

	total = 0;
	if (n == 0)
		total += ft_put_c('0');
	else
	{
		ft_putnbr_u(n);
		total += ft_count(n);
	}
	return (total);
}
