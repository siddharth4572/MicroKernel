#include <stdint.h>
#include <stdarg.h>
#include "printk.h"
#include "string.h"
#include "cursor.h"
#include "term.h"

static	int	get_flag(char c)
{
	int		ret = 0;

	switch (c)
	{
		case 's':
			ret = PRINTK_STR;
			break ;
		case 'p':
			ret = PRINTK_PTR;
			break ;
		case 'c':
			ret = PRINTK_CHR;
			break ;
		case 'd':
			ret = PRINTK_INT;
			break ;
		case 'x':
			ret = PRINTK_HEX32;
			break ;
		case 'X':
			ret = PRINTK_HEX64;
			break ;
		case 'b':
			ret = PRINTK_BIN;
			break ;
	}
	return (ret);
}

static void	get_str(va_list *ap, char *loc_buff)
{
	char *n = va_arg(*ap, char*);
	strcpy(loc_buff, n);
}

static void	get_ptr(va_list *ap, char *loc_buff)
{
	uint32_t	n = va_arg(*ap, uint32_t);
	loc_buff[0] = '0';
	loc_buff[1] = 'x';
	itoa_base_buf(n, 16, loc_buff + 2);
}

static void	get_char(va_list *ap, char *loc_buff)
{
	int		c = va_arg(*ap, int);
	loc_buff[0] = (char)c;
	loc_buff[1] =  0;
}

static void	get_int(va_list *ap, char *loc_buff)
{
	int		n = va_arg(*ap, int);
	itoa_buf(n, loc_buff);
}

static void	get_hex32(va_list *ap, char *loc_buff)
{
	uint64_t	n = va_arg(*ap, uint32_t);
	itoa_base_buf(n, 16, loc_buff);
}

static void	get_hex64(va_list *ap, char *loc_buff)
{
	uint64_t	n = va_arg(*ap, uint64_t);
	itoa_base_buf(n, 16, loc_buff);
}

static void	get_bin(va_list *ap, char *loc_buff)
{
	uint32_t	n = va_arg(*ap, uint32_t);
	itoa_base_buf(n, 2, loc_buff);
}

static void	flush_printk_buff(char *buff, size_t *j)
{
	term_write(buff, *j);
	update_cursor(terminal_column, terminal_row);
	*j = 0;
}

static void	process_flag(va_list *ap, int flag, char *buff, size_t *j)
{
	static void (*fl[PRINTK_FLAGS_LEN])(va_list *ap, char *loc_buff) = {0x0, get_str,
			get_ptr, get_char, get_int, get_hex32, get_hex64, get_bin};
	size_t	len;
	char	loc_buff[128];

	bzero(loc_buff, 128);
	fl[flag](ap, loc_buff);
	len = strlen(loc_buff);
	if (*j + len > PRINTK_BUFF_LEN)
	{
		flush_printk_buff(buff, j);
	}
	strcat(buff, loc_buff);
	*j += len;
}

int		printk(const char *restrict format, ...)
{
	va_list	ap;
	size_t	len = strlen(format);
	size_t	j = 0;
	char	buff[PRINTK_BUFF_LEN];
	int		flag;

	bzero(buff, PRINTK_BUFF_LEN);
	va_start(ap, format);
	for (size_t i = 0; i < len; i++)
	{
		if (format[i] == '%' && i + 1 < len)
		{
			if ((flag = get_flag(format[i + 1])) != 0)
			{
				process_flag(&ap, flag, buff, &j);
			}
			else if (format[i + 1] == '%')
			{
				buff[j] = '%';
				j++;
			}
			i++;
		}
		else
		{
			buff[j] = format[i];
			j++;
		}

		if (j == PRINTK_BUFF_LEN && i + 1 < len)
			flush_printk_buff(buff, &j);
	}
	va_end(ap);
	flush_printk_buff(buff, &j);
	return (0);
}
