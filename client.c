/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:52:04 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/13 19:45:30 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		i--;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
		return (ft_printf("Error\nUsage: <PID> <Message>\n"), 1);
	pid = ft_atoi(av[1]);
	i = 0;
	while (av[2][i])
	{
		send_char(pid, av[2][i]);
		i++;
	}
	send_char(pid, av[2][i]);
}
