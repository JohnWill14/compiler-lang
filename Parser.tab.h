/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    REAL = 259,                    /* REAL  */
    IDENTIFIER = 260,              /* IDENTIFIER  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    FOR = 263,                     /* FOR  */
    WHILE = 264,                   /* WHILE  */
    LOOP = 265,                    /* LOOP  */
    TYPE = 266,                    /* TYPE  */
    TEXT = 267,                    /* TEXT  */
    ALLOC = 268,                   /* ALLOC  */
    NUM = 269,                     /* NUM  */
    MATH = 270,                    /* MATH  */
    COMPARISON = 271,              /* COMPARISON  */
    LOGIC = 272,                   /* LOGIC  */
    FUN = 273,                     /* FUN  */
    VAR = 274,                     /* VAR  */
    VAL = 275,                     /* VAL  */
    IN = 276,                      /* IN  */
    LP = 277,                      /* LP  */
    RP = 278,                      /* RP  */
    LC = 279,                      /* LC  */
    RC = 280,                      /* RC  */
    LB = 281,                      /* LB  */
    RB = 282,                      /* RB  */
    PARAMETERS = 283,              /* PARAMETERS  */
    PARAMETER = 284,               /* PARAMETER  */
    BLOCK = 285,                   /* BLOCK  */
    COLON = 286,                   /* COLON  */
    COMMA = 287,                   /* COMMA  */
    FINALIZE = 288,                /* FINALIZE  */
    PRINT = 289,                   /* PRINT  */
    BREAK_TOKEN = 290,             /* BREAK_TOKEN  */
    RETURN_TOKEN = 291,            /* RETURN_TOKEN  */
    ALLOC_LABEL = 292,             /* ALLOC_LABEL  */
    OPERATION_LABEL = 293          /* OPERATION_LABEL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 58 "Parser.y"
union semrec
{
#line 58 "Parser.y"
 /* The Semantic Records */

    int intval; /* Integer values */
    int doubleval; /* Double values */
    char *id; /* Identifiers */
    struct lbs *lbls; /* For backpatching */

#line 111 "Parser.tab.h"

};
#line 58 "Parser.y"
typedef union semrec YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
