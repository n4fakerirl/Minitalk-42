/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/10 06:50:06 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server	*server;

void	signal_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		server->charc |= (1 << server->bits);
	}
	server->bits++;
	if (server->bits == 8)
	{
		if (server->charc == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", server->charc);
		server->charc = 0;
		server->bits = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	server = malloc(sizeof(t_server));
	if (!server)
		return (0);
	ft_printf("PID: %d\n", getpid());
	ft_bzero(server, sizeof(t_server));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
