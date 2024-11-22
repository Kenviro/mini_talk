/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:03:50 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/22 15:05:31 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

char	*realloc_str(char *str, char c)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(ft_strlen(str) + 2);
	if (!temp)
	{
		perror("Erreur de realloc");
		free(str);
		exit(EXIT_FAILURE);
	}
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = c;
	temp[i + 1] = '\0';
	free(str);
	return (temp);
}

void	good_malloc(char c, pid_t client_pid)
{
	static char	*str = NULL;

	if (!str)
	{
		str = malloc(1);
		if (!str)
		{
			perror("Erreur de malloc");
			exit(EXIT_FAILURE);
		}
		str[0] = '\0';
	}
	if (c == '\0')
	{
		write(1, str, ft_strlen(str));
		free (str);
		str = NULL;
		if (client_pid)
			kill(client_pid, SIGUSR1);
	}
	else
		str = realloc_str(str, c);
}
