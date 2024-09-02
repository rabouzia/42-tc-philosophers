/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:27:09 by ramzerk           #+#    #+#             */
/*   Updated: 2024/08/23 10:34:39 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long 	time_get(void)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL)== -1)
		return 0;
	return ((tv.tv_sec * 1000) + (tv.tv_sec / 1000));
}
