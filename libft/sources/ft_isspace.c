/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:04:56 by melwong           #+#    #+#             */
/*   Updated: 2025/07/15 10:22:17 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	char	*whitespace;

	whitespace = WHITESPACE;
	while (*whitespace)
	{
		if (c == *whitespace)
			return (1);
		whitespace++;
	}
	return (0);
}
