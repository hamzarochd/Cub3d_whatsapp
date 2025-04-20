/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:50:30 by ymouigui          #+#    #+#             */
/*   Updated: 2023/11/19 00:47:13 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ft_printf.h"

int	ft_exec(va_list args, char c)
{
	int	total;

	total = 0;
	if (c == 'c')
		total += ft_put_c(va_arg(args, int));
	else if (c == 's')
		total += ft_put_s(va_arg(args, char *));
	else if (c == 'p')
	{
		total += ft_put_s("0x");
		total += ft_put_p(va_arg(args, unsigned long long));
	}
	else if (c == 'd' || c == 'i')
		total += ft_put_d(va_arg(args, int));
	else if (c == 'X' || c == 'x')
		total += ft_put_x(va_arg(args, unsigned int), c);
	else if (c == 'u')
		total += ft_put_u(va_arg(args, unsigned int));
	else
		total += ft_put_c(c);
	return (total);
}
