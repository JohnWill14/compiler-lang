/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Parser.y"

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include "SymbolTable.h" 
#include "Tree.h"
#include "Print_tree.h" 
#ifndef YYDEBUG  
    #define YYDEBUG 1
#endif
extern int yylineno;
extern char* yytext;

int errors; 

int yylex(void);
int yyerror(char* s);


//SymbolTable
void add_identify_var(char *sym_name, int nivel, char* name_function, bool constante, char* type){
    symvar *s;
    s = getsymVar(sym_name, nivel, name_function);
    if (s == NULL)
        s = putsymVar(sym_name, nivel, name_function, constante, type);
    else { 
        errors++;
        printf( "variable %s is already defined in %s\n", sym_name, s->function);
    }
}

void check_var(char *sym_name, int nivel, char* name_function){
    symvar *s;
    s = getsymVar(sym_name, nivel, name_function);
    if (s == NULL){ 
        errors++;
        printf( "variable %s not is defined. line %d\n", sym_name, yylineno);
    }
}


void add_identify_func ( Tree* function ){
    symfunc *s;
    s = getsymfunc (function->label);
    if (s == NULL){
        Node* no = list_getItem(function->neighbors, 0);
        Tree* lista_de_parametros = no->value;
        int tam_p = list_get_size(lista_de_parametros->neighbors);
        char** name_array = (char **) malloc(sizeof(char *) * tam_p);
        int count = 0;

        list_forEach(non, lista_de_parametros->neighbors){
            Tree* tno = (Tree*)non->value;
            Node* no_type = list_getItem(tno->neighbors, 0);
            Tree* tno_type = (Tree*) no_type->value;

            name_array[count] = (char *) malloc (strlen(tno_type->label)+1);
            strcpy (name_array[count],tno_type->label);

            add_identify_var(tno->label, 1, function->label, 0, tno_type->label);

            count++;
        }


        Node* no_type = list_getItem(function->neighbors, 1);
        Tree* tno_type = (Tree*) no_type->value;
        char* type = (char *) malloc (strlen(tno_type->label)+1);
        strcpy (type,tno_type->label);

        s = putsymfunc (function->label, name_array, tam_p, type );
    } else { 
        errors++;
        printf( "function %s is already defined\n", function->label );
    }
}

void add_call ( Tree* call){

    int tam_p = list_get_size(call->neighbors);
    char** name_array = (char **) malloc(sizeof(char *) * tam_p);
    int count = 0;
    list_forEach(non, call->neighbors){

        Tree* tno = (Tree*)non->value;
        name_array[count] = (char *) malloc (strlen(tno->label)+1);
        strcpy (name_array[count],tno->label);
        count++;
    }

     putsymCall (yylineno, call->label, function_current, name_array, tam_p, nivel_block_current);
}

void context_check_func(char *sym_name ){ 
    symfunc *identifier;
    identifier = getsymfunc( sym_name );
    if ( identifier == NULL){ 
        errors++;
        printf( "%s", sym_name );
        printf( "%s\n", " is an undeclared identifier" );
    }
}


