# nasm-long-numbers

upd: MUL_LINUX.asm seems to work under Linux
     (SUB_LINUX.asm seems to work on Linux as well)

Target OS - Mac OS
To make it work on Linux : 
1) set propper siscall numbers in defines at the top of programmes (0, 1, 60)
2) change start to _start
3) (optionaly) change .data to .rodata
