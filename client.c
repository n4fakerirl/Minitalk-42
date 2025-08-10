/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:52:04 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/10 06:52:15 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	size_t	len;
	size_t	i;

	if (ac != 3)
		return (write(2, "Usage: ./client <PID> <Message>\n", 32), 1);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (write(2, "Error: Invalid PID\n", 19), 1);
	len = ft_strlen(av[2]);
	if (len > MAX_MSG_SIZE)
		return (write(2, "Error: Message too long\n", 24), 1);
	i = 0;
	while (i <= len)
	{
		send_char(pid, av[2][i]);
		i++;
	}
	return (0);
}
