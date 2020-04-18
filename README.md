# FT_PRINTF

Ft_printf is a near-total recreation of the C language's printf() function. This project is an exercise in large project management, and also an introduction to variable arguments in C.

## Getting Started

To set up this project, run `git clone https://github.com/mint42/printf` in the folder of your choosing. You can compile this library by, in the root of the project's repository, running the `make` command, and compile the tester for the program by running `make test`.

Then run the program using `./test`.

If you're interested in making your own tester for this project, the `man printf` page is compatible with ft_printf() as well. The only difference is that classic printf() has undefined behavior warnings at compile time, and this ft_printf() will print a [shruggie ¯\_(ツ)_/¯](http://letmegooglethat.com/?q=shruggie) in the place of undefined behavior.

## Notes

This project is built into a recreated cstdlib. The up-to-date library that is used in future projects can be found [here](https://github.com/mint42/libft), but this repository is still around for testing purposes. 

It currently is only compilable on macOS, but the ft_printf found in my 42 library (linked above) has been updated for linux compatibility.

Unlike classic printf(), this ft_printf() does not handle an internal buffer. It uses write() calls to print, so output will follow the flow of the program.

## Author

[Ari Reedy](https://github.com/mint42/)
