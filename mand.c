/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:02:44 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/08 11:10:13 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c,int *ptr)
{
	write(1,&c,1);
	*ptr = *ptr +1;;
}
void 	ft_putstr(char *str,int *ptr)
{
	int	i;
	i = 0;
	while(str[i])
	{
		ft_putchar(str[i],ptr);
		i++;
	}
}

void ft_putnbr(int n,char c,int *ptr)
{
	unsigned int 	nb;
	nb = n;
	if(c!='u')
	{
		if (n < 0)
		{
			ft_putchar('-',ptr);
			nb = n * -1;
		}
	}
	if (nb / 10)
		ft_putnbr(nb/10,c,ptr);
	ft_putchar((nb % 10) + 48,ptr);
}
void hex(unsigned int nb,char c,int *ptr)
{
	char arr[16]="0123456789abcdef";
	if (nb / 16)
		hex(nb/16,c,ptr);
	if (c == 'x')
		ft_putchar(arr[nb%16],ptr);
	else
	{
		if (arr[nb%16] >= '0' && arr[nb%16] <= '9')
		       ft_putchar(arr[nb%16],ptr);
		else
			ft_putchar(arr[nb%16] - 32,ptr);
	}
}
void hexlong(unsigned long nb,int *ptr)
{
        char arr[16]="0123456789abcdef";
        if (nb / 16)
                hexlong(nb/16,ptr);
        ft_putchar(arr[nb%16],ptr);
}

void	hexvalue(void *pt,int *ptr)
{
	ft_putchar('0',ptr);
	ft_putchar('x',ptr);
	hexlong((unsigned long)pt,ptr);
}

void	placeholder(char c,int *ptr,va_list args)
{
	if(c == 'c')
        	ft_putchar(va_arg(args,int),ptr);
	if(c == 's')
	{
		char *str;
		str = va_arg(args,char *);
		if (!str)
			str = "(null)";
		ft_putstr(str,ptr);
	}
      	if(c == 'd' || c == 'i')
       		ft_putnbr(va_arg(args,int),c,ptr);
        if(c == 'u')
        	ft_putnbr(va_arg(args,unsigned int),c,ptr);
        if(c == 'x' || c == 'X')
               	hex(va_arg(args,int),c,ptr);
        if(c == 'p')
               	hexvalue(va_arg(args,void *),ptr);
        if(c == '%')
              	ft_putchar('%',ptr);

}

int ft_printf(const char *str, ...)
{
	va_list args;
	t_list *data;
	data = libft_calloc(1,sizeof(t_list));
	va_start(args,str);
	int	i;
	int	cn;
	cn = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] != '%')
			ft_putchar(str[i],&cn);
		else
		{
			i++;
			placeholder(str[i],&cn,args);
		}
		i++;
	}
	va_end(args);
	return (cn);
}
