/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:44:30 by ymouigui          #+#    #+#             */
/*   Updated: 2023/11/19 04:12:12 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ft_printf.h"

int	ft_ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		total;

	i = 0;
	total = 0;
	va_start (args, string);
	if (write(1, "", 0) == -1)
		return (-1);
	while (string[i])
	{
		if (string[i] == '%')
		{
			if (!string[i + 1])
				break ;
			total += ft_exec(args, string[i + 1]);
			i++;
		}
		else
			total += ft_put_c(string[i]);
		i++;
	}
	va_end(args);
	return (total);
}
