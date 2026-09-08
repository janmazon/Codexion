/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 13:14:38 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/07 17:15:51 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdio.h>

typedef enum    e_coder_status
{
    STATUS_COMPILING,
    STATUS_DEBUGGING,
    STATUS_REFACTORING,
    STATUS_WAITING,
    STATUS_BURNED,
}   t_coder_status;

typedef enum    e_dongle_status
{
    STATUS_AVAILABLE,
    STATUS_USING,
    STATUS_COOLDOWN,
}   t_dongle_status;

typedef enum    e_scheduler
{
    FIFO,
    EDF,
}   t_scheduler;

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

typedef struct  s_parameters
{
    int         number_of_coders;
    long        time_to_burnout;
    long        time_to_compile;
    long        time_to_debug;
    long        time_to_refactor;
    int         number_of_compiles_required;
    long        dongle_cooldown;
    t_scheduler scheduler;
}   t_parameters;

#endif