#line 176 "Parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_REAL = 4,                       /* REAL  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_LOOP = 10,                      /* LOOP  */
  YYSYMBOL_TYPE = 11,                      /* TYPE  */
  YYSYMBOL_TEXT = 12,                      /* TEXT  */
  YYSYMBOL_ALLOC = 13,                     /* ALLOC  */
  YYSYMBOL_NUM = 14,                       /* NUM  */
  YYSYMBOL_MATH = 15,                      /* MATH  */
  YYSYMBOL_COMPARISON = 16,                /* COMPARISON  */
  YYSYMBOL_LOGIC = 17,                     /* LOGIC  */
  YYSYMBOL_FUN = 18,                       /* FUN  */
  YYSYMBOL_VAR = 19,                       /* VAR  */
  YYSYMBOL_VAL = 20,                       /* VAL  */
  YYSYMBOL_IN = 21,                        /* IN  */
  YYSYMBOL_LP = 22,                        /* LP  */
  YYSYMBOL_RP = 23,                        /* RP  */
  YYSYMBOL_LC = 24,                        /* LC  */
  YYSYMBOL_RC = 25,                        /* RC  */
  YYSYMBOL_LB = 26,                        /* LB  */
  YYSYMBOL_RB = 27,                        /* RB  */
  YYSYMBOL_PARAMETERS = 28,                /* PARAMETERS  */
  YYSYMBOL_PARAMETER = 29,                 /* PARAMETER  */
  YYSYMBOL_BLOCK = 30,                     /* BLOCK  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_COMMA = 32,                     /* COMMA  */
  YYSYMBOL_FINALIZE = 33,                  /* FINALIZE  */
  YYSYMBOL_PRINT = 34,                     /* PRINT  */
  YYSYMBOL_BREAK_TOKEN = 35,               /* BREAK_TOKEN  */
  YYSYMBOL_RETURN_TOKEN = 36,              /* RETURN_TOKEN  */
  YYSYMBOL_ALLOC_LABEL = 37,               /* ALLOC_LABEL  */
  YYSYMBOL_OPERATION_LABEL = 38,           /* OPERATION_LABEL  */
  YYSYMBOL_CALL_FUNCTION = 39,             /* CALL_FUNCTION  */
  YYSYMBOL_CALL_PARAM = 40,                /* CALL_PARAM  */
  YYSYMBOL_41_ = 41,                       /* '+'  */
  YYSYMBOL_42_ = 42,                       /* '-'  */
  YYSYMBOL_43_ = 43,                       /* '*'  */
  YYSYMBOL_44_ = 44,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_code = 47,                      /* code  */
  YYSYMBOL_function = 48,                  /* function  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_declarations_parameter = 51,    /* declarations_parameter  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_declaration_parameter = 53,     /* declaration_parameter  */
  YYSYMBOL_block = 54,                     /* block  */
  YYSYMBOL_command = 55,                   /* command  */
  YYSYMBOL_56_4 = 56,                      /* $@4  */
  YYSYMBOL_57_5 = 57,                      /* $@5  */
  YYSYMBOL_declarations = 58,              /* declarations  */
  YYSYMBOL_declaration = 59,               /* declaration  */
  YYSYMBOL_60_6 = 60,                      /* $@6  */
  YYSYMBOL_declaration_val = 61,           /* declaration_val  */
  YYSYMBOL_62_7 = 62,                      /* $@7  */
  YYSYMBOL_63_8 = 63,                      /* $@8  */
  YYSYMBOL_attribution = 64,               /* attribution  */
  YYSYMBOL_65_9 = 65,                      /* $@9  */
  YYSYMBOL_66_10 = 66,                     /* $@10  */
  YYSYMBOL_novo_valor = 67,                /* novo_valor  */
  YYSYMBOL_operation = 68,                 /* operation  */
  YYSYMBOL_69_11 = 69,                     /* $@11  */
  YYSYMBOL_70_12 = 70,                     /* $@12  */
  YYSYMBOL_label_abstrato = 71,            /* label_abstrato  */
  YYSYMBOL_72_13 = 72,                     /* $@13  */
  YYSYMBOL_73_14 = 73,                     /* $@14  */
  YYSYMBOL_74_15 = 74,                     /* $@15  */
  YYSYMBOL_75_16 = 75,                     /* $@16  */
  YYSYMBOL_while = 76,                     /* while  */
  YYSYMBOL_77_17 = 77,                     /* $@17  */
  YYSYMBOL_78_18 = 78,                     /* $@18  */
  YYSYMBOL_logik = 79,                     /* logik  */
  YYSYMBOL_80_19 = 80,                     /* $@19  */
  YYSYMBOL_comparator = 81,                /* comparator  */
  YYSYMBOL_82_20 = 82,                     /* $@20  */
  YYSYMBOL_logic_c = 83,                   /* logic_c  */
  YYSYMBOL_84_21 = 84,                     /* $@21  */
  YYSYMBOL_condition = 85,                 /* condition  */
  YYSYMBOL_86_22 = 86,                     /* $@22  */
  YYSYMBOL_87_23 = 87,                     /* $@23  */
  YYSYMBOL_condition_pod = 88,             /* condition_pod  */
  YYSYMBOL_89_24 = 89,                     /* $@24  */
  YYSYMBOL_breakkk = 90,                   /* breakkk  */
  YYSYMBOL_91_25 = 91,                     /* $@25  */
  YYSYMBOL_return_ss = 92,                 /* return_ss  */
  YYSYMBOL_93_26 = 93,                     /* $@26  */
  YYSYMBOL_return_type = 94,               /* return_type  */
  YYSYMBOL_95_27 = 95,                     /* $@27  */
  YYSYMBOL_call_function = 96,             /* call_function  */
  YYSYMBOL_97_28 = 97,                     /* $@28  */
  YYSYMBOL_98_29 = 98,                     /* $@29  */
  YYSYMBOL_parameter_func = 99,            /* parameter_func  */
  YYSYMBOL_100_30 = 100,                   /* $@30  */
  YYSYMBOL_101_31 = 101,                   /* $@31  */
  YYSYMBOL_102_32 = 102,                   /* $@32  */
  YYSYMBOL_103_33 = 103,                   /* $@33  */
  YYSYMBOL_104_34 = 104,                   /* $@34  */
  YYSYMBOL_parameter_final = 105           /* parameter_final  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    43,    41,     2,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   139,   139,   141,   143,   147,   155,   146,   168,   169,
     169,   177,   178,   180,   181,   183,   183,   186,   186,   193,
     196,   197,   198,   201,   202,   205,   206,   210,   210,   221,
     228,   221,   240,   240,   252,   252,   265,   266,   268,   271,
     271,   275,   275,   279,   282,   282,   287,   289,   287,   293,
     293,   300,   306,   300,   315,   315,   321,   325,   330,   335,
     335,   342,   343,   343,   348,   353,   348,   362,   363,   363,
     372,   374,   374,   380,   380,   389,   390,   394,   399,   399,
     406,   408,   406,   414,   415,   415,   419,   419,   423,   423,
     427,   429,   427,   434,   435
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "REAL",
  "IDENTIFIER", "IF", "ELSE", "FOR", "WHILE", "LOOP", "TYPE", "TEXT",
  "ALLOC", "NUM", "MATH", "COMPARISON", "LOGIC", "FUN", "VAR", "VAL", "IN",
  "LP", "RP", "LC", "RC", "LB", "RB", "PARAMETERS", "PARAMETER", "BLOCK",
  "COLON", "COMMA", "FINALIZE", "PRINT", "BREAK_TOKEN", "RETURN_TOKEN",
  "ALLOC_LABEL", "OPERATION_LABEL", "CALL_FUNCTION", "CALL_PARAM", "'+'",
  "'-'", "'*'", "'/'", "$accept", "program", "code", "function", "$@1",
  "$@2", "declarations_parameter", "$@3", "declaration_parameter", "block",
  "command", "$@4", "$@5", "declarations", "declaration", "$@6",
  "declaration_val", "$@7", "$@8", "attribution", "$@9", "$@10",
  "novo_valor", "operation", "$@11", "$@12", "label_abstrato", "$@13",
  "$@14", "$@15", "$@16", "while", "$@17", "$@18", "logik", "$@19",
  "comparator", "$@20", "logic_c", "$@21", "condition", "$@22", "$@23",
  "condition_pod", "$@24", "breakkk", "$@25", "return_ss", "$@26",
  "return_type", "$@27", "call_function", "$@28", "$@29", "parameter_func",
  "$@30", "$@31", "$@32", "$@33", "$@34", "parameter_final", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-79)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -9,    10,    18,    -9,   -92,   -92,   -92,   -92,    14,    19,
       9,    16,    32,    15,   -92,    34,    20,   -92,    19,   -92,
      24,   -92,     2,    37,   -92,   -92,   -92,   -92,   -92,   -92,
      26,     2,   -92,   -92,   -92,   -92,   -92,   -92,    31,    33,
      35,    36,    49,    54,    27,     8,   -92,   -92,   -92,    11,
       0,     5,     5,    30,   -92,    38,   -92,   -92,    40,   -92,
      39,    11,    41,   -92,   -92,   -92,    11,   -92,   -92,   -92,
     -92,    42,   -92,   -92,    43,    45,   -92,   -92,    47,    52,
      48,    62,    63,    53,   -92,   -92,    55,    11,    11,    11,
      11,    56,   -92,    44,    44,    44,   -92,    58,   -92,   -92,
      57,   -92,   -92,     0,     0,   -92,   -92,   -92,   -92,    11,
       0,     0,   -92,   -92,   -92,    50,     0,    60,     5,   -92,
      -1,    65,    59,    64,   -92,   -92,   -92,   -92,    66,     2,
      71,     2,    49,   -92,   -92,   -92,   -92,   -92,    67,   -92,
      68,   -92,   -92,    69,   -92,    11,    11,    44,    84,     5,
     -92,   -92,   -92,   -92,    86,   -92,   -92,   -92,    72,     2,
      70,   -92
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     5,     1,     4,     2,     0,     8,
       0,     0,     0,     0,     9,     0,    11,     6,     8,    10,
       0,    12,    13,    80,    64,    51,    15,    17,    71,    73,
       0,    13,    19,    20,    21,    22,    23,    24,    32,     0,
       0,     0,     0,     0,     0,    75,     7,    14,    34,     0,
      83,     0,     0,     0,    16,     0,    18,    72,    76,    77,
       0,     0,    49,    44,    39,    41,     0,    38,    33,    36,
      37,    84,    88,    86,     0,    57,    58,    56,     0,     0,
       0,     0,     0,     0,    74,    35,     0,     0,     0,     0,
       0,     0,    90,    93,    93,    93,    81,     0,    65,    54,
       0,    27,    29,    83,    83,    50,    45,    40,    42,     0,
      83,    83,    85,    89,    87,     0,    83,     0,     0,    52,
       0,     0,     0,     0,    43,    91,    94,    82,     0,    13,
      61,    13,     0,    26,    28,    30,    79,    47,     0,    60,
       0,    62,    55,     0,    25,     0,     0,    93,    67,     0,
      53,    31,    48,    92,    68,    66,    63,    70,     0,    13,
       0,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -92,    94,   -92,   -92,   -92,   -92,    83,   -92,   -92,   -31,
     -92,   -92,   -92,   -92,   -67,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -60,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -50,   -92,   -16,   -92,   -92,   -92,
     -51,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -69,   -92,   -92,   -92,   -92,   -92,
     -91
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     3,     8,    20,    11,    16,    19,    30,
      31,    42,    43,   134,    54,   120,    56,   121,   145,    32,
      49,    61,    68,    69,    89,    90,    70,    88,    86,   146,
      87,    33,    41,   131,    78,   118,    79,    97,   142,   149,
      34,    40,   117,   155,   158,    35,    44,    36,    45,    60,
      83,    37,    39,   115,    74,    93,    95,    94,   110,   138,
     112
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    85,    80,   113,   114,    71,    91,    23,    24,     1,
      75,    25,    72,    58,    73,     4,    62,    76,     5,    77,
      59,    26,    27,    63,    10,    64,    65,   105,   106,   107,
     108,   132,   133,    66,   122,   123,     9,    28,    29,    13,
      12,   125,   126,    14,    67,    17,    15,   128,    22,   124,
      38,    46,    18,    48,    53,    50,   153,    51,    52,    55,
      57,    81,   -78,   -46,    92,   144,    96,   -59,    99,    82,
      98,   100,    84,   101,   102,   103,   111,   104,   135,   109,
     116,   119,   136,   127,   129,   151,   152,   137,   141,   139,
     147,   154,    24,   148,   150,   161,   159,     6,   140,   156,
     143,    21,   130,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160
};

static const yytype_int16 yycheck[] =
{
      31,    61,    52,    94,    95,     5,    66,     5,     6,    18,
       5,     9,    12,     5,    14,     5,     5,    12,     0,    14,
      12,    19,    20,    12,     5,    14,    15,    87,    88,    89,
      90,    32,    33,    22,   103,   104,    22,    35,    36,    23,
      31,   110,   111,    11,    33,    11,    31,   116,    24,   109,
      13,    25,    32,    22,     5,    22,   147,    22,    22,     5,
      33,    31,    22,    22,    22,   132,    23,    22,    16,    31,
      23,    23,    33,    11,    11,    22,    32,    22,    13,    23,
      22,    24,    23,    33,    24,   145,   146,    23,    17,    23,
      23,     7,     6,    25,    25,    25,    24,     3,   129,   149,
     131,    18,   118,   154,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   159
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    18,    46,    48,     5,     0,    46,    47,    49,    22,
       5,    51,    31,    23,    11,    31,    52,    11,    32,    53,
      50,    51,    24,     5,     6,     9,    19,    20,    35,    36,
      54,    55,    64,    76,    85,    90,    92,    96,    13,    97,
      86,    77,    56,    57,    91,    93,    25,    54,    22,    65,
      22,    22,    22,     5,    59,     5,    61,    33,     5,    12,
      94,    66,     5,    12,    14,    15,    22,    33,    67,    68,
      71,     5,    12,    14,    99,     5,    12,    14,    79,    81,
      79,    31,    31,    95,    33,    67,    73,    75,    72,    69,
      70,    67,    22,   100,   102,   101,    23,    82,    23,    16,
      23,    11,    11,    22,    22,    67,    67,    67,    67,    23,
     103,    32,   105,   105,   105,    98,    22,    87,    80,    24,
      60,    62,    99,    99,    67,    99,    99,    33,    99,    24,
      81,    78,    32,    33,    58,    13,    23,    23,   104,    23,
      54,    17,    83,    54,    59,    63,    74,    23,    25,    84,
      25,    67,    67,   105,     7,    88,    79,    85,    89,    24,
      54,    25
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    49,    50,    48,    51,    52,
      51,    53,    53,    54,    54,    56,    55,    57,    55,    55,
      55,    55,    55,    55,    55,    58,    58,    60,    59,    62,
      63,    61,    65,    64,    66,    64,    67,    67,    68,    69,
      68,    70,    68,    68,    72,    71,    73,    74,    71,    75,
      71,    77,    78,    76,    80,    79,    81,    81,    81,    82,
      81,    83,    84,    83,    86,    87,    85,    88,    89,    88,
      88,    91,    90,    93,    92,    94,    94,    94,    95,    94,
      97,    98,    96,    99,   100,    99,   101,    99,   102,    99,
     103,   104,    99,   105,   105
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     1,     0,     0,    12,     0,     0,
       5,     0,     2,     0,     2,     0,     3,     0,     3,     1,
       1,     1,     1,     1,     1,     2,     1,     0,     5,     0,
       0,     7,     0,     4,     0,     5,     1,     1,     1,     0,
       3,     0,     3,     4,     0,     3,     0,     0,     7,     0,
       3,     0,     0,     9,     0,     5,     1,     1,     1,     0,
       5,     0,     0,     3,     0,     0,    10,     0,     0,     5,
       2,     0,     3,     0,     4,     0,     1,     1,     0,     5,
       0,     0,     7,     0,     0,     3,     0,     3,     0,     3,
       0,     0,     7,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* $@1: %empty  */
