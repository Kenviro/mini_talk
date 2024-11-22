/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:49:12 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/21 12:02:29 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(150);
		i--;
	}
}

void	send_message(int pid, const char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int			pid;
	const char	*message;

	if (argc != 3)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	message = argv[2];
	send_message(pid, message);
	return (0);
}
