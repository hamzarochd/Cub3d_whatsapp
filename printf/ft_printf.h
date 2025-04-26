/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:56:11 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/26 16:03:23 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef printf_H
# define printf_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>

int		printf(const char *string, ...);
int		ft_exec(va_list args, char c);
int		ft_put_c(char c);
int		ft_put_s(char *str);
int		ft_put_x(unsigned int str, char c);
int		ft_put_p(unsigned long long str);
int		ft_put_d(int n);
int		ft_put_u(unsigned int n);

#endif