#line 147 "Parser.y"
                      {
                    create_no((yyvsp[0].id), FUN);
                    create_no(NULL, PARAMETERS);
                }
#line 1386 "Parser.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 155 "Parser.y"
                { 
                    revert_no();
                    create_no((yyvsp[0].id), TYPE);
                    revert_no();
                    add_identify_func(current_tree);
                    create_no(NULL, BLOCK);
                }
#line 1398 "Parser.tab.c"
    break;

  case 7: /* function: FUN IDENTIFIER $@1 LP declarations_parameter RP COLON TYPE $@2 LC block RC  */
#line 164 "Parser.y"
              {
                finalize_tree();
            }
#line 1406 "Parser.tab.c"
    break;

  case 9: /* $@3: %empty  */
#line 169 "Parser.y"
                                    { 
                            create_no((yyvsp[-2].id), PARAMETER);
                            create_no((yyvsp[0].id), TYPE);
                            revert_no();
                            revert_no();
                        }
#line 1417 "Parser.tab.c"
    break;

  case 13: /* block: %empty  */
#line 180 "Parser.y"
                    {revert_no();}
#line 1423 "Parser.tab.c"
    break;

  case 15: /* $@4: %empty  */
#line 183 "Parser.y"
             {
            create_no(NULL, VAR);
        }
