# FT_PRINTF

This project was completed in April 2021 as part of the 42 school cursus. The aim was to compile a library containing the functions from our [libft](https://github.com/Magueija/libft) and our own version of the printf function.

All modifications must respect the [42 norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).


## Solving the problem

This problem requires to do more advanced **parsing**, and also to use **variadic functions** since printf takes an undefined number of arguments.


## Using ft_printf

```
int   ft_printf(format, ...);
```

ft_printf receives a string, called the format, which may contain a number of placeholders introduced by the character % and concluded by the type of conversion (string to string, int to decimal, int to hexa, etc.). Between the '%' and the conversion may be a number of options: flags, modifiers (which modify the length of the expected data), field and precision. <br />
A placeholder consists of optional or required fields in this form: %\[flags\]\[width\]\[.precision\]\[length\]specifier.

Here is a summary of the different options :

If any **specifier** is in uppercase, the result is the same as its lower specifier but the output will be printed in uppercase.
| Specifier | Type of argument | Effect |
|:----------:|:----------------:|:------:|
| d / i | int | Prints an int in decimal form |
| f | double | Prints a float (default precision is 6) |
| e | double | Prints a float in cientific notation form (default precision is 6) |
| g | double | Signed values are displayed in f or e format, whichever is more compact for the given value and precision |
| u | unsigned int | Prints an unsigned int in decimal form |
| o | unsigned int | Prints an int in octal form |
| x | unsigned int | Prints an int in hexadecimal form (lowercase) |
| c | char | Prints a char |
| s | char * | Prints a string |
| p | void * | Prints a pointer's address |
| n | int * | Number of characters that are successfully written so far to the stream |
| % | - | Prints % |

The field **width** is the minimum length of the string resulting from the conversion, and is given with a number. By default, if the resulting string is shorted that the field width, the resulting string is aligned on the right and spaces are used to fill the extra characters on the left.

The field **precision** is also a number, preceded with a point. For diuox conversions, it corresponds to the minimum length of the string, padded with 0 on the left if the result of the conversion is shorter than the precision. For feg conversion, it specifies the number of digits after the decimal point. For s conversions, it gives the maximum number of characters to be printed from the argument.

| Flag | Effect |
|:----:|:------:|
| - | Left-justify within the field width |
| + | Forces positive numbers to be preceded with a '+' sign |
| ' ' (space) | If no sign is going to be written, a blank space is inserted before the value |
| # | o and x conversions are preceded with 0 or 0x respectively |
| 0 | Pads with zeros instead of the default spaces |

| Length | Effect |
|:---------:|:------:|
| hh | di accept a signed char, uox an unsigned char |
| h | di accept a short int, uox an unsigned short int |
| l | di accept a long int, uox an unsigned long int, c a wint_t and s a wchar_t * |
| ll | di accept a long long int, uox an unsigned long long int |


## Getting Started

Run the command `make` to create the **libftprintf.a** library file located in the *bin* folder. See the exemple bellow :
```
cd ft_printf
make
gcc -I./libft/include -I./include/ -L./bin/ -lftprintf main.c -o test
```

<br />

All available **Makefile** commands :
 - `make debug`       : creates *libftprintf.a*, but with debug flags (-g -fsanitize=address);
 - `make norm`        : checks the norm on all *ft_printf* files, [norminnette](https://github.com/42School/norminette/) needs to be installed; 
 - `make norm_libft`  : checks the norm on all libft files or only for a folder like `make norm_libft f=char`;
 - `make clean`       : removes all object files;
 - `make fclean`      : removes all object files and library files (.a);
 - `make clean_dep`   : removes all dependencies files;
 - `make clean_debug` : removes all debug files and folders;
 - `make clean_all`   : equals to *make fclean* && *make clean_dep* && *make clean_debug*;
 - `make re_debug`    : equals to *make fclean* && *make debug*;
 - `make re`          : equals to *make fclean* && *make*;


## Testing

The project was tested with the *test/* files and with the following testers:
 - [printfTester](https://github.com/Tripouille/printfTester)
 - [pft](https://github.com/gavinfielder/pft)
 - [42TESTERS-PRINTF](https://github.com/Mazoise/42TESTERS-PRINTF)

Thanks to everyone who made these testers! Helped me a lot! :heart:


## Authors

  - **[Magueija](https://github.com/Magueija)**
