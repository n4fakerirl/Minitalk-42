/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/10 02:56:59 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(char bit)
{
    
}

int	main(void)
{
    int serv_pid;

    serv_pid = getpid();
    printf("Server PID : %d\n", serv_pid);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
}