#line 1431 "Parser.tab.c"
    break;

  case 17: /* $@5: %empty  */
#line 186 "Parser.y"
             {
            create_no(NULL, VAL);
        }
#line 1439 "Parser.tab.c"
    break;

  case 18: /* command: VAL $@5 declaration_val  */
#line 188 "Parser.y"
                          {
                revert_no();
                revert_no();
        }
#line 1448 "Parser.tab.c"
    break;

  case 19: /* command: attribution  */
#line 193 "Parser.y"
                     {
            revert_no();
        }
#line 1456 "Parser.tab.c"
    break;

  case 22: /* command: breakkk  */
#line 198 "Parser.y"
                 {
            create_no(NULL, BREAK_TOKEN);
        }
#line 1464 "Parser.tab.c"
    break;

  case 26: /* declarations: FINALIZE  */
#line 206 "Parser.y"
                     {
            revert_no();
           }
#line 1472 "Parser.tab.c"
    break;

  case 27: /* $@6: %empty  */
#line 210 "Parser.y"
                                   {
                add_identify_var((yyvsp[-2].id), nivel_block_current, function_current, constante_current, (yyvsp[0].id));
                    
                create_no((yyvsp[-2].id), IDENTIFIER);
                create_no((yyvsp[0].id), TYPE);
                revert_no();
                revert_no();
            }
