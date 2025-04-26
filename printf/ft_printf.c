/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:44:30 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/26 16:03:23 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *string, ...)
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
