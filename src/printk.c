#include <stdarg.h>
#include "monitor.h"

int printk( const char *fmt, ... )
{
	va_list args;
	va_start(args, fmt);
	int count;
	char buf[20];
	int len = 8;
	
	while ( *fmt != 0 )
	{
		switch ( *fmt ){
			case '%':
				fmt++;
				switch ( *fmt )
            {
				case 'd':
				case 'i':   //int
					sitoa(buf, 10, va_arg(args, int));
                    monitor_write (buf);
					break;
				case 'u':	// Unsigned
					sitoa(buf, 16, va_arg( args, unsigned int));
                    monitor_write (buf);
					break;
				case 's':	// string (char*)
                    monitor_write (va_arg(args, char*));
					break;
				case 'c':	// char
                    monitor_put (va_arg(args, char));
					break;
                case 'x':   //hex
                    monitor_write_hex (va_arg(args, unsigned int));
            }
				fmt++;
				break;
			default:
                monitor_put(*fmt);
				fmt++;
		}
		count++;
	}
	//move_cursor();
	va_end(args);
	return count;
}