#line 1485 "Parser.tab.c"
    break;

  case 29: /* $@7: %empty  */
#line 221 "Parser.y"
                                      {
                add_identify_var((yyvsp[-2].id), nivel_block_current, function_current, constante_current, (yyvsp[0].id));
                    
                create_no((yyvsp[-2].id), IDENTIFIER);
                create_no((yyvsp[0].id), TYPE);
                revert_no();
                revert_no();
            }
#line 1498 "Parser.tab.c"
    break;

  case 30: /* $@8: %empty  */
#line 228 "Parser.y"
                    {
                create_no(NULL, ALLOC_LABEL);
                check_var((yyvsp[-4].id), nivel_block_current, function_current);
            
                create_no((yyvsp[-4].id), IDENTIFIER);
                revert_no();
                create_no((yyvsp[0].id), ALLOC);
                revert_no();
                create_no(NULL, OPERATION_LABEL);
            }
#line 1513 "Parser.tab.c"
    break;

  case 32: /* $@9: %empty  */
#line 240 "Parser.y"
                              {
            create_no(NULL, ALLOC_LABEL);
            check_var((yyvsp[-1].id), nivel_block_current, function_current);
            errors += check_var_is_Constant((yyvsp[-1].id), nivel_block_current, function_current);

            create_no((yyvsp[-1].id), IDENTIFIER);
            revert_no();
            create_no((yyvsp[0].id), ALLOC);
            revert_no();
            create_no(NULL, OPERATION_LABEL);
        }
