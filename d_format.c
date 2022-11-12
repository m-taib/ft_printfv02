/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/12 20:12:17 by mtaib            ###   ########.fr       */
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

void ft_printnb(int n,int *cn,int status)
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
	if (!status)
		if (n < 0)
			write(1,"-",1);
	if (nb / 10)
		ft_printnb(nb/10,cn,status);
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
	int	s;
	s = 0;
	if (pt->space && !pt->width )//&& !pwd )//&& !mwd)//(pt->minus || pt->per))
	{
		write(1," ",1);
		if (!pt->width && !pwd && !mwd)	
			ft_printnb(n,cn,pt->status);
	}
	
	if (pt->minus)
	{
		if (pt->per)	
		{

			i = pwd;
			if (pt->plus && (n >= 0))// || n < 0))
			{mwd--;
				if (n > 0)
					s = 1;}
			if (pwd > nlen(n))
				if (pwd > i + nlen(n))
					i = pwd;
				else
					i = nlen(n);
			else
				i = nlen(n);
			if (n < 0)
				write(1,"-",1);
			if (s == 1)
			{
				mwd++;
				write(1,"+",1);
			}
			i = handle_zero_spaces(pwd,i,'0',cn);
			ft_printnb(n,cn,pt->status);
			if (n < 0)
				i++;
			handle_zero_spaces(mwd,i,' ',cn);
		}
		else
		{
			i = nlen(n);
			if (pt->plus && n > 0)
				write(1,"+",1);
			if ( n < 0)
				write(1,"-",1);
			ft_printnb(n,cn,pt->status);
			if (n < 0)
				i++;
            		handle_zero_spaces(mwd,i,' ',cn);
		}
	}
	if ((pt->width || pt->plus) && !pt->minus)
	{
		if (pt->per || pt->plus)
		{
			if (pt->plus && (n >= 0)) //|| n < 0))
			{	
				//mwd--;
				if (n >= 0)
					s = 1;}
			i = nlen(n);
			if (pwd > nlen(n))
			{
				i = pwd;
				if (mwd >= i )//+ nlen(n))
					i = pwd;
				else
					i = nlen(n);
				if (pt->plus && n > 0)
					i++;
			}
			else
				if (!pt->plus)
					i = nlen(n);
				else 
					if (n > 0)
						i = nlen(n) + 1;
			if (n < 0)
				mwd--;
				//i++;
			if (mwd > i)
				handle_zero_spaces(mwd,i,' ',cn);
			if (s == 1)
				write(1,"+",1);
			if (n < 0)
				write(1,"-",1);
			if (pwd > nlen(n))
				handle_zero_spaces(pwd,nlen(n),'0',cn);
			ft_printnb(n,cn,pt->status);
		}
		else
		{
			i = nlen(n);
			if (pt->plus && (n > 0))// || n < 0))
				mwd--;
			if (n < 0)
				mwd--;
			handle_zero_spaces(mwd,i,' ',cn);
			if (pt->plus && n > 0)
				write(1,"+",1);
			if (n < 0)
				write(1,"-",1);
			ft_printnb(n,cn,pt->status);
		}	
	}
}

void	ft_putnbr(int n,char *str,int *cn,t_list *pt)
{
	int		pwd;
	int		mwd;
	int		i;
	i = 0;
	pwd = 0;
	mwd = 0;
	if (pt->status)
	 {
		if (pt->plus && (!pt->width && !pt->minus && pt->zero && pt->per))
			mwd = 1;
		if (pt->width)
			mwd = ft_atoi(&str[i]);
		if (pt->zero && !(pt->minus && pt->per))
			mwd = ft_atoi(&str[i]);

		if (pt->minus)
		{
			if (pt->space || pt->plus)
			{
				while(str[i] && str[i] != '-')
					i++;
				if (n > 0)
					mwd = ft_atoi(&str[i]) - 1;
				else
					mwd = ft_atoi(&str[i]);
			}
			else
				mwd = ft_atoi(&str[i]);
		}
		if (pt->per)
		{
			while(str[i] && str[i] != '.')
				i++;
			if (str[i])
				pwd = ft_atoi(&str[i+1]);
		}
		ft_putnbr_original(n,pwd,cn,mwd,pt);
	}
	else
		ft_printnb(n,cn,pt->status);
	
}
