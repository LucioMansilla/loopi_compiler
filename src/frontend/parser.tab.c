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
#line 1 "parser.y"

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ast.h"
#include "errors.h"

int yylex(void);
void yyerror(const char *format,...);
extern  ASTNode* root; 
extern int yylineno; 
int count_params = 0;

#line 85 "parser.tab.c"

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
    INT = 258,                     /* INT  */
    ID = 259,                      /* ID  */
    BOOL = 260,                    /* BOOL  */
    TINT = 261,                    /* TINT  */
    TBOOL = 262,                   /* TBOOL  */
    TVOID = 263,                   /* TVOID  */
    RETURN = 264,                  /* RETURN  */
    IF = 265,                      /* IF  */
    OR = 266,                      /* OR  */
    AND = 267,                     /* AND  */
    PROGRAM = 268,                 /* PROGRAM  */
    EXTERN = 269,                  /* EXTERN  */
    THEN = 270,                    /* THEN  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    EQUALS = 273,                  /* EQUALS  */
    NOT = 274,                     /* NOT  */
    TMENOS = 275,                  /* TMENOS  */
    TMINUS = 276                   /* TMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "parser.y"

    int int_val;
    char *id_val;
    ASTNode *node;
    ValueType type_val;
    struct SymbolTable* st;

#line 161 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_TINT = 6,                       /* TINT  */
  YYSYMBOL_TBOOL = 7,                      /* TBOOL  */
  YYSYMBOL_TVOID = 8,                      /* TVOID  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_PROGRAM = 13,                   /* PROGRAM  */
  YYSYMBOL_EXTERN = 14,                    /* EXTERN  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_EQUALS = 18,                    /* EQUALS  */
  YYSYMBOL_NOT = 19,                       /* NOT  */
  YYSYMBOL_TMENOS = 20,                    /* TMENOS  */
  YYSYMBOL_21_ = 21,                       /* '<'  */
  YYSYMBOL_22_ = 22,                       /* '>'  */
  YYSYMBOL_23_ = 23,                       /* '+'  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_25_ = 25,                       /* '*'  */
  YYSYMBOL_26_ = 26,                       /* '/'  */
  YYSYMBOL_27_ = 27,                       /* '%'  */
  YYSYMBOL_TMINUS = 28,                    /* TMINUS  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* ','  */
  YYSYMBOL_35_ = 35,                       /* '='  */
  YYSYMBOL_36_ = 36,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_init = 38,                      /* init  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_body_program = 41,              /* body_program  */
  YYSYMBOL_methods = 42,                   /* methods  */
  YYSYMBOL_method_decl = 43,               /* method_decl  */
  YYSYMBOL_44_2 = 44,                      /* $@2  */
  YYSYMBOL_45_3 = 45,                      /* $@3  */
  YYSYMBOL_46_4 = 46,                      /* $@4  */
  YYSYMBOL_47_5 = 47,                      /* $@5  */
  YYSYMBOL_block = 48,                     /* block  */
  YYSYMBOL_49_6 = 49,                      /* $@6  */
  YYSYMBOL_param = 50,                     /* param  */
  YYSYMBOL_param_list = 51,                /* param_list  */
  YYSYMBOL_declarations = 52,              /* declarations  */
  YYSYMBOL_var_decl = 53,                  /* var_decl  */
  YYSYMBOL_sentence_list = 54,             /* sentence_list  */
  YYSYMBOL_sentence = 55,                  /* sentence  */
  YYSYMBOL_method_call = 56,               /* method_call  */
  YYSYMBOL_expr_params = 57,               /* expr_params  */
  YYSYMBOL_58_7 = 58,                      /* $@7  */
  YYSYMBOL_expr = 59,                      /* expr  */
  YYSYMBOL_type = 60,                      /* type  */
  YYSYMBOL_valor = 61                      /* valor  */
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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   264

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    36,     2,     2,     2,    27,     2,     2,
      32,    33,    25,    23,    34,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
      21,    35,    22,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    28
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    69,    69,    71,    72,    73,    76,    77,
      80,    80,    91,    91,   101,   101,   109,   109,   118,   118,
     119,   122,   123,   126,   136,   147,   148,   151,   162,   163,
     166,   171,   172,   173,   174,   175,   176,   177,   178,   181,
     193,   201,   201,   204,   208,   209,   216,   221,   225,   229,
     234,   239,   242,   247,   252,   257,   262,   267,   272,   277,
     284,   285,   288,   289
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "ID", "BOOL",
  "TINT", "TBOOL", "TVOID", "RETURN", "IF", "OR", "AND", "PROGRAM",
  "EXTERN", "THEN", "ELSE", "WHILE", "EQUALS", "NOT", "TMENOS", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "TMINUS", "'{'", "'}'", "';'",
  "'('", "')'", "','", "'='", "'!'", "$accept", "init", "program", "$@1",
  "body_program", "methods", "method_decl", "$@2", "$@3", "$@4", "$@5",
  "block", "$@6", "param", "param_list", "declarations", "var_decl",
  "sentence_list", "sentence", "method_call", "expr_params", "$@7", "expr",
  "type", "valor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,     4,    46,   -75,   -75,   -75,     8,   -75,   -75,    44,
      26,   -75,     8,     8,   -75,    51,    27,   -75,   -75,    58,
     -75,   -75,   -22,    -1,    49,    27,    65,    57,   -75,   -25,
      69,   -75,    48,   -75,    54,   -75,    65,    65,    65,   -75,
     167,   -75,   -75,    48,   -75,    15,   -75,    47,    95,   -75,
      25,   -75,    96,   -75,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,   -75,    50,   -75,    71,   -75,   -12,
      62,    56,    60,   -75,   -75,    15,    53,    95,    64,   -75,
      63,   116,   -75,   217,   227,   237,   237,   237,    84,    84,
     -75,   -75,   -75,   -75,   -75,    65,   -75,   184,    65,    65,
      43,    98,   -75,   -75,   -75,   -75,    66,   201,   -75,   133,
     150,    73,    78,    65,   -75,    91,    48,   -75,   -75,    48,
     -75,    99,    48,   -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     1,     0,    60,    61,     0,
       0,     7,     9,     6,    26,     0,     0,     4,     8,     0,
       5,    25,     0,     0,    12,     0,     0,    10,    21,     0,
       0,    14,     0,    62,    45,    63,     0,     0,     0,    51,
       0,    44,    16,     0,    22,     0,    23,     0,    18,    13,
       0,    52,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,    11,     0,    15,     0,
       0,     0,     0,    37,    38,     0,     0,    29,     0,    40,
       0,    41,    48,    49,    50,    56,    54,    55,    46,    57,
      47,    58,    59,    17,    24,     0,    33,     0,     0,     0,
       0,     0,    20,    28,    31,    39,     0,     0,    32,     0,
       0,     0,     0,     0,    30,     0,     0,    19,    42,     0,
      36,    34,     0,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,    12,   -75,   -75,   -75,   -75,
     -75,   -32,   -75,   100,   -75,    55,    -9,   -74,   -75,   -46,
      18,   -75,   -19,   -11,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     6,    10,    11,    12,    43,    32,    47,
      65,    74,    75,    27,    29,    13,    14,    76,    77,    39,
      80,   106,    81,    15,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      49,    19,    78,   103,    21,     7,     8,    40,    44,    45,
      23,    66,    30,    26,     7,     8,     9,    51,    52,    53,
      50,     7,     8,    95,    18,    20,   111,     1,    33,    34,
      35,    78,    28,     4,    67,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    36,     5,    69,    16,     7,
       8,    97,    70,    71,    78,    22,    17,    37,    79,    23,
      72,    38,    25,    31,   101,    33,    34,    35,    33,    34,
      35,    42,    48,    46,    73,    94,   107,    48,    68,   109,
     110,    93,    36,   102,   120,    36,    50,   121,    98,   101,
     123,    21,    99,    96,    37,   104,   105,    37,    38,    69,
     113,    38,   112,   117,    70,    71,   119,    54,    55,    61,
      62,    63,    72,    26,    56,   122,    24,    57,    58,    59,
      60,    61,    62,    63,    48,     0,    73,    54,    55,    82,
     100,   118,     0,     0,    56,     0,     0,    57,    58,    59,
      60,    61,    62,    63,    54,    55,     0,     0,     0,   -43,
       0,    56,     0,     0,    57,    58,    59,    60,    61,    62,
      63,    54,    55,     0,     0,     0,   115,     0,    56,     0,
       0,    57,    58,    59,    60,    61,    62,    63,    54,    55,
       0,     0,     0,   116,     0,    56,     0,     0,    57,    58,
      59,    60,    61,    62,    63,    54,    55,     0,    64,     0,
       0,     0,    56,     0,     0,    57,    58,    59,    60,    61,
      62,    63,    54,    55,     0,   108,     0,     0,     0,    56,
       0,     0,    57,    58,    59,    60,    61,    62,    63,    55,
       0,     0,   114,     0,     0,    56,     0,     0,    57,    58,
      59,    60,    61,    62,    63,    56,     0,     0,    57,    58,
      59,    60,    61,    62,    63,   -44,     0,     0,   -44,   -44,
      59,    60,    61,    62,    63
};

static const yytype_int8 yycheck[] =
{
      32,    12,    48,    77,    13,     6,     7,    26,    33,    34,
      32,    43,    23,    35,     6,     7,     8,    36,    37,    38,
      32,     6,     7,    35,    12,    13,   100,    13,     3,     4,
       5,    77,    33,    29,    45,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    20,     0,     4,     4,     6,
       7,    70,     9,    10,   100,     4,    30,    32,    33,    32,
      17,    36,     4,    14,    75,     3,     4,     5,     3,     4,
       5,    14,    29,     4,    31,     4,    95,    29,    31,    98,
      99,    31,    20,    30,   116,    20,    32,   119,    32,   100,
     122,   100,    32,    31,    32,    31,    33,    32,    36,     4,
      34,    36,     4,    30,     9,    10,    15,    11,    12,    25,
      26,    27,    17,    35,    18,    16,    16,    21,    22,    23,
      24,    25,    26,    27,    29,    -1,    31,    11,    12,    33,
      75,   113,    -1,    -1,    18,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    11,    12,    -1,    -1,    -1,    33,
      -1,    18,    -1,    -1,    21,    22,    23,    24,    25,    26,
      27,    11,    12,    -1,    -1,    -1,    33,    -1,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    11,    12,
      -1,    -1,    -1,    33,    -1,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    11,    12,    -1,    31,    -1,
      -1,    -1,    18,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,    11,    12,    -1,    31,    -1,    -1,    -1,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,    12,
      -1,    -1,    31,    -1,    -1,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    38,    39,    29,     0,    40,     6,     7,     8,
      41,    42,    43,    52,    53,    60,     4,    30,    42,    60,
      42,    53,     4,    32,    50,     4,    35,    50,    33,    51,
      60,    14,    45,     3,     4,     5,    20,    32,    36,    56,
      59,    61,    14,    44,    33,    34,     4,    46,    29,    48,
      32,    59,    59,    59,    11,    12,    18,    21,    22,    23,
      24,    25,    26,    27,    31,    47,    48,    60,    31,     4,
       9,    10,    17,    31,    48,    49,    54,    55,    56,    33,
      57,    59,    33,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    31,     4,    35,    31,    59,    32,    32,
      52,    60,    30,    54,    31,    33,    58,    59,    31,    59,
      59,    54,     4,    34,    31,    33,    33,    30,    57,    15,
      48,    48,    16,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    40,    39,    41,    41,    41,    42,    42,
      44,    43,    45,    43,    46,    43,    47,    43,    49,    48,
      48,    50,    50,    51,    51,    52,    52,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      56,    58,    57,    57,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     5,     2,     1,     1,     2,     1,
       0,     5,     0,     5,     0,     6,     0,     6,     0,     5,
       3,     2,     3,     2,     4,     2,     1,     5,     2,     1,
       4,     2,     3,     2,     6,     8,     5,     1,     1,     4,
       3,     0,     4,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1
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
  case 3: /* $@1: %empty  */
#line 69 "parser.y"
                    { open_level(); }
#line 1306 "parser.tab.c"
    break;

  case 4: /* program: PROGRAM '{' $@1 body_program '}'  */
#line 69 "parser.y"
                                                       {(yyval.node) = (yyvsp[-1].node);}
#line 1312 "parser.tab.c"
    break;

  case 5: /* body_program: declarations methods  */
#line 71 "parser.y"
                                   { (yyval.node) = create_ast_node(NULL,(yyvsp[-1].node),(yyvsp[0].node));}
#line 1318 "parser.tab.c"
    break;

  case 6: /* body_program: declarations  */
#line 72 "parser.y"
                           { (yyval.node) = create_ast_node(NULL,(yyvsp[0].node),NULL);}
#line 1324 "parser.tab.c"
    break;

  case 7: /* body_program: methods  */
#line 73 "parser.y"
                      { (yyval.node) = create_ast_node(NULL,NULL,(yyvsp[0].node));}
#line 1330 "parser.tab.c"
    break;

  case 8: /* methods: method_decl methods  */
#line 76 "parser.y"
                             { (yyval.node) = root;}
#line 1336 "parser.tab.c"
    break;

  case 9: /* methods: method_decl  */
#line 77 "parser.y"
                       { (yyval.node) = (yyvsp[0].node);}
#line 1342 "parser.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 80 "parser.y"
                  {
        if(lookup_in_current_level((yyvsp[-1].id_val)) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", (yyvsp[-1].id_val));
        add_func_to_st((yyvsp[-2].type_val),(yyvsp[-1].id_val),(yyvsp[0].st),yylineno,false);
    }
#line 1352 "parser.tab.c"
    break;

  case 11: /* method_decl: type ID param $@2 block  */
#line 85 "parser.y"
          { 
            close_level();
            Attributes* info = lookup_in_all_levels((yyvsp[-3].id_val));
            ASTNode* temp = create_decl_func(info,(yyvsp[0].node));
            (yyval.node) = temp;
     }
#line 1363 "parser.tab.c"
    break;

  case 12: /* $@3: %empty  */
#line 91 "parser.y"
                     {
        if(lookup_in_current_level((yyvsp[-1].id_val)) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", (yyvsp[-1].id_val));
        add_func_to_st(TYPE_VOID,(yyvsp[-1].id_val),(yyvsp[0].st),yylineno,false);
    }
#line 1373 "parser.tab.c"
    break;

  case 13: /* method_decl: TVOID ID param $@3 block  */
#line 96 "parser.y"
          {  close_level();
            Attributes* info = lookup_in_all_levels((yyvsp[-3].id_val));
            ASTNode* temp = create_decl_func(info,(yyvsp[0].node));
            (yyval.node) = temp; }
#line 1382 "parser.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 101 "parser.y"
                            {
        if(lookup_in_current_level((yyvsp[-2].id_val)) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", (yyvsp[-2].id_val));
        add_func_to_st(TYPE_VOID,(yyvsp[-2].id_val),(yyvsp[-1].st),yylineno,true);
    }
#line 1392 "parser.tab.c"
    break;

  case 15: /* method_decl: TVOID ID param EXTERN $@4 ';'  */
#line 106 "parser.y"
        {
         (yyval.node) = root; }
#line 1399 "parser.tab.c"
    break;

  case 16: /* $@5: %empty  */
#line 109 "parser.y"
                           {
        if(lookup_in_current_level((yyvsp[-2].id_val)) != NULL) 
            yyerror("Try to declare the method: %s but the identifier already declared", (yyvsp[-2].id_val));
        add_func_to_st((yyvsp[-3].type_val),(yyvsp[-2].id_val),(yyvsp[-1].st),yylineno,true);
    }
#line 1409 "parser.tab.c"
    break;

  case 17: /* method_decl: type ID param EXTERN $@5 ';'  */
#line 114 "parser.y"
        { (yyval.node) = root; }
#line 1415 "parser.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 118 "parser.y"
           { open_level(); }
#line 1421 "parser.tab.c"
    break;

  case 19: /* block: '{' $@6 declarations sentence_list '}'  */
#line 118 "parser.y"
                                                            { close_level(); (yyval.node) = (yyvsp[-2].node); }
#line 1427 "parser.tab.c"
    break;

  case 20: /* block: '{' sentence_list '}'  */
#line 119 "parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1433 "parser.tab.c"
    break;

  case 21: /* param: '(' ')'  */
#line 122 "parser.y"
               { (yyval.st) = create_symbol_table(); }
#line 1439 "parser.tab.c"
    break;

  case 22: /* param: '(' param_list ')'  */
#line 123 "parser.y"
                           { (yyval.st) = (yyvsp[-1].st); }
#line 1445 "parser.tab.c"
    break;

  case 23: /* param_list: type ID  */
#line 126 "parser.y"
                    { 
                SymbolTable* table = create_symbol_table();
                if(lookup_symbol(table,(yyvsp[0].id_val)) != NULL) 
                    yyerror("Identifier %s already declared", (yyvsp[0].id_val));
                else {
                    Attributes* info = create_attributes((yyvsp[-1].type_val),0,(yyvsp[0].id_val),yylineno,CLASS_FORMAL_PARAM);
                    insert_symbol(table,info);
                }
                (yyval.st) = table;
           }
#line 1460 "parser.tab.c"
    break;

  case 24: /* param_list: param_list ',' type ID  */
#line 136 "parser.y"
                                  { 
                if(lookup_symbol((yyvsp[-3].st),(yyvsp[0].id_val)) != NULL) 
                    yyerror("Identifier %s already declared", (yyvsp[0].id_val));
                else {
                    Attributes* info = create_attributes((yyvsp[-1].type_val),0,(yyvsp[0].id_val),yylineno,CLASS_FORMAL_PARAM);
                    insert_symbol((yyvsp[-3].st),info);
                }
                (yyval.st) = (yyvsp[-3].st);
           }
#line 1474 "parser.tab.c"
    break;

  case 25: /* declarations: declarations var_decl  */
#line 147 "parser.y"
                                    { (yyval.node) = create_list_decl_node((yyvsp[-1].node),(yyvsp[0].node)); }
#line 1480 "parser.tab.c"
    break;

  case 26: /* declarations: var_decl  */
#line 148 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1486 "parser.tab.c"
    break;

  case 27: /* var_decl: type ID '=' expr ';'  */
#line 151 "parser.y"
                               { 
            Attributes* info = lookup_in_current_level((yyvsp[-3].id_val));
            if (info != NULL) 
                yyerror("Identifier %s already declared", (yyvsp[-3].id_val));
            else {
                ASTNode* id = create_id_node((yyvsp[-3].id_val),yylineno);
                add_symbol_to_current_level(id->info);
                (yyval.node) = create_single_decl_node((yyvsp[-4].type_val),id,(yyvsp[-1].node),yylineno);
            }
     }
#line 1501 "parser.tab.c"
    break;

  case 28: /* sentence_list: sentence sentence_list  */
#line 162 "parser.y"
                                      { (yyval.node) = create_sentence_list_node((yyvsp[-1].node),(yyvsp[0].node));}
#line 1507 "parser.tab.c"
    break;

  case 29: /* sentence_list: sentence  */
#line 163 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1513 "parser.tab.c"
    break;

  case 30: /* sentence: ID '=' expr ';'  */
#line 166 "parser.y"
                          { 
         Attributes* info = lookup_in_all_levels((yyvsp[-3].id_val));
         if (info == NULL) yyerror("Identifier %s not declared", (yyvsp[-3].id_val));
         (yyval.node) = create_assign_node((create_ast_node(info,NULL,NULL)), (yyvsp[-1].node), yylineno);
          }
#line 1523 "parser.tab.c"
    break;

  case 31: /* sentence: method_call ';'  */
#line 171 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1529 "parser.tab.c"
    break;

  case 32: /* sentence: RETURN expr ';'  */
#line 172 "parser.y"
                           { (yyval.node) = create_return_node((yyvsp[-1].node),yylineno); }
#line 1535 "parser.tab.c"
    break;

  case 33: /* sentence: RETURN ';'  */
#line 173 "parser.y"
                      { (yyval.node) = create_return_node(NULL,yylineno); }
#line 1541 "parser.tab.c"
    break;

  case 34: /* sentence: IF '(' expr ')' THEN block  */
#line 174 "parser.y"
                                      { (yyval.node) = (yyvsp[0].node); }
#line 1547 "parser.tab.c"
    break;

  case 35: /* sentence: IF '(' expr ')' THEN block ELSE block  */
#line 175 "parser.y"
                                                 { (yyval.node) = (yyvsp[-2].node); }
#line 1553 "parser.tab.c"
    break;

  case 36: /* sentence: WHILE '(' expr ')' block  */
#line 176 "parser.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1559 "parser.tab.c"
    break;

  case 37: /* sentence: ';'  */
#line 177 "parser.y"
               { (yyval.node) = root; }
#line 1565 "parser.tab.c"
    break;

  case 38: /* sentence: block  */
#line 178 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1571 "parser.tab.c"
    break;

  case 39: /* method_call: ID '(' expr_params ')'  */
#line 181 "parser.y"
                                    {
                Attributes* info = lookup_in_global_level((yyvsp[-3].id_val));
                if(info == NULL || info->class_type != CLASS_DECL_FUNCTION)
                    yyerror("Method %s not declared", (yyvsp[-3].id_val));
                if(info->parameter_list->length  != count_params){
                    printf("CountParams: %d",count_params);
                    printf("\nst_length: %d",info->parameter_list->length);
                    yyerror("Error with the params on: %s", (yyvsp[-3].id_val));
                }
                count_params = 0;
                (yyval.node) = root; 
                }
#line 1588 "parser.tab.c"
    break;

  case 40: /* method_call: ID '(' ')'  */
#line 193 "parser.y"
                        { 
                Attributes* info = lookup_in_global_level((yyvsp[-2].id_val));
                if(info == NULL || info->class_type != CLASS_DECL_FUNCTION)
                    yyerror("Method %s not declared", (yyvsp[-2].id_val));
                (yyval.node) = root; 
            }
#line 1599 "parser.tab.c"
    break;

  case 41: /* $@7: %empty  */
#line 201 "parser.y"
                 {
    count_params++;
}
#line 1607 "parser.tab.c"
    break;

  case 42: /* expr_params: expr $@7 ',' expr_params  */
#line 203 "parser.y"
                  { (yyval.node) = (yyvsp[-3].node); }
#line 1613 "parser.tab.c"
    break;

  case 43: /* expr_params: expr  */
#line 204 "parser.y"
                   { (yyval.node) = (yyvsp[0].node); 
                count_params++;}
#line 1620 "parser.tab.c"
    break;

  case 44: /* expr: valor  */
#line 208 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1626 "parser.tab.c"
    break;

  case 45: /* expr: ID  */
#line 209 "parser.y"
           { 
               Attributes* info = lookup_in_all_levels((yyvsp[0].id_val));
               if (info == NULL)
                    yyerror("Identifier %s not declared", (yyvsp[0].id_val));
               else
                  (yyval.node) = create_ast_node(info,NULL,NULL);  
             }
#line 1638 "parser.tab.c"
    break;

  case 46: /* expr: expr '+' expr  */
#line 217 "parser.y"
            {
               Attributes* attr = create_op_attributes(TYPE_INT, "+", yylineno, CLASS_ADD);
               (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node)); 
            }
#line 1647 "parser.tab.c"
    break;

  case 47: /* expr: expr '*' expr  */
#line 222 "parser.y"
            { Attributes* attr = create_op_attributes(TYPE_INT, "*",yylineno, CLASS_MUL);
              (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));           
            }
#line 1655 "parser.tab.c"
    break;

  case 48: /* expr: '(' expr ')'  */
#line 226 "parser.y"
        {
            (yyval.node) = (yyvsp[-1].node);
        }
#line 1663 "parser.tab.c"
    break;

  case 49: /* expr: expr OR expr  */
#line 230 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"||",yylineno,CLASS_OR);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1672 "parser.tab.c"
    break;

  case 50: /* expr: expr AND expr  */
#line 235 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"&&",yylineno,CLASS_AND);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1681 "parser.tab.c"
    break;

  case 51: /* expr: method_call  */
#line 239 "parser.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1689 "parser.tab.c"
    break;

  case 52: /* expr: TMENOS expr  */
#line 243 "parser.y"
    {
                Attributes* attr = create_op_attributes(TYPE_INT,"-",yylineno,CLASS_MINUS);
                (yyval.node) = create_ast_node(attr, (yyvsp[0].node), NULL);   
    }
#line 1698 "parser.tab.c"
    break;

  case 53: /* expr: '!' expr  */
#line 248 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"!",yylineno,CLASS_NOT);
                (yyval.node) = create_ast_node(attr, (yyvsp[0].node), NULL);
            }
#line 1707 "parser.tab.c"
    break;

  case 54: /* expr: expr '<' expr  */
#line 253 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"<",yylineno,CLASS_LESS);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1716 "parser.tab.c"
    break;

  case 55: /* expr: expr '>' expr  */
#line 258 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,">",yylineno,CLASS_GREATER);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1725 "parser.tab.c"
    break;

  case 56: /* expr: expr EQUALS expr  */
#line 263 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_BOOL,"==",yylineno,CLASS_EQUALS);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1734 "parser.tab.c"
    break;

  case 57: /* expr: expr '-' expr  */
#line 268 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_INT,"-",yylineno,CLASS_SUB);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1743 "parser.tab.c"
    break;

  case 58: /* expr: expr '/' expr  */
#line 273 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_INT,"/",yylineno,CLASS_DIV);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1752 "parser.tab.c"
    break;

  case 59: /* expr: expr '%' expr  */
#line 278 "parser.y"
            {
                Attributes* attr = create_op_attributes(TYPE_INT,"%",yylineno,CLASS_MOD);
                (yyval.node) = create_ast_node(attr, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 1761 "parser.tab.c"
    break;

  case 60: /* type: TINT  */
#line 284 "parser.y"
           { (yyval.type_val) = TYPE_INT; }
#line 1767 "parser.tab.c"
    break;

  case 61: /* type: TBOOL  */
#line 285 "parser.y"
            { (yyval.type_val) = TYPE_BOOL; }
#line 1773 "parser.tab.c"
    break;

  case 62: /* valor: INT  */
#line 288 "parser.y"
           { (yyval.node) = create_int_node((yyvsp[0].int_val),yylineno); }
#line 1779 "parser.tab.c"
    break;

  case 63: /* valor: BOOL  */
#line 289 "parser.y"
             { (yyval.node) = create_bool_node((yyvsp[0].int_val),yylineno); }
#line 1785 "parser.tab.c"
    break;


#line 1789 "parser.tab.c"

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

#line 291 "parser.y"