#line 1529 "Parser.tab.c"
    break;

  case 34: /* $@10: %empty  */
#line 252 "Parser.y"
                              {
            create_no(NULL, ALLOC_LABEL);
            check_var((yyvsp[-2].id), nivel_block_current, function_current);

            create_no((yyvsp[-2].id), IDENTIFIER);
            revert_no();
            create_no((yyvsp[-1].id), ALLOC);
            revert_no();
            create_no(NULL, OPERATION_LABEL);
        }
#line 1544 "Parser.tab.c"
    break;

  case 38: /* operation: FINALIZE  */
#line 268 "Parser.y"
                   {
            revert_no();
        }
#line 1552 "Parser.tab.c"
    break;

  case 39: /* $@11: %empty  */
#line 271 "Parser.y"
              {
            create_no((yyvsp[0].id), NUM);
            revert_no();
        }
#line 1561 "Parser.tab.c"
    break;

  case 41: /* $@12: %empty  */
#line 275 "Parser.y"
              {
                create_no((yyvsp[0].id), MATH);
                revert_no();
        }
#line 1570 "Parser.tab.c"
    break;

  case 44: /* $@13: %empty  */
#line 282 "Parser.y"
                    {
                    errors += checkString((yyvsp[0].id), nivel_block_current, function_current);
                    create_no((yyvsp[0].id), TEXT);
                    revert_no();
                }
