//#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
typedef struct t_list
{
	int minus;
	int zero;
	int per;
	int dec;
}t_list;
void    *ft_memset(void *b, int c, size_t len)
{
        size_t          i;
        unsigned char           *str;

        str = (unsigned char *)b;
        i = 0;
        while (i < len)
        {
                str[i] = c;
                i++;
        }
        return ((void *)(str));
}
void    ft_bzero(void *s, size_t n)
{
        ft_memset(s, 0, n);
}

void    *ft_calloc(size_t count, size_t size)
{
        void    *ptr;

        ptr = malloc(count * size);
        if (!ptr)
                return (NULL);
        ft_bzero(ptr, count*size);
        return (ptr);
}

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
        	ft_putchar(va_arg(args,int),ptr);
	if(c == 's')
        	ft_putstr(va_arg(args,char *),ptr);
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
// ITOA
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

///////
void comb(char *str,int *ptr,va_list args,t_list *pt)
{
	int cn;
	int	i;
	int	cz;
	int n;
	cz = 0;
	i = 0;
	cn = 0;
	if (pt->minus == 1)
		cn = ft_atoi(str+1);
	if (pt->minus == 1 && pt->dec == 1)
	{
		while (str[i] && str[i] != '.')
			i++;
		i++;
		n = va_arg(args,int);
		cz = ft_atoi(str + i) - nlen(n);
		cn = cn - cz - nlen(n);
		while(cz--)
			write(1,"0",1);
		ft_putnbr(n,'d',ptr);
		while(cn--)
			write(1," ",1);	
	}
}
void check(char *str,int *ptr,va_list args,t_list *pt)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			pt->minus = 1;
		if (str[i] == '0')
			pt->zero = 1;
		if (str[i] == 'd')
			pt->dec = 1;
		i++;
	}
	if (str[i] == '.')
		pt->per = 1;
	comb(str,ptr,args,pt);
}
int ft_printf(const char *str, ...)
{
	va_list args;
	t_list *data;
	data = ft_calloc(1,sizeof(t_list));
	va_start(args,str);
	int	i;
	int	cn;
	cn = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		if(str[i] != '%') //|| (data->minus != 1 || data->dec != 1))
			ft_putchar(str[i],&cn);
		else
		{
			i++;
			check((char *)(str + i),&cn,args,data);
			break;
			//placeholder(str[i],&cn,args);
		}
		i++;
	}
	va_end(args);
	return (cn);
}
int main()
{
	int b;
	b = 6;
	ft_printf("%-10.2d",b);
	printf("||\n%-10.2d",b);
}
/*
int main()
{
	char c = 'a';
	char *s = "string";
	int i = -132454845;
	int x = 1213432;
	int x2 = 0;
	unsigned int u = 2147483649;
	int amp = 12;
	int n;
	char *sc = "";
	int	*ptr;

	int ret = 0;
	int ret2 = 0;


	write(1,"\n|____MANDATORY____|\n",21);

	//char test
	write(1,"\n|%c basic test|\n",17);

	ret = printf("printf c:%cl\n", c);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf c:%cl\n", c);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 c:%c, %cl\n", c, c);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 c:%c, %cl\n", c, c);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%% basic test|\n",17);

	ret = printf("printf %%:%%l\n");
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf %%:%%l\n");
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 %%:%%, \n");
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 %%:%%, \n");
	ft_printf("ft_printf num:%i\n", ret2);

	//integer test
	write(1,"\n|%i basic test|\n",17);

	ret = printf("printf i:%il\n", i);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf i:%il\n", i);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 i:%i, %il\n", i, i);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 i:%i, %il\n", i, i);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%d basic test|\n",17);

	ret = printf("printf d:%dl\n", i);
	printf("printf num:%d\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf d:%dl\n", i);
	ft_printf("ft_printf num:%d\n", ret2);

	ret = printf("printf 2 d:%d, %dl\n", i, i);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 d:%d, %dl\n", i, i);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%u basic test|\n",17);

	ret = printf("printf u:%ul\n", u);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf u:%ul\n", u);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 u:%u, %ul\n", u, u);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 u:%u, %ul\n", u, u);
	ft_printf("ft_printf num:%i\n", ret2);

	//str test
	write(1,"\n|%s basic test|\n",17);

	ret = printf("printf s:%sl\n", s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf s:%sl\n", s);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 s:%s, %sl\n", s, s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 s:%s, %sl\n", s, s);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%p basic test|\n",17);

	ret = printf("printf p:%pl\n", s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf p:%pl\n", s);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 p:%p, %pl\n", s, s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 p:%p, %pl\n", s, s);
	ft_printf("ft_printf num:%i\n", ret2);

	//hexadecimal test
	write(1,"\n|%x basic test|\n",17);

	ret = printf("printf x:%xl\n", x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf x:%xl\n", x);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 x:%x, %xl\n", x, x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 x:%x, %xl\n", x, x);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%X basic test|\n",17);

	ret = printf("printf X:%Xl\n", x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf X:%Xl\n", x);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 X:%X, %Xl\n", x, x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 X:%X, %Xl\n", x, x);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|Multiple specifiers test|\n",28);

	ret = printf("printf c, %%, d, i, u, s, p, x, X:%c, %%, %d, %i, %u, %s, %p, %x, %Xl\n", c, i, i, u, s, s, x, x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf c, %%, d, i, u, s, p, x, X:%c, %%, %d, %i, %u, %s, %p, %x, %Xl\n", c, i, i, u, s, s, x, x);
	ft_printf("ft_printf num:%i\n\n\n", ret2);


	x = 0;
	ptr = &x;

	printf("ft_printf: \n");
	i = ft_printf("Hello My Name is: %c%c%c%c%c %s and Im %d years and %X years in hex, My adress is %p, print %% with no argument\n", 'A','y','m','a','n',"Bouabra",18,18,ptr);
	printf("%d\n\n", i);
	printf("printf: \n");
	i = printf("Hello My Name is: %c%c%c%c%c %s and Im %d years and %X years in hex, My adress is %p, print %% with no argument\n", 'A','y','m','a','n',"Bouabra",18,18,ptr);
	printf("%d\n", i);

	return 0;
}*/
