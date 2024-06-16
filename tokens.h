// enum{
//     IF=1, // if
//     ELSE, // else
//     FOR, // for
//     IN, // in
//     WHILE, // while
//     LOOP, // loop
//     FUN, // fun
//     VAR, // var
//     VAL, // val
//     NUM, // numeric
//     REAL, // numeric real
//     COMPARISON, // comparison
//     ALLOC, // allocation
//     LP, //(
//     RP, //)
//     LC, // {
//     RC,// }
//     LB, // [
//     RB,// ]
//     ID, // VAR, function... names
//     MATH, // +,  -, /, *, **
//     TEXT, // string
//     TYPE, // Int, Long, String, Float, Double, Boolean, Char
//     COLON, // :
//     FINALIZE, // ;
// }

#ifndef TOKENS_H
#define TOKENS_H

#define IF 1
#define ELSE 2
#define FOR 3
#define IN 4
#define WHILE 5
#define LOOP 6
#define FUN 7
#define VAR 8
#define VAL 9
#define TYPE 10
#define NUM 11
#define ID 12
#define COMPARISON 13
#define ALLOC 14
#define LP 15
#define RP 16
#define LC 17
#define RC 18
#define LB 19
#define RB 20
#define MATH 21
#define TEXT 22
#define COLON 23
#define COMMA 24
#define LOGIC 25
#define FINALIZE 26

#endif // TOKENS_H
