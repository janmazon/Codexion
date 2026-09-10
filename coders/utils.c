/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:36:45 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 13:37:50 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_stop(t_coder *coder)
{
	int	status;

	pthread_mutex_lock(coder->stop_mutex);
	status = *(coder->stop_flag);
	pthread_mutex_unlock(coder->stop_mutex);
	return (status);
}

void	print_status(t_coder *coder, char *status)
{
	long	time;

	pthread_mutex_lock(coder->print_mutex);
	if (check_stop(coder) == 1)
	{
		pthread_mutex_unlock(coder->print_mutex);
		return ;
	}
	time = get_time() - coder->params->start_time;
	printf("%ld %d %s\n", time, coder->id, status);
	pthread_mutex_unlock(coder->print_mutex);
}
