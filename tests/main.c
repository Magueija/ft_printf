#include <stdio.h>
#include "ft_printf.h"
#include <float.h>

int main()
{

	/* // All
	ft_printf("All:\n");
	ft_printf("ft_printf: %c %s %p %d %i %u %x %X\n", c, "str", p, -123, 2147483650, 2147483648, 26, 10);
	   printf("   printf: %c %s %p %d %i %u %x %X\n\n", c, "str", p, -123, 2147483650, 2147483648, 26, 10);

	// char (c)
	ft_printf("char (c):\n");
	ft_printf("ft_printf: |%c|-|%60c|-|%-010c|-|%011c|-|%-00c|-|%1c|-|%hc|-|%*c|-|%*c|-|%hc|-|%.5c|-|%.*c|\n", c, c, c, c, c, c, c, -5, c, 5, 'C', "是", c, 3, c);
	   printf("   printf: |%c|-|%60c|-|%-010c|-|%011c|-|%-00c|-|%1c|-|%hc|-|%*c|-|%*c|-|%hc|-|%.5c|-|%.*c|\n\n", c, c, c, c, c, c, c, -5, c, 5, 'C', "是", c, 3, c);
	
	// string (s)
	ft_printf("string (s):\n");
	ft_printf("ft_printf: |%s|-|%-s|-|%-010s|-|%011s|-|%-00s|-|%1s|-|%hs|-|%*s|-|%*s|-|%hs|-|%.5s|-|%.*s|\n", s, s, s, s, s, s, s, -5, s, 5, s, s, s, 3, s);
	   printf("   printf: |%s|-|%-s|-|%-010s|-|%011s|-|%-00s|-|%1s|-|%hs|-|%*s|-|%*s|-|%hs|-|%.5s|-|%.*s|\n\n", s, s, s, s, s, s, s, -5, s, 5, s, s, s, 3, s);

	// pointer (p)
	ft_printf("pointer (p):\n");
	ft_printf("ft_printf: |%p|-|%+p|-|%-015p|-|%020p|-|%-00p|-|%1p|-|% hp|-|%*p|-|% *p|-|%hp|-|%.5p|-|%.*p|\n", p, p, p, p, p, p, p, -5, p, 5, p, p, p, 3, p);
	   printf("   printf: |%p|-|%+p|-|%-015p|-|%020p|-|%-00p|-|%1p|-|% hp|-|%*p|-|% *p|-|%hp|-|%.5p|-|%.*p|\n\n", p, p, p, p, p, p, p, -5, p, 5, p, p, p, 3, p);
	
	// int (i/d)
	ft_printf("int (i/d):\n");
	ft_printf("ft_printf: |%i|-|%+li|-|%-010.5i|-|%015.10i|-|%-00d|-|% 1d|-|% hd|-|%*d|-|% *d|-|%.5hd|-|%.5d|-|%.*d|\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	   printf("   printf: |%i|-|%+li|-|%-010.5i|-|%015.10i|-|%-00d|-|% 1d|-|% hd|-|%*d|-|% *d|-|%.5hd|-|%.5d|-|%.*d|\n\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	
	// unsigned int (u)
	ft_printf("unsigned int (u):\n");
	ft_printf("ft_printf: |%u|-|%+lu|-|%-010.5u|-|%015.10u|-|%-00u|-|% 1u|-|% hu|-|%*u|-|% *u|-|%.5hu|-|%.5u|-|%.*u|\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	   printf("   printf: |%u|-|%+lu|-|%-010.5u|-|%015.10u|-|%-00u|-|% 1u|-|% hu|-|%*u|-|% *u|-|%.5hu|-|%.5u|-|%.*u|\n\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	
	// hexadecimal (x/X)
	ft_printf("hexadecimal (x/X):\n");
	ft_printf("ft_printf: |%x|-|%+lx|-|%-010.5X|-|%015.10X|-|%-00x|-|% 1X|-|% hx|-|%*X|-|% *x|-|%.5hX|-|%.5x|-|%.*X|\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	   printf("   printf: |%x|-|%+lx|-|%-010.5X|-|%015.10X|-|%-00x|-|% 1X|-|% hx|-|%*X|-|% *x|-|%.5hX|-|%.5x|-|%.*X|\n\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	
	// octal (o)
	ft_printf("octal (o):\n");
	ft_printf("ft_printf: |%o|-|%+lo|-|%-010.5o|-|%015.10o|-|%-00o|-|% 1o|-|% ho|-|%*o|-|% *o|-|%.5ho|-|%.5o|-|%.*o|\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	   printf("   printf: |%o|-|%+lo|-|%-010.5o|-|%015.10o|-|%-00o|-|% 1o|-|% ho|-|%*o|-|% *o|-|%.5ho|-|%.5o|-|%.*o|\n\n", 123, 2147483647, 012, 15268479, 150000001, -25, 9, -5, 0, 5, 15, -32769, 300, 3, 10);
	

	// float (f)
	double f = 300.9999;
	ft_printf("float (f):\n");
	   printf("   printf: |%-010.5lf|\n", f);
	ft_printf("ft_printf: |%-010.5lf|\n", f);
	   
	int nb;
	// float (f)
	ft_printf("float (f):\n");
	nb = ft_printf("ft_printf: |%#f|-|%+llf|-|%-010.5llf|-|%015.10llf|-|%-00llf|-|% 1llf|-|%f|-|%*llf|-|% *llf|-|%.5f|-|%.5llf|-|%.*lf|\n", 123.0, 2147483647.0, 012.345, 15268479.5354, 150000001.24, -25.60, 9.0, 24, 0.0, 5, 15.000005, -32769.235, 300.9999, 3, 10.0);
	ft_printf("\t%i\n", nb);
	nb =    printf("   printf: |%#f|-|%+llf|-|%-010.5llf|-|%015.10llf|-|%-00llf|-|% 1llf|-|%f|-|%*llf|-|% *llf|-|%.5f|-|%.5llf|-|%.*lf|\n", 123.0, 2147483647.0, 012.345, 15268479.5354, 150000001.24, -25.60, 9.0, 24, 0.0, 5, 15.000005, -32769.235, 300.9999, 3, 10.0);
	   printf("\t%i\n\n", nb);
	// nº printed (n)
	ft_printf("nº printed (n):\n");
	ft_printf("ft_printf: 12345%n6789\n", &i);
	ft_printf("%i\n", i);
	   printf("   printf: 12345%n6789\n", &i);
	   printf("%i\n", i);
	 */

	int w;
	
	// random
	w = ft_printf("%g", "tomas magueija silva");
	ft_printf("\n%i\n", w);
	w =    printf("%g", 2.122E-314);
	printf("\n%i\n", w);

	return 0; // 0.22250738585072014e-308 -1.17e-3 
}