#line 1580 "Parser.tab.c"
    break;

  case 46: /* $@14: %empty  */
#line 287 "Parser.y"
                            {
                    create_no((yyvsp[0].id), CALL_FUNCTION);
                }
#line 1588 "Parser.tab.c"
    break;

  case 47: /* $@15: %empty  */
#line 289 "Parser.y"
                                       {
                    add_call(current_tree);
                    revert_no();            
                }
#line 1597 "Parser.tab.c"
    break;

  case 49: /* $@16: %empty  */
#line 293 "Parser.y"
                            {

                    check_var((yyvsp[0].id), nivel_block_current, function_current);
                    create_no((yyvsp[0].id), IDENTIFIER);
                    revert_no();
                }
#line 1608 "Parser.tab.c"
    break;

  case 51: /* $@17: %empty  */
#line 300 "Parser.y"
             {
            create_no(NULL, WHILE);
        }
#line 1616 "Parser.tab.c"
    break;

  case 52: /* $@18: %empty  */
#line 306 "Parser.y"
           {
            create_no(NULL, BLOCK);
        }
#line 1624 "Parser.tab.c"
    break;

  case 53: /* while: WHILE $@17 LP logik RP LC $@18 block RC  */
#line 310 "Parser.y"
          {
            {revert_no();}
        }
#line 1632 "Parser.tab.c"
    break;

  case 54: /* $@19: %empty  */
#line 315 "Parser.y"
                            {
            create_no((yyvsp[0].id), COMPARISON);
            revert_no();
        }
#line 1641 "Parser.tab.c"
    break;

  case 56: /* comparator: NUM  */
#line 321 "Parser.y"
                {
                 create_no((yyvsp[0].id), NUM);
                revert_no();
            }
#line 1650 "Parser.tab.c"
    break;

  case 57: /* comparator: IDENTIFIER  */
#line 325 "Parser.y"
                      {
                check_var((yyvsp[0].id), nivel_block_current, function_current);
                 create_no((yyvsp[0].id), IDENTIFIER);
                revert_no();
            }
#line 1660 "Parser.tab.c"
    break;

  case 58: /* comparator: TEXT  */
#line 330 "Parser.y"
                {
                errors += checkString((yyvsp[0].id), nivel_block_current, function_current);
                create_no((yyvsp[0].id), TEXT);
                revert_no();
            }
#line 1670 "Parser.tab.c"
    break;

  case 59: /* $@20: %empty  */
#line 335 "Parser.y"
                        {
                create_no((yyvsp[0].id), CALL_FUNCTION);
            }
#line 1678 "Parser.tab.c"
    break;

  case 60: /* comparator: IDENTIFIER $@20 LP parameter_func RP  */
#line 337 "Parser.y"
                                   {
                add_call(current_tree);
                revert_no();            
            }
#line 1687 "Parser.tab.c"
    break;

  case 62: /* $@21: %empty  */
#line 343 "Parser.y"
            {
            create_no((yyvsp[0].id), LOGIC);
            revert_no();
    }
#line 1696 "Parser.tab.c"
    break;

  case 64: /* $@22: %empty  */
#line 348 "Parser.y"
              {
            create_no(NULL, IF);
        }
#line 1704 "Parser.tab.c"
    break;

  case 65: /* $@23: %empty  */
#line 353 "Parser.y"
          {
            create_no(NULL, BLOCK);
        }
#line 1712 "Parser.tab.c"
    break;

  case 67: /* condition_pod: %empty  */
#line 362 "Parser.y"
                           {revert_no();}
#line 1718 "Parser.tab.c"
    break;

  case 68: /* $@24: %empty  */
#line 363 "Parser.y"
              {
            create_no(NULL, ELSE);
            create_no(NULL, BLOCK);
        }
#line 1727 "Parser.tab.c"
    break;

  case 69: /* condition_pod: ELSE $@24 LC block RC  */
#line 369 "Parser.y"
          {
            revert_no();
        }
#line 1735 "Parser.tab.c"
    break;

  case 71: /* $@25: %empty  */
