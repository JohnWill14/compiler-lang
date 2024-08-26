 bison  -d Parser.y
flex scanner.l
gcc -o Lang *.c -lm
