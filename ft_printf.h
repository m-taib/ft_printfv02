#ifndef FT_PRINTF_H
#define FT_PRINTF_H 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
typedef struct t_list
{
	 int status;
     int minus;
     int zero;
     int per;
     int dec;
     int width;
	 int space;
	 int plus;
}t_list;
int ft_printf(const char *str, ...);
int     ft_strlen(const char *str);
void    ft_putchar(char c,int *ptr);
void    ft_putstr(char *str,int *ptr);
void	ft_putnbr(int n,char *st,int *cn,t_list *pt);
void hex(unsigned int nb,char c,int *ptr);
void hexlong(unsigned long nb,int *ptr);
void    hexvalue(void *pt,int *ptr);
void	placeholder(char *str,char c,int *ptr,va_list args,t_list *pt);
int ft_atoi(const char *str);
int     nlen(long int n);
char *ft_itoa(int n);
#endif
