/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:14:38 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/07 14:03:34 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

typedef enum    e_coder_status
{
    status_compiling,
    status_debugging,
    status_refactoring,
    status_waiting,
    status_burned,
}   t_coder_status;

typedef enum    e_dongle_status
{
    status_available,
    status_using,
    status_cooldown,
}   t_dongle_status;

typedef struct  s_coder
{
    int             id;
    t_coder_status  status;
    int             compile_counter;
    long            last_compile_start;
    pthread_mutex_t mutex;
}   t_coder;

typedef struct  s_dongle
{
    int             id;
    t_dongle_status status;
    long            last_release_time;
    pthread_mutex_t mutex;
}   t_dongle;

#endif