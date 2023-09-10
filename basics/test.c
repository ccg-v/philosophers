/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:20:07 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/08 20:34:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		i;
	char	str[5];

	strcpy(str, "hola");
	i = 0;
	while (i < 5)
	{
		printf("i = %d\n", i);
		printf("%s\n", str);
		i++;
	}
	return (0);
}
