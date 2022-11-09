/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/08 20:19:41 by mtaib            ###   ########.fr       */
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
		write(1,"-",1);
		n *= -1;
		//c++;
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

void ft_printnb(int n,int *cn)
{
	unsigned int 	nb;
	nb = n;
	//if(c!='u')
	//{
		if (n < 0)
		{
			nb = n * -1;
		}
	//}
	if (nb / 10)
		ft_printnb(nb/10,cn);
	ft_putchar((nb % 10) + 48,cn);

}
int handle_zero_spaces(int a,int b,char c,int *cn)
{
	int	i;
	i = 0;
	while (a > b)
	{
		i++;
		ft_putchar(c,cn);
                a--;
	}
	i = i + b;
	return (i);
}
void ft_putnbr_original(int n,int pwd,int *cn,int mwd,t_list *pt)
{
	int		i;
	/*while (pwd > nlen(n))
		{
			i++;
			ft_putchar('0',cn);
			pwd--;
		}
*/
	if (pt->minus)
	{
		if (pt->per)	
		{
			i = handle_zero_spaces(pwd,nlen(n),'0',cn);
			ft_printnb(n,cn);
			if (n < 0)
				i++;
			handle_zero_spaces(mwd,i,' ',cn);
		}
		else
		{
			i = nlen(n);
			ft_printnb(n,cn);
			if (n < 0)
                                i++;
                        handle_zero_spaces(mwd,i,' ',cn);
		}
	}
	if (pt->width)
	{
		if (pt->per)
		{
			if (n < 0)
                                i++;
			handle_zero_spaces(mwd,i,' ',cn);
			handle_zero_spaces(pwd,nlen(n),'0',cn);
			ft_printnb(n,cn);
		}
		else
		{
			i = nlen(n);
			handle_zero_spaces(mwd,i,' ',cn);
			ft_printnb(n,cn);
		}	
	}
	/*while (mwd > i)
	{
		ft_putchar(' ',cn);
		mwd--;
	}*/
}

void	ft_putnbr(int n,char *str,int *cn,t_list *pt)
{
	int		pwd;
	int		mwd;
	int		i;
	i = 0;
	pwd = 0;
	mwd = 0;
	//if (pt->state)
	//{
		if (pt->width)
			mwd = ft_atoi(&str[i]);
		if (pt->zero && !(pt->minus && pt->per))
			mwd = ft_atoi(&str[i]);
		if (pt->minus)
			mwd = ft_atoi(&str[i+1]);
		if (pt->per)
		{
			while(str[i] && str[i] != '.')
				i++;
			if (str[i])
				pwd = ft_atoi(&str[i+1]);
		}
		ft_putnbr_original(n,pwd,cn,mwd,pt);
	//}

	
}