#line 374 "Parser.y"
                     {
            create_no(NULL, BREAK_TOKEN);
            errors += check_break(yylineno);
            revert_no();
        }
#line 1745 "Parser.tab.c"
    break;

  case 73: /* $@26: %empty  */
#line 380 "Parser.y"
                       {
            create_no(NULL, RETURN_TOKEN);
        }
#line 1753 "Parser.tab.c"
    break;

  case 74: /* return_ss: RETURN_TOKEN $@26 return_type FINALIZE  */
#line 384 "Parser.y"
                {
            errors+= check_return();
            revert_no();
        }
#line 1762 "Parser.tab.c"
    break;

  case 76: /* return_type: IDENTIFIER  */
#line 390 "Parser.y"
                        {
                create_no((yyvsp[0].id), IDENTIFIER);
                revert_no();  
            }
#line 1771 "Parser.tab.c"
    break;

  case 77: /* return_type: TEXT  */
#line 394 "Parser.y"
                  {
                errors += checkString((yyvsp[0].id), nivel_block_current, function_current);
                create_no((yyvsp[0].id), TEXT);
                revert_no();  
            }
#line 1781 "Parser.tab.c"
    break;

  case 78: /* $@27: %empty  */
#line 399 "Parser.y"
                        {
                create_no((yyvsp[0].id), CALL_FUNCTION);
            }
#line 1789 "Parser.tab.c"
    break;

  case 79: /* return_type: IDENTIFIER $@27 LP parameter_func RP  */
#line 401 "Parser.y"
                                   {
                add_call(current_tree);
                revert_no();            
            }
#line 1798 "Parser.tab.c"
    break;

  case 80: /* $@28: %empty  */
#line 406 "Parser.y"
                         {
            create_no((yyvsp[0].id), CALL_FUNCTION);
        }
#line 1806 "Parser.tab.c"
    break;

  case 81: /* $@29: %empty  */
#line 408 "Parser.y"
                               {
            add_call(current_tree);
            revert_no();            
        }
#line 1815 "Parser.tab.c"
    break;

  case 84: /* $@30: %empty  */
#line 415 "Parser.y"
                       {
                create_no((yyvsp[0].id), CALL_PARAM);
                revert_no();            
            }
#line 1824 "Parser.tab.c"
    break;

  case 86: /* $@31: %empty  */
#line 419 "Parser.y"
                {
                create_no((yyvsp[0].id), CALL_PARAM);
                revert_no();            
            }
#line 1833 "Parser.tab.c"
    break;

  case 88: /* $@32: %empty  */
#line 423 "Parser.y"
                 {
                create_no((yyvsp[0].id), CALL_PARAM);
                revert_no();            
            }
#line 1842 "Parser.tab.c"
    break;

  case 90: /* $@33: %empty  */
#line 427 "Parser.y"
                          {
                 create_no((yyvsp[-1].id), CALL_FUNCTION);
            }
#line 1850 "Parser.tab.c"
    break;

  case 91: /* $@34: %empty  */
#line 429 "Parser.y"
                             {
              add_call(current_tree);
             revert_no(); 
            }
#line 1859 "Parser.tab.c"
    break;


#line 1863 "Parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 437 "Parser.y"


void addFuncs(){
    char** p =  (char **) malloc(sizeof(char *) * 2);
    char c[] = "String";
    p[0] = (char *) malloc (strlen("String")+1);
    strcpy(p[0], c);
    putsymfunc ("println", p, 1, "Void" );
    putsymfunc ("print", p, 1, "Void" );
}

void main( int argc, char *argv[] ){ 
    extern FILE *yyin;
    ++argv; --argc;
    addFuncs();
    yyin = fopen( argv[0], "r" );
    errors = 0;
    yyparse ();
    errors += valid();
    errors += check_returns_f();
    if ( errors == 0 ){ 
        showFuncTable();
        showVarTable();
        showCallTable();
        print_code ();
        printf ( "Sucessfull Parse Completed!!!\n" );
    }else{
        printf ( "Error Parse not Completed\n" );
    }
}

int yyerror ( char *s ) {
    errors++;
    printf("%s - not expected \"%s\" line %d\n", s, yylval, yylineno);
}
