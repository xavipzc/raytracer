/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 00:28:50 by svilau            #+#    #+#             */
/*   Updated: 2016/03/10 01:08:16 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_isalnum(int c)
{
	if (c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
		return (0);
	else
		return (1);
}
