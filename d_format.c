/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/07 11:29:16 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		arb;
	int		res;
	arb = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
				|| str[i] == '\t' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			arb *= -1;
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * arb);
}

int		nlen(long int n)
{
	int		c;
	c = 0;
	if (n < 0)
	{
		n *= -1;
		c++;
	}
	if (n ==0)
		c++;
	while(n)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char *ft_itoa(int n)
{
	char	*str;
	int		i;
	long	j;
	long nb;
	nb = n;

	i = nlen(n);
	str = (char *)malloc(sizeof(char) *( nlen(nb)+1));
	if (!str)
		return (NULL);
	j = 0;
	if (nb < 0)
	{
		nb*= -1;
		str[j] = '-';
		j++;
	}
	str[i] = '\0';
	i--;
	while (i >= j)
	{
		str[i] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	return (str);
}
