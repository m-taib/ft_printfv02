#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
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
void hexlong(long int nb,int *ptr)
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
	hexlong((long int)pt,ptr);
}
void	placeholder(char c,int *ptr,va_list args)
{
	if(c == 'c')
		return 1;		
	if(c == 's')
		ft_strlen(va_arg(args,char *),ptr);
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
typedef struct flags
{
	int width;
	int zero;
	int pre;
	int space;
	int hash;
	int plus;
	int mines;
}flags;
int	check_flags(char c,flags flag)
{
	if (c == '+')
		flag.plus = 1;
	if (c == '-')
                flag.plus = 1;
	if (c == ' ')
                flag.plus = 1;
	if (c == '#')
                flag.plus = 1;
	if (c == '0')
                flag.plus = 1;
	if (c == '+' || c == '-' || c == ' ' || c == '#' || c == '0')
		return 1;
	return 0;
}
int     size(int n)
{
        int     c;
        c = 0;
        if (n < 0)
        {
                c++;
                n *= -1;
        }
        while (n)
        {
                n = n /10;
                c++;
        }
        return (c);
}

int     ft_atoi(const char *str)
{
        int     i;
        int     res;
        int     sign;
        sign = 1;
        res = 0;
        i = 0;
        while (str[i] >= 0 && str[i] <= 32)
                i++;
        while (str[i] == '-' || str[i] == '+')
        {
                if (str[i] =='-')
                        sign *= -1;
                i++;
        }
        while(str[i] >='0' && str[i] <='9')
        {
                res = res * 10 + (str[i] - 48);
                i++;
        }
        return (res * sign);
}
int    width_c(char c,int *ptr,va_list args)
{
	int i;
	i = 0;
        if(c == 'c')
                i++:
        if(c == 's')
                i = ft_strlen(va_arg(args,char *));
        if(c == 'd' || c == 'i')
                i = size(va_arg(args,int));
        if(c == 'u')
                i = size(va_arg(args,unsigned int));
        if(c == 'x' || c == 'X')
                i = size(va_arg(args,int)) + 2;
        if(c == 'p')
                i = size((long int)va_arg(args,void *));
	return i;
}

int ft_printf(const char *str, ...)
{
	flags flag;
	va_list args;
	va_start(args,str);
	int	i;
	int	cn;
	int	wd;
	cn = 0;
	i = 0;
	
	width_c(str[i],args,wd);
	while (i < ft_strlen(str))
	{
		if(str[i] != '%')
			ft_putchar(str[i],&cn);
		else
		{
			i++;
			
			wd = ft_atoi(str+ i);
			while (wd)
			{
				ft_putchar(' ',&cn);
				wd--;
			}
			width_c(str[i],args,wd);
			while(check_flags((str[i]),flag))
				i++;
			placeholder(str[i],&cn,args);
		}
		i++;
	}
	va_end(args);
	return (cn);
}

int	main()
{
	int *p;

}
