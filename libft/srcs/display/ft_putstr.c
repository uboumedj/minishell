/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:42:09 by uboumedj          #+#    #+#             */
/*   Updated: 2018/02/28 17:21:13 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putstr(char const *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		write(1, str, i);
	}
}