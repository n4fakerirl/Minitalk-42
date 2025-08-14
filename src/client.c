/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:52:04 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/14 18:18:20 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (ft_putstr_fd("Error\nCan't send signal.\n", 2), 0);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (ft_putstr_fd("Error\nCan't send signal.\n", 2), 0);
		}
		usleep(200);
		i--;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
		return (ft_putstr_fd("Error\nUsage: <PID> <Message>\n", 2), 1);
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1 || pid == 0)
		return (ft_putstr_fd("Error\nPID doesn't exist.\n", 2), 1);
	i = 0;
	while (av[2][i])
	{
		if (!send_char(pid, av[2][i]))
			return (1);
		i++;
	}
	if (!send_char(pid, av[2][i]))
		return (1);
	return (0);
}
