/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DT_TOK_EOF = 0,
     DT_TOK_COMMA = 258,
     DT_TOK_ELLIPSIS = 259,
     DT_TOK_ASGN = 260,
     DT_TOK_ADD_EQ = 261,
     DT_TOK_SUB_EQ = 262,
     DT_TOK_MUL_EQ = 263,
     DT_TOK_DIV_EQ = 264,
     DT_TOK_MOD_EQ = 265,
     DT_TOK_AND_EQ = 266,
     DT_TOK_XOR_EQ = 267,
     DT_TOK_OR_EQ = 268,
     DT_TOK_LSH_EQ = 269,
     DT_TOK_RSH_EQ = 270,
     DT_TOK_QUESTION = 271,
     DT_TOK_COLON = 272,
     DT_TOK_LOR = 273,
     DT_TOK_LXOR = 274,
     DT_TOK_LAND = 275,
     DT_TOK_BOR = 276,
     DT_TOK_XOR = 277,
     DT_TOK_BAND = 278,
     DT_TOK_EQU = 279,
     DT_TOK_NEQ = 280,
     DT_TOK_LT = 281,
     DT_TOK_LE = 282,
     DT_TOK_GT = 283,
     DT_TOK_GE = 284,
     DT_TOK_LSH = 285,
     DT_TOK_RSH = 286,
     DT_TOK_ADD = 287,
     DT_TOK_SUB = 288,
     DT_TOK_MUL = 289,
     DT_TOK_DIV = 290,
     DT_TOK_MOD = 291,
     DT_TOK_LNEG = 292,
     DT_TOK_BNEG = 293,
     DT_TOK_ADDADD = 294,
     DT_TOK_SUBSUB = 295,
     DT_TOK_PREINC = 296,
     DT_TOK_POSTINC = 297,
     DT_TOK_PREDEC = 298,
     DT_TOK_POSTDEC = 299,
     DT_TOK_IPOS = 300,
     DT_TOK_INEG = 301,
     DT_TOK_DEREF = 302,
     DT_TOK_ADDROF = 303,
     DT_TOK_OFFSETOF = 304,
     DT_TOK_SIZEOF = 305,
     DT_TOK_STRINGOF = 306,
     DT_TOK_XLATE = 307,
     DT_TOK_LPAR = 308,
     DT_TOK_RPAR = 309,
     DT_TOK_LBRAC = 310,
     DT_TOK_RBRAC = 311,
     DT_TOK_PTR = 312,
     DT_TOK_DOT = 313,
     DT_TOK_STRING = 314,
     DT_TOK_IDENT = 315,
     DT_TOK_PSPEC = 316,
     DT_TOK_AGG = 317,
     DT_TOK_TNAME = 318,
     DT_TOK_INT = 319,
     DT_KEY_AUTO = 320,
     DT_KEY_BREAK = 321,
     DT_KEY_CASE = 322,
     DT_KEY_CHAR = 323,
     DT_KEY_CONST = 324,
     DT_KEY_CONTINUE = 325,
     DT_KEY_COUNTER = 326,
     DT_KEY_DEFAULT = 327,
     DT_KEY_DO = 328,
     DT_KEY_DOUBLE = 329,
     DT_KEY_ELSE = 330,
     DT_KEY_ENUM = 331,
     DT_KEY_EXTERN = 332,
     DT_KEY_FLOAT = 333,
     DT_KEY_FOR = 334,
     DT_KEY_GOTO = 335,
     DT_KEY_IF = 336,
     DT_KEY_IMPORT = 337,
     DT_KEY_INLINE = 338,
     DT_KEY_INT = 339,
     DT_KEY_LONG = 340,
     DT_KEY_PROBE = 341,
     DT_KEY_PROVIDER = 342,
     DT_KEY_REGISTER = 343,
     DT_KEY_RESTRICT = 344,
     DT_KEY_SELF = 345,
     DT_KEY_SHORT = 346,
     DT_KEY_SIGNED = 347,
     DT_KEY_STATIC = 348,
     DT_KEY_STRING = 349,
     DT_KEY_STRUCT = 350,
     DT_KEY_SWITCH = 351,
     DT_KEY_THIS = 352,
     DT_KEY_TYPEDEF = 353,
     DT_KEY_UNION = 354,
     DT_KEY_UNSIGNED = 355,
     DT_KEY_VOID = 356,
     DT_KEY_VOLATILE = 357,
     DT_KEY_WHILE = 358,
     DT_KEY_XLATOR = 359,
     DT_TOK_EPRED = 360,
     DT_CTX_DEXPR = 361,
     DT_CTX_DPROG = 362,
     DT_CTX_DTYPE = 363
   };
#endif
/* Tokens.  */
#define DT_TOK_EOF 0
#define DT_TOK_COMMA 258
#define DT_TOK_ELLIPSIS 259
#define DT_TOK_ASGN 260
#define DT_TOK_ADD_EQ 261
#define DT_TOK_SUB_EQ 262
#define DT_TOK_MUL_EQ 263
#define DT_TOK_DIV_EQ 264
#define DT_TOK_MOD_EQ 265
#define DT_TOK_AND_EQ 266
#define DT_TOK_XOR_EQ 267
#define DT_TOK_OR_EQ 268
#define DT_TOK_LSH_EQ 269
#define DT_TOK_RSH_EQ 270
#define DT_TOK_QUESTION 271
#define DT_TOK_COLON 272
#define DT_TOK_LOR 273
#define DT_TOK_LXOR 274
#define DT_TOK_LAND 275
#define DT_TOK_BOR 276
#define DT_TOK_XOR 277
#define DT_TOK_BAND 278
#define DT_TOK_EQU 279
#define DT_TOK_NEQ 280
#define DT_TOK_LT 281
#define DT_TOK_LE 282
#define DT_TOK_GT 283
#define DT_TOK_GE 284
#define DT_TOK_LSH 285
#define DT_TOK_RSH 286
#define DT_TOK_ADD 287
#define DT_TOK_SUB 288
#define DT_TOK_MUL 289
#define DT_TOK_DIV 290
#define DT_TOK_MOD 291
#define DT_TOK_LNEG 292
#define DT_TOK_BNEG 293
#define DT_TOK_ADDADD 294
#define DT_TOK_SUBSUB 295
#define DT_TOK_PREINC 296
#define DT_TOK_POSTINC 297
#define DT_TOK_PREDEC 298
#define DT_TOK_POSTDEC 299
#define DT_TOK_IPOS 300
#define DT_TOK_INEG 301
#define DT_TOK_DEREF 302
#define DT_TOK_ADDROF 303
#define DT_TOK_OFFSETOF 304
#define DT_TOK_SIZEOF 305
#define DT_TOK_STRINGOF 306
#define DT_TOK_XLATE 307
#define DT_TOK_LPAR 308
#define DT_TOK_RPAR 309
#define DT_TOK_LBRAC 310
#define DT_TOK_RBRAC 311
#define DT_TOK_PTR 312
#define DT_TOK_DOT 313
#define DT_TOK_STRING 314
#define DT_TOK_IDENT 315
#define DT_TOK_PSPEC 316
#define DT_TOK_AGG 317
#define DT_TOK_TNAME 318
#define DT_TOK_INT 319
#define DT_KEY_AUTO 320
#define DT_KEY_BREAK 321
#define DT_KEY_CASE 322
#define DT_KEY_CHAR 323
#define DT_KEY_CONST 324
#define DT_KEY_CONTINUE 325
#define DT_KEY_COUNTER 326
#define DT_KEY_DEFAULT 327
#define DT_KEY_DO 328
#define DT_KEY_DOUBLE 329
#define DT_KEY_ELSE 330
#define DT_KEY_ENUM 331
#define DT_KEY_EXTERN 332
#define DT_KEY_FLOAT 333
#define DT_KEY_FOR 334
#define DT_KEY_GOTO 335
#define DT_KEY_IF 336
#define DT_KEY_IMPORT 337
#define DT_KEY_INLINE 338
#define DT_KEY_INT 339
#define DT_KEY_LONG 340
#define DT_KEY_PROBE 341
#define DT_KEY_PROVIDER 342
#define DT_KEY_REGISTER 343
#define DT_KEY_RESTRICT 344
#define DT_KEY_SELF 345
#define DT_KEY_SHORT 346
#define DT_KEY_SIGNED 347
#define DT_KEY_STATIC 348
#define DT_KEY_STRING 349
#define DT_KEY_STRUCT 350
#define DT_KEY_SWITCH 351
#define DT_KEY_THIS 352
#define DT_KEY_TYPEDEF 353
#define DT_KEY_UNION 354
#define DT_KEY_UNSIGNED 355
#define DT_KEY_VOID 356
#define DT_KEY_VOLATILE 357
#define DT_KEY_WHILE 358
#define DT_KEY_XLATOR 359
#define DT_TOK_EPRED 360
#define DT_CTX_DEXPR 361
#define DT_CTX_DPROG 362
#define DT_CTX_DTYPE 363




/* Copy the first part of user declarations.  */
#line 1 "libdtrace/dt_grammar.y"

/*
 * Oracle Linux DTrace.
 * Copyright (c) 2006, 2025, Oracle and/or its affiliates. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 */

#include <dt_impl.h>
#include <string.h>

#define	OP1(op, c)	dt_node_op1(op, c)
#define	OP2(op, l, r)	dt_node_op2(op, l, r)
#define	OP3(x, y, z)	dt_node_op3(x, y, z)
#define	LINK(l, r)	dt_node_link(l, r)
#define	DUP(s)		strdup(s)

int yylex (void);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 22 "libdtrace/dt_grammar.y"
{
	dt_node_t *l_node;
	dt_decl_t *l_decl;
	char *l_str;
	uintmax_t l_int;
	int l_tok;
}
/* Line 193 of yacc.c.  */
#line 343 "/tmp/dt_grammar.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 356 "/tmp/dt_grammar.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  99
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   819

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  85
/* YYNRULES -- Number of rules.  */
#define YYNRULES  237
/* YYNRULES -- Number of states.  */
#define YYNSTATES  359

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   363

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   109,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   110,     2,   111,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    17,    19,    22,
      24,    27,    29,    32,    34,    36,    38,    40,    42,    43,
      51,    52,    55,    57,    68,    78,    80,    83,    88,    95,
     101,   103,   106,   113,   118,   120,   125,   130,   138,   140,
     142,   146,   148,   150,   152,   156,   157,   159,   161,   165,
     167,   169,   171,   173,   175,   177,   181,   183,   188,   192,
     197,   201,   205,   208,   211,   218,   226,   228,   231,   234,
     237,   240,   245,   248,   250,   252,   254,   256,   258,   260,
     262,   267,   269,   273,   277,   281,   283,   287,   291,   293,
     297,   301,   303,   307,   311,   315,   319,   321,   325,   329,
     331,   335,   337,   341,   343,   347,   349,   353,   355,   359,
     361,   365,   367,   369,   375,   377,   381,   383,   385,   387,
     389,   391,   393,   395,   397,   399,   401,   403,   405,   409,
     412,   416,   418,   421,   423,   426,   428,   431,   433,   436,
     438,   441,   443,   446,   448,   450,   452,   454,   456,   458,
     460,   462,   464,   466,   468,   470,   472,   474,   476,   478,
     480,   482,   484,   486,   488,   490,   492,   494,   498,   501,
     504,   508,   510,   512,   514,   517,   519,   523,   525,   529,
     531,   534,   536,   539,   541,   545,   547,   550,   554,   558,
     561,   564,   568,   570,   574,   577,   579,   583,   585,   588,
     590,   594,   597,   600,   602,   604,   607,   610,   614,   616,
     619,   621,   623,   627,   629,   633,   635,   638,   641,   643,
     646,   648,   650,   653,   657,   660,   662,   665,   667,   668,
     669,   675,   676,   678,   680,   681,   686,   687
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     113,     0,    -1,   114,     0,    -1,   115,     0,    -1,   116,
       0,    -1,   106,    -1,   106,   157,    -1,   107,    -1,   107,
     117,    -1,   108,    -1,   108,   187,    -1,   118,    -1,   117,
     118,    -1,   119,    -1,   124,    -1,   127,    -1,   130,    -1,
     158,    -1,    -1,    83,   159,   179,   120,     5,   155,   109,
      -1,    -1,   122,   187,    -1,    28,    -1,   104,   187,    26,
     121,    60,   123,   110,   125,   111,   109,    -1,   104,   187,
      26,   121,    60,   123,   110,   111,   109,    -1,   126,    -1,
     125,   126,    -1,    60,     5,   155,   109,    -1,    87,    60,
     110,   128,   111,   109,    -1,    87,    60,   110,   111,   109,
      -1,   129,    -1,   128,   129,    -1,    86,    60,   194,    17,
     194,   109,    -1,    86,    60,   194,   109,    -1,   131,    -1,
     131,   110,   134,   111,    -1,   131,    35,   157,   105,    -1,
     131,    35,   157,   105,   110,   134,   111,    -1,   132,    -1,
     133,    -1,   132,     3,   133,    -1,    61,    -1,    64,    -1,
     135,    -1,   134,   109,   135,    -1,    -1,   157,    -1,   155,
      -1,   136,     3,   155,    -1,    60,    -1,    62,    -1,    64,
      -1,    59,    -1,    90,    -1,    97,    -1,    53,   157,    54,
      -1,   137,    -1,   138,    55,   136,    56,    -1,   138,    53,
      54,    -1,   138,    53,   136,    54,    -1,   138,    58,    60,
      -1,   138,    57,    60,    -1,   138,    39,    -1,   138,    40,
      -1,    49,    53,   187,     3,    60,    54,    -1,    52,    26,
     187,    28,    53,   157,    54,    -1,   138,    -1,    39,   139,
      -1,    40,   139,    -1,   140,   141,    -1,    50,   139,    -1,
      50,    53,   187,    54,    -1,    51,   139,    -1,    23,    -1,
      34,    -1,    32,    -1,    33,    -1,    38,    -1,    37,    -1,
     139,    -1,    53,   187,    54,   141,    -1,   141,    -1,   142,
      34,   141,    -1,   142,    35,   141,    -1,   142,    36,   141,
      -1,   142,    -1,   143,    32,   142,    -1,   143,    33,   142,
      -1,   143,    -1,   144,    30,   143,    -1,   144,    31,   143,
      -1,   144,    -1,   145,    26,   144,    -1,   145,    28,   144,
      -1,   145,    27,   144,    -1,   145,    29,   144,    -1,   145,
      -1,   146,    24,   145,    -1,   146,    25,   145,    -1,   146,
      -1,   147,    23,   146,    -1,   147,    -1,   148,    22,   147,
      -1,   148,    -1,   149,    21,   148,    -1,   149,    -1,   150,
      20,   149,    -1,   150,    -1,   151,    19,   150,    -1,   151,
      -1,   152,    18,   151,    -1,   154,    -1,   152,    -1,   152,
      16,   157,    17,   154,    -1,   154,    -1,   139,   156,   155,
      -1,     5,    -1,     8,    -1,     9,    -1,    10,    -1,     6,
      -1,     7,    -1,    14,    -1,    15,    -1,    11,    -1,    12,
      -1,    13,    -1,   155,    -1,   157,     3,   155,    -1,   159,
     109,    -1,   159,   169,   109,    -1,   162,    -1,   162,   159,
      -1,   163,    -1,   163,   159,    -1,   164,    -1,   164,   159,
      -1,   161,    -1,   161,   159,    -1,   163,    -1,   163,   159,
      -1,   164,    -1,   164,   159,    -1,    65,    -1,    88,    -1,
      93,    -1,    77,    -1,    98,    -1,   161,    -1,    90,    -1,
      97,    -1,   101,    -1,    68,    -1,    91,    -1,    84,    -1,
      85,    -1,    78,    -1,    74,    -1,    92,    -1,   100,    -1,
      94,    -1,    63,    -1,   165,    -1,   175,    -1,    69,    -1,
      89,    -1,   102,    -1,   166,   168,   111,    -1,   167,    63,
      -1,   167,   110,    -1,   167,    63,   110,    -1,    95,    -1,
      99,    -1,   171,    -1,   168,   171,    -1,   170,    -1,   169,
       3,   170,    -1,   179,    -1,   172,   173,   109,    -1,   163,
      -1,   163,   172,    -1,   164,    -1,   164,   172,    -1,   174,
      -1,   173,     3,   174,    -1,   179,    -1,    17,   153,    -1,
     179,    17,   153,    -1,   176,   177,   111,    -1,    76,    63,
      -1,    76,   110,    -1,    76,    63,   110,    -1,   178,    -1,
     178,     3,   177,    -1,   178,     3,    -1,    60,    -1,    60,
       5,   157,    -1,   180,    -1,   182,   180,    -1,    60,    -1,
     181,   179,    54,    -1,   180,   190,    -1,   180,   194,    -1,
      53,    -1,    34,    -1,    34,   183,    -1,    34,   182,    -1,
      34,   183,   182,    -1,   164,    -1,   183,   164,    -1,   185,
      -1,     4,    -1,   185,     3,     4,    -1,   186,    -1,   185,
       3,   186,    -1,   160,    -1,   160,   179,    -1,   160,   188,
      -1,   172,    -1,   172,   188,    -1,   182,    -1,   189,    -1,
     182,   189,    -1,   181,   188,    54,    -1,   189,   190,    -1,
     190,    -1,   189,   194,    -1,   194,    -1,    -1,    -1,   191,
      55,   192,   193,    56,    -1,    -1,   153,    -1,   184,    -1,
      -1,    53,   195,   196,    54,    -1,    -1,   184,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   193,   194,   197,   198,   201,   202,   205,
     206,   210,   211,   215,   216,   217,   218,   219,   224,   223,
     238,   238,   243,   247,   252,   259,   260,   264,   270,   273,
     279,   280,   284,   287,   294,   310,   313,   317,   324,   328,
     329,   335,   336,   339,   340,   343,   344,   348,   349,   355,
     356,   357,   358,   359,   360,   361,   365,   366,   370,   373,
     377,   380,   383,   386,   389,   393,   400,   401,   402,   403,
     404,   405,   408,   413,   414,   415,   416,   417,   418,   422,
     423,   429,   430,   433,   436,   442,   443,   446,   452,   453,
     456,   462,   463,   466,   469,   472,   478,   479,   482,   488,
     489,   495,   496,   502,   503,   509,   510,   516,   517,   523,
     524,   529,   533,   534,   539,   540,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   559,   560,   565,
     570,   578,   579,   580,   581,   582,   583,   587,   588,   589,
     590,   591,   592,   596,   597,   598,   599,   600,   604,   605,
     606,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     618,   621,   622,   623,   626,   627,   628,   632,   635,   639,
     640,   644,   645,   649,   650,   654,   655,   661,   668,   674,
     675,   676,   677,   681,   682,   686,   687,   688,   694,   695,
     699,   700,   704,   705,   706,   709,   710,   715,   716,   720,
     721,   722,   723,   726,   729,   730,   731,   732,   736,   737,
     741,   742,   743,   748,   749,   755,   758,   761,   766,   769,
     775,   776,   777,   781,   782,   783,   784,   785,   788,   789,
     788,   799,   800,   801,   804,   804,   812,   813
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "DT_TOK_EOF", "error", "$undefined", "DT_TOK_COMMA", "DT_TOK_ELLIPSIS",
  "DT_TOK_ASGN", "DT_TOK_ADD_EQ", "DT_TOK_SUB_EQ", "DT_TOK_MUL_EQ",
  "DT_TOK_DIV_EQ", "DT_TOK_MOD_EQ", "DT_TOK_AND_EQ", "DT_TOK_XOR_EQ",
  "DT_TOK_OR_EQ", "DT_TOK_LSH_EQ", "DT_TOK_RSH_EQ", "DT_TOK_QUESTION",
  "DT_TOK_COLON", "DT_TOK_LOR", "DT_TOK_LXOR", "DT_TOK_LAND", "DT_TOK_BOR",
  "DT_TOK_XOR", "DT_TOK_BAND", "DT_TOK_EQU", "DT_TOK_NEQ", "DT_TOK_LT",
  "DT_TOK_LE", "DT_TOK_GT", "DT_TOK_GE", "DT_TOK_LSH", "DT_TOK_RSH",
  "DT_TOK_ADD", "DT_TOK_SUB", "DT_TOK_MUL", "DT_TOK_DIV", "DT_TOK_MOD",
  "DT_TOK_LNEG", "DT_TOK_BNEG", "DT_TOK_ADDADD", "DT_TOK_SUBSUB",
  "DT_TOK_PREINC", "DT_TOK_POSTINC", "DT_TOK_PREDEC", "DT_TOK_POSTDEC",
  "DT_TOK_IPOS", "DT_TOK_INEG", "DT_TOK_DEREF", "DT_TOK_ADDROF",
  "DT_TOK_OFFSETOF", "DT_TOK_SIZEOF", "DT_TOK_STRINGOF", "DT_TOK_XLATE",
  "DT_TOK_LPAR", "DT_TOK_RPAR", "DT_TOK_LBRAC", "DT_TOK_RBRAC",
  "DT_TOK_PTR", "DT_TOK_DOT", "DT_TOK_STRING", "DT_TOK_IDENT",
  "DT_TOK_PSPEC", "DT_TOK_AGG", "DT_TOK_TNAME", "DT_TOK_INT",
  "DT_KEY_AUTO", "DT_KEY_BREAK", "DT_KEY_CASE", "DT_KEY_CHAR",
  "DT_KEY_CONST", "DT_KEY_CONTINUE", "DT_KEY_COUNTER", "DT_KEY_DEFAULT",
  "DT_KEY_DO", "DT_KEY_DOUBLE", "DT_KEY_ELSE", "DT_KEY_ENUM",
  "DT_KEY_EXTERN", "DT_KEY_FLOAT", "DT_KEY_FOR", "DT_KEY_GOTO",
  "DT_KEY_IF", "DT_KEY_IMPORT", "DT_KEY_INLINE", "DT_KEY_INT",
  "DT_KEY_LONG", "DT_KEY_PROBE", "DT_KEY_PROVIDER", "DT_KEY_REGISTER",
  "DT_KEY_RESTRICT", "DT_KEY_SELF", "DT_KEY_SHORT", "DT_KEY_SIGNED",
  "DT_KEY_STATIC", "DT_KEY_STRING", "DT_KEY_STRUCT", "DT_KEY_SWITCH",
  "DT_KEY_THIS", "DT_KEY_TYPEDEF", "DT_KEY_UNION", "DT_KEY_UNSIGNED",
  "DT_KEY_VOID", "DT_KEY_VOLATILE", "DT_KEY_WHILE", "DT_KEY_XLATOR",
  "DT_TOK_EPRED", "DT_CTX_DEXPR", "DT_CTX_DPROG", "DT_CTX_DTYPE", "';'",
  "'{'", "'}'", "$accept", "dtrace_program", "d_expression", "d_program",
  "d_type", "translation_unit", "external_declaration",
  "inline_definition", "@1", "translator_input_type", "@2",
  "translator_close_paren", "translator_definition",
  "translator_member_list", "translator_member", "provider_definition",
  "provider_probe_list", "provider_probe", "probe_definition",
  "probe_specifiers", "probe_specifier_list", "probe_specifier",
  "statement_list", "statement", "argument_expression_list",
  "primary_expression", "postfix_expression", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_xor_expression", "logical_or_expression", "constant_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "declaration", "declaration_specifiers",
  "parameter_declaration_specifiers", "storage_class_specifier",
  "d_storage_class_specifier", "type_specifier", "type_qualifier",
  "struct_or_union_specifier", "struct_or_union_definition",
  "struct_or_union", "struct_declaration_list", "init_declarator_list",
  "init_declarator", "struct_declaration", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enum_definition", "enumerator_list", "enumerator", "declarator",
  "direct_declarator", "lparen", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "type_name", "abstract_declarator", "direct_abstract_declarator",
  "array", "@3", "@4", "array_parameters", "function", "@5",
  "function_parameters", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,    59,
     123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   118,   118,   118,   120,   119,
     122,   121,   123,   124,   124,   125,   125,   126,   127,   127,
     128,   128,   129,   129,   130,   130,   130,   130,   131,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   137,
     137,   137,   137,   137,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   141,
     141,   142,   142,   142,   142,   143,   143,   143,   144,   144,
     144,   145,   145,   145,   145,   145,   146,   146,   146,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   151,   152,
     152,   153,   154,   154,   155,   155,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   157,   157,   158,
     158,   159,   159,   159,   159,   159,   159,   160,   160,   160,
     160,   160,   160,   161,   161,   161,   161,   161,   162,   162,
     162,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   164,   164,   164,   165,   165,   166,
     166,   167,   167,   168,   168,   169,   169,   170,   171,   172,
     172,   172,   172,   173,   173,   174,   174,   174,   175,   175,
     176,   176,   177,   177,   177,   178,   178,   179,   179,   180,
     180,   180,   180,   181,   182,   182,   182,   182,   183,   183,
     184,   184,   184,   185,   185,   186,   186,   186,   187,   187,
     188,   188,   188,   189,   189,   189,   189,   189,   191,   192,
     190,   193,   193,   193,   195,   194,   196,   196
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     0,     7,
       0,     2,     1,    10,     9,     1,     2,     4,     6,     5,
       1,     2,     6,     4,     1,     4,     4,     7,     1,     1,
       3,     1,     1,     1,     3,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     6,     7,     1,     2,     2,     2,
       2,     4,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       3,     1,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     2,
       3,     1,     1,     1,     2,     1,     3,     1,     3,     1,
       2,     1,     2,     1,     3,     1,     2,     3,     3,     2,
       2,     3,     1,     3,     2,     1,     3,     1,     2,     1,
       3,     2,     2,     1,     1,     2,     2,     3,     1,     2,
       1,     1,     3,     1,     3,     1,     2,     2,     1,     2,
       1,     1,     2,     3,     2,     1,     2,     1,     0,     0,
       5,     0,     1,     1,     0,     4,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     7,     9,     0,     0,     0,     0,    73,    75,
      76,    74,    78,    77,     0,     0,     0,     0,     0,     0,
       0,    52,    49,    50,    51,    53,    54,    56,    66,    79,
       0,    81,    85,    88,    91,    96,    99,   101,   103,   105,
     107,   109,   112,   114,   127,     6,    41,   161,    42,   143,
     152,   164,   157,     0,   146,   156,     0,   154,   155,     0,
     144,   165,   149,   153,   158,   145,   160,   171,   150,   147,
     172,   159,   151,   166,     0,     8,    11,    13,    14,    15,
      16,    34,    38,    39,    17,     0,   148,   131,   133,   135,
     162,     0,     0,   163,     0,   179,   181,   218,    10,     1,
       2,     3,     4,     0,    67,    68,     0,     0,    70,    72,
       0,     0,     0,    62,    63,     0,     0,     0,     0,   116,
     120,   121,   117,   118,   119,   124,   125,   126,   122,   123,
       0,    79,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   189,   190,     0,     0,     0,    12,
       0,    45,     0,   204,   203,   199,   129,     0,   175,   177,
     197,     0,     0,   132,   134,   136,     0,   173,     0,   168,
     169,   195,     0,   192,   180,   182,   234,   228,   220,   219,
     221,   225,     0,   227,     0,     0,     0,    55,     0,    58,
       0,    47,     0,    61,    60,   115,    82,    83,    84,    86,
      87,    89,    90,    92,    94,    93,    95,    97,    98,   100,
     102,   104,   106,   108,     0,   110,   128,   191,    18,     0,
      20,     0,     0,    43,    46,    40,   208,   206,   205,     0,
     130,   234,   201,   202,     0,   198,   167,   174,     0,     0,
     183,   185,   170,     0,   188,   194,   236,     0,   222,   224,
     226,   229,     0,    71,     0,    80,     0,    59,    57,     0,
       0,     0,     0,     0,    30,     0,     0,    36,    45,    35,
     209,   207,   176,   200,   186,   111,     0,   178,     0,   196,
     193,   211,   215,   137,   139,   141,   237,   210,   213,     0,
     223,   231,     0,     0,    48,   113,     0,     0,    29,     0,
      31,     0,    21,    45,    44,   184,   187,   216,   228,   220,
     217,   138,   140,   142,     0,   235,   232,   233,     0,    64,
       0,     0,     0,    28,    22,     0,     0,   212,   214,   230,
      65,    19,     0,    33,     0,    37,     0,     0,     0,     0,
      25,    32,     0,    24,     0,    26,     0,    23,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    75,    76,    77,   270,   275,
     276,   335,    78,   349,   350,    79,   273,   274,    80,    81,
      82,    83,   232,   233,   200,    27,    28,   131,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,   284,    43,    44,   130,   111,    84,    85,   292,    86,
      87,    95,    96,    90,    91,    92,   176,   167,   168,   177,
      97,   249,   250,    93,    94,   182,   183,   169,   170,   171,
     172,   238,   296,   297,   298,    98,   257,   190,   191,   192,
     301,   328,   193,   256,   299
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -236
static const yytype_int16 yypact[] =
{
     -35,   558,   637,   717,    46,    51,    63,    83,  -236,  -236,
    -236,  -236,  -236,  -236,   592,   592,    77,   626,   592,   115,
     451,  -236,  -236,  -236,  -236,  -236,  -236,  -236,   178,   261,
     558,  -236,   173,   140,   157,   149,   219,   141,   146,   170,
     182,   185,   122,  -236,  -236,   208,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,   -36,  -236,  -236,   677,  -236,  -236,   154,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,   717,   637,  -236,  -236,  -236,  -236,
    -236,    -5,   216,  -236,  -236,    -6,  -236,   677,   677,   677,
    -236,   717,     2,  -236,   166,   717,   717,    15,  -236,  -236,
    -236,  -236,  -236,   558,  -236,  -236,   717,   451,  -236,  -236,
     717,    30,   174,  -236,  -236,   524,   558,   177,   179,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
     558,  -236,  -236,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   124,  -236,     4,   143,   225,  -236,
     558,   558,    70,    11,  -236,  -236,  -236,    17,  -236,  -236,
     130,     4,    26,  -236,  -236,  -236,   121,  -236,    93,   144,
    -236,   250,   153,   254,  -236,  -236,    82,    24,   139,  -236,
     130,  -236,   205,  -236,   275,   226,   251,  -236,   558,  -236,
      47,  -236,    20,  -236,  -236,  -236,  -236,  -236,  -236,   173,
     173,   140,   140,   157,   157,   157,   157,   149,   149,   219,
     141,   146,   170,   182,    52,   185,  -236,  -236,  -236,   -49,
    -236,    12,    89,  -236,   208,  -236,  -236,  -236,    11,     4,
    -236,  -236,  -236,  -236,   227,   130,  -236,  -236,   558,    19,
    -236,   265,  -236,   558,  -236,   166,   336,   230,   130,  -236,
    -236,  -236,   228,  -236,   232,  -236,   558,  -236,  -236,   558,
     281,   229,   181,   -44,  -236,   231,   717,   189,   558,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,    93,  -236,   558,  -236,
    -236,  -236,   114,   677,   677,   677,  -236,   284,  -236,   238,
    -236,   296,   249,   558,  -236,  -236,   558,   253,  -236,   198,
    -236,   282,  -236,   558,  -236,  -236,  -236,  -236,   102,    94,
    -236,  -236,  -236,  -236,   378,  -236,  -236,  -236,   255,  -236,
      57,   200,     9,  -236,  -236,   203,   116,  -236,  -236,  -236,
    -236,  -236,   253,  -236,    21,  -236,   206,   309,   207,    22,
    -236,  -236,   558,  -236,   211,  -236,   212,  -236,  -236
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -236,  -236,  -236,  -236,  -236,  -236,   242,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,   -27,  -236,  -236,    50,  -236,  -236,
    -236,   163,    13,    53,   221,  -236,  -236,    -1,  -236,   -12,
     109,   110,    39,   117,   186,   191,   193,   190,   192,   201,
    -236,  -235,  -144,  -105,  -236,     5,  -236,   -53,  -236,  -216,
    -236,     3,     0,  -236,  -236,  -236,  -236,  -236,   104,   168,
     -52,  -236,    64,  -236,  -236,    97,  -236,  -147,  -168,   -89,
     -68,  -236,    56,  -236,    38,   -13,   -96,  -176,  -138,  -236,
    -236,  -236,  -149,  -236,  -236
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -229
static const yytype_int16 yytable[] =
{
      29,   189,    89,   156,   245,    88,    45,   112,   187,   228,
     201,   201,   258,   104,   105,   153,   108,   109,   132,    29,
     239,   243,   286,   266,   244,   205,   342,   154,   163,   188,
     160,   251,   242,   153,   173,   174,   175,   271,   163,   178,
     293,   260,   271,   184,   185,   163,    99,   164,   226,   163,
     266,   100,   259,   316,   165,   153,    89,   164,   163,    88,
     153,   158,   272,   101,   165,   179,   326,   309,   186,   269,
    -228,     1,     2,     3,   155,    89,   268,   186,    88,   164,
      51,   347,   347,   102,   197,   293,   165,    89,    89,    89,
      88,    88,    88,   194,   195,   237,   243,   196,   187,   187,
      61,   267,    29,   166,   285,   161,    29,   242,   293,   260,
     248,   340,   180,    73,    29,    29,  -203,   277,   343,   188,
     259,   206,   207,   208,   178,   305,   240,   163,   287,    29,
     106,    46,   348,   354,    48,  -203,   163,  -203,   151,   251,
     152,   110,  -203,   258,   285,   317,   164,   186,   163,  -228,
      29,   245,    29,   165,   165,   186,   224,   285,   332,    29,
      29,   304,   165,   236,   146,   231,   234,   186,   147,  -228,
     281,   244,   136,   137,   165,   140,   141,   142,   143,   213,
     214,   215,   216,   241,    47,  -228,   265,   138,   139,    50,
      51,   148,   186,   346,  -228,    52,   320,    53,   278,    55,
     279,   331,   149,   318,   150,    57,    58,   133,   134,   135,
      61,   153,    63,    64,   157,    66,    67,   113,   114,   162,
      70,    71,    72,    73,   319,   278,   181,   345,   198,   318,
     318,   115,   246,   116,   227,   117,   118,   203,   280,   204,
     321,   322,   323,   144,   145,   209,   210,   356,   211,   212,
     319,   230,    29,   229,   252,   253,   295,   255,   289,   294,
     261,   217,   218,   312,   254,    29,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    29,   262,   264,
     263,   283,   288,   234,   300,   303,   306,   324,   302,   307,
     308,   311,   325,    89,    89,    89,    88,    88,    88,   313,
     291,   295,    29,   329,   294,    29,   241,   333,   330,   341,
     334,   339,    29,   344,   352,   351,   353,   159,   234,     8,
     357,   358,   355,   310,   295,   235,   336,   294,     9,    10,
      11,   314,   219,    12,    13,    14,    15,   202,   220,   222,
     291,   221,   223,   282,   247,    16,    17,    18,    19,    20,
     315,    29,   290,   225,     0,    21,    22,   327,    23,    47,
      24,    49,   338,     0,    50,    51,     0,     0,     0,     0,
      52,     0,    53,    54,    55,     0,     0,     0,     0,     0,
      57,    58,   337,     0,    60,    61,    25,    63,    64,    65,
      66,    67,     0,    26,    69,    70,    71,    72,    73,    47,
       0,    49,     0,     0,    50,    51,     0,     0,     0,     0,
      52,     0,    53,    54,    55,     0,     0,     0,     0,     0,
      57,    58,     0,     0,    60,    61,     0,    63,    64,    65,
      66,    67,     0,     0,    69,    70,    71,    72,    73,     0,
       0,    47,     0,    49,     0,     0,    50,    51,     0,     0,
       0,     0,    52,     0,    53,    54,    55,     0,     0,     0,
       0,     0,    57,    58,     0,     0,    60,    61,     0,    63,
      64,    65,    66,    67,     8,     0,    69,    70,    71,    72,
      73,     0,     0,     9,    10,    11,     0,     0,    12,    13,
      14,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
      21,    22,     0,    23,    47,    24,     0,     0,     0,    50,
      51,     0,     0,     0,     0,    52,     0,    53,     0,    55,
       0,     0,     0,     0,     0,    57,    58,     0,     0,     0,
      61,    25,    63,    64,     0,    66,    67,     8,    26,     0,
      70,    71,    72,    73,     0,     0,     9,    10,    11,     0,
       0,    12,    13,    14,    15,     0,     0,     0,     0,     0,
       0,     0,     0,    16,    17,    18,    19,    20,   199,     0,
       0,     8,     0,    21,    22,     0,    23,     0,    24,     0,
       9,    10,    11,     0,     0,    12,    13,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,     0,     0,    25,     8,     0,    21,    22,     0,
      23,    26,    24,     0,     9,    10,    11,     0,     0,    12,
      13,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,    16,    17,    18,    19,   103,     0,     0,    25,     8,
       0,    21,    22,     0,    23,    26,    24,     0,     9,    10,
      11,     0,     0,    12,    13,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    17,    18,    19,   107,
       0,     0,    25,     0,     0,    21,    22,     0,    23,    26,
      24,     0,     0,     0,     0,     0,     0,     0,    46,     0,
      47,    48,    49,     0,     0,    50,    51,     0,     0,     0,
       0,    52,     0,    53,    54,    55,    25,     0,     0,     0,
      56,    57,    58,    26,    59,    60,    61,    62,    63,    64,
      65,    66,    67,     0,    68,    69,    70,    71,    72,    73,
      47,    74,    49,     0,     0,    50,    51,     0,     0,     0,
       0,    52,     0,    53,    54,    55,     0,     0,     0,     0,
       0,    57,    58,     0,     0,    60,    61,    62,    63,    64,
      65,    66,    67,     0,    68,    69,    70,    71,    72,    73,
      47,     0,     0,     0,     0,    50,    51,     0,     0,     0,
       0,    52,     0,    53,     0,    55,     0,     0,     0,     0,
       0,    57,    58,     0,     0,     0,    61,     0,    63,    64,
       0,    66,    67,     0,     0,     0,    70,    71,    72,    73
};

static const yytype_int16 yycheck[] =
{
       1,    97,     2,    56,   172,     2,     1,    20,    97,   156,
     115,   116,   188,    14,    15,     3,    17,    18,    30,    20,
       3,   170,     3,     3,   171,   130,    17,    63,    34,    97,
      35,   178,   170,     3,    87,    88,    89,    86,    34,    91,
     256,   190,    86,    95,    96,    34,     0,    53,   153,    34,
       3,     0,   190,   288,    60,     3,    56,    53,    34,    56,
       3,    74,   111,     0,    60,    63,   301,   111,    53,    17,
      55,   106,   107,   108,   110,    75,    56,    53,    75,    53,
      69,    60,    60,     0,    54,   301,    60,    87,    88,    89,
      87,    88,    89,   106,   107,   163,   245,   110,   187,   188,
      89,    54,   103,   109,   248,   110,   107,   245,   324,   258,
      17,    54,   110,   102,   115,   116,    34,   105,   109,   187,
     258,   133,   134,   135,   176,   269,   109,    34,   109,   130,
      53,    61,   111,   111,    64,    53,    34,    55,    16,   286,
      18,    26,    60,   319,   288,   292,    53,    53,    34,    55,
     151,   319,   153,    60,    60,    53,   151,   301,   307,   160,
     161,   266,    60,   163,    23,   160,   161,    53,    22,    55,
     238,   318,    32,    33,    60,    26,    27,    28,    29,   140,
     141,   142,   143,    53,    63,    55,   198,    30,    31,    68,
      69,    21,    53,   342,    55,    74,   292,    76,   109,    78,
     111,   306,    20,   292,    19,    84,    85,    34,    35,    36,
      89,     3,    91,    92,    60,    94,    95,    39,    40,     3,
      99,   100,   101,   102,   292,   109,    60,   111,    54,   318,
     319,    53,   111,    55,   110,    57,    58,    60,   238,    60,
     293,   294,   295,    24,    25,   136,   137,   352,   138,   139,
     318,    26,   253,   110,   110,     5,   256,     3,   253,   256,
      55,   144,   145,   276,   111,   266,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   278,     3,    28,
      54,    54,    17,   278,    54,    53,     5,     3,    60,    60,
     109,    60,    54,   293,   294,   295,   293,   294,   295,   110,
       4,   301,   303,    54,   301,   306,    53,   109,   303,   109,
      28,    56,   313,   110,     5,   109,   109,    75,   313,    23,
     109,   109,   349,   273,   324,   162,   313,   324,    32,    33,
      34,   278,   146,    37,    38,    39,    40,   116,   147,   149,
       4,   148,   150,   239,   176,    49,    50,    51,    52,    53,
     286,   352,   255,   152,    -1,    59,    60,   301,    62,    63,
      64,    65,   324,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      84,    85,     4,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    -1,    97,    98,    99,   100,   101,   102,    63,
      -1,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    88,    89,    -1,    91,    92,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,    -1,
      -1,    63,    -1,    65,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    23,    -1,    98,    99,   100,   101,
     102,    -1,    -1,    32,    33,    34,    -1,    -1,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,
      59,    60,    -1,    62,    63,    64,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    74,    -1,    76,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      89,    90,    91,    92,    -1,    94,    95,    23,    97,    -1,
      99,   100,   101,   102,    -1,    -1,    32,    33,    34,    -1,
      -1,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    -1,
      -1,    23,    -1,    59,    60,    -1,    62,    -1,    64,    -1,
      32,    33,    34,    -1,    -1,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    -1,    -1,    90,    23,    -1,    59,    60,    -1,
      62,    97,    64,    -1,    32,    33,    34,    -1,    -1,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    -1,    -1,    90,    23,
      -1,    59,    60,    -1,    62,    97,    64,    -1,    32,    33,
      34,    -1,    -1,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      -1,    -1,    90,    -1,    -1,    59,    60,    -1,    62,    97,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    90,    -1,    -1,    -1,
      83,    84,    85,    97,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    97,    98,    99,   100,   101,   102,
      63,   104,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    97,    98,    99,   100,   101,   102,
      63,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    -1,    76,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    89,    -1,    91,    92,
      -1,    94,    95,    -1,    -1,    -1,    99,   100,   101,   102
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   106,   107,   108,   113,   114,   115,   116,    23,    32,
      33,    34,    37,    38,    39,    40,    49,    50,    51,    52,
      53,    59,    60,    62,    64,    90,    97,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   154,   155,   157,    61,    63,    64,    65,
      68,    69,    74,    76,    77,    78,    83,    84,    85,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    97,    98,
      99,   100,   101,   102,   104,   117,   118,   119,   124,   127,
     130,   131,   132,   133,   158,   159,   161,   162,   163,   164,
     165,   166,   167,   175,   176,   163,   164,   172,   187,     0,
       0,     0,     0,    53,   139,   139,    53,    53,   139,   139,
      26,   157,   187,    39,    40,    53,    55,    57,    58,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     156,   139,   141,    34,    35,    36,    32,    33,    30,    31,
      26,    27,    28,    29,    24,    25,    23,    22,    21,    20,
      19,    16,    18,     3,    63,   110,   159,    60,   187,   118,
      35,   110,     3,    34,    53,    60,   109,   169,   170,   179,
     180,   181,   182,   159,   159,   159,   168,   171,   172,    63,
     110,    60,   177,   178,   172,   172,    53,   181,   182,   188,
     189,   190,   191,   194,   187,   187,   187,    54,    54,    54,
     136,   155,   136,    60,    60,   155,   141,   141,   141,   142,
     142,   143,   143,   144,   144,   144,   144,   145,   145,   146,
     147,   148,   149,   150,   157,   151,   155,   110,   179,   110,
      26,   157,   134,   135,   157,   133,   164,   182,   183,     3,
     109,    53,   190,   194,   179,   180,   111,   171,    17,   173,
     174,   179,   110,     5,   111,     3,   195,   188,   189,   190,
     194,    55,     3,    54,    28,   141,     3,    54,    56,    17,
     120,    86,   111,   128,   129,   121,   122,   105,   109,   111,
     164,   182,   170,    54,   153,   154,     3,   109,    17,   157,
     177,     4,   160,   161,   163,   164,   184,   185,   186,   196,
      54,   192,    60,    53,   155,   154,     5,    60,   109,   111,
     129,    60,   187,   110,   135,   174,   153,   179,   181,   182,
     188,   159,   159,   159,     3,    54,   153,   184,   193,    54,
     157,   155,   194,   109,    28,   123,   134,     4,   186,    56,
      54,   109,    17,   109,   110,   111,   194,    60,   111,   125,
     126,   109,     5,   109,   111,   126,   155,   109,   109
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 192 "libdtrace/dt_grammar.y"
    { return dt_node_root((yyvsp[(1) - (2)].l_node)); ;}
    break;

  case 3:
#line 193 "libdtrace/dt_grammar.y"
    { return dt_node_root((yyvsp[(1) - (2)].l_node)); ;}
    break;

  case 4:
#line 194 "libdtrace/dt_grammar.y"
    { return dt_node_root((yyvsp[(1) - (2)].l_node)); ;}
    break;

  case 5:
#line 197 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = NULL; ;}
    break;

  case 6:
#line 198 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (yyvsp[(2) - (2)].l_node); ;}
    break;

  case 7:
#line 201 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_program(NULL); ;}
    break;

  case 8:
#line 202 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_program((yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 9:
#line 205 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = NULL; ;}
    break;

  case 10:
#line 206 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (dt_node_t *)(yyvsp[(2) - (2)].l_decl); ;}
    break;

  case 12:
#line 211 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = LINK((yyvsp[(1) - (2)].l_node), (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 18:
#line 224 "libdtrace/dt_grammar.y"
    { dt_scope_push(NULL, CTF_ERR); ;}
    break;

  case 19:
#line 225 "libdtrace/dt_grammar.y"
    {
			/*
			 * We push a new declaration scope before shifting the
			 * assignment_expression in order to preserve ds_class
			 * and ds_ident for use in dt_node_inline().  Once the
			 * entire inline_definition rule is matched, pop the
			 * scope and construct the inline using the saved decl.
			 */
			dt_scope_pop();
			(yyval.l_node) = dt_node_inline((yyvsp[(6) - (7)].l_node));
		;}
    break;

  case 20:
#line 238 "libdtrace/dt_grammar.y"
    { yypcb->pcb_xlator_input = 1; ;}
    break;

  case 21:
#line 240 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = (yyvsp[(2) - (2)].l_decl); ;}
    break;

  case 22:
#line 243 "libdtrace/dt_grammar.y"
    { yypcb->pcb_xlator_input = 0; ;}
    break;

  case 23:
#line 249 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_xlator((yyvsp[(2) - (10)].l_decl), (yyvsp[(4) - (10)].l_decl), (yyvsp[(5) - (10)].l_str), (yyvsp[(8) - (10)].l_node));
		;}
    break;

  case 24:
#line 253 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_xlator((yyvsp[(2) - (9)].l_decl), (yyvsp[(4) - (9)].l_decl), (yyvsp[(5) - (9)].l_str), NULL);
		;}
    break;

  case 26:
#line 260 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = LINK((yyvsp[(1) - (2)].l_node),(yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 27:
#line 264 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_member(NULL, (yyvsp[(1) - (4)].l_str), (yyvsp[(3) - (4)].l_node));
		;}
    break;

  case 28:
#line 270 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_provider((yyvsp[(2) - (6)].l_str), (yyvsp[(4) - (6)].l_node));
		;}
    break;

  case 29:
#line 273 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_provider((yyvsp[(2) - (5)].l_str), NULL);
		;}
    break;

  case 31:
#line 280 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = LINK((yyvsp[(1) - (2)].l_node), (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 32:
#line 284 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_probe((yyvsp[(2) - (6)].l_str), 2, (yyvsp[(3) - (6)].l_node), (yyvsp[(5) - (6)].l_node));
		;}
    break;

  case 33:
#line 287 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_probe((yyvsp[(2) - (4)].l_str), 1, (yyvsp[(3) - (4)].l_node), NULL);
		;}
    break;

  case 34:
#line 294 "libdtrace/dt_grammar.y"
    {
			/*
			 * If the input stream is a file, do not permit a probe
			 * specification without / <pred> / or { <act> } after
			 * it.  This can only occur if the next token is EOF or
			 * an ambiguous predicate was slurped up as a comment.
			 * We cannot perform this check if input() is a string
			 * because dtrace(1M) [-fmnP] also use the compiler and
			 * things like dtrace -n BEGIN have to be accepted.
			 */
			if (yypcb->pcb_fileptr != NULL) {
				dnerror((yyvsp[(1) - (1)].l_node), D_SYNTAX, "expected predicate and/"
				    "or actions following probe description\n");
			}
			(yyval.l_node) = dt_node_clause((yyvsp[(1) - (1)].l_node), NULL, NULL);
		;}
    break;

  case 35:
#line 310 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_clause((yyvsp[(1) - (4)].l_node), NULL, (yyvsp[(3) - (4)].l_node));
		;}
    break;

  case 36:
#line 313 "libdtrace/dt_grammar.y"
    {
			dnerror((yyvsp[(3) - (4)].l_node), D_SYNTAX, "expected actions { } following "
			    "probe description and predicate\n");
		;}
    break;

  case 37:
#line 318 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_clause((yyvsp[(1) - (7)].l_node), (yyvsp[(3) - (7)].l_node), (yyvsp[(6) - (7)].l_node));
		;}
    break;

  case 38:
#line 324 "libdtrace/dt_grammar.y"
    { yybegin(YYS_EXPR); (yyval.l_node) = (yyvsp[(1) - (1)].l_node); ;}
    break;

  case 40:
#line 329 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = LINK((yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 41:
#line 335 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_pdesc_by_name((yyvsp[(1) - (1)].l_str)); ;}
    break;

  case 42:
#line 336 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_pdesc_by_id((yyvsp[(1) - (1)].l_int)); ;}
    break;

  case 43:
#line 339 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (yyvsp[(1) - (1)].l_node); ;}
    break;

  case 44:
#line 340 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = LINK((yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node)); ;}
    break;

  case 45:
#line 343 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = NULL; ;}
    break;

  case 46:
#line 344 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_statement((yyvsp[(1) - (1)].l_node)); ;}
    break;

  case 48:
#line 349 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = LINK((yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 49:
#line 355 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_ident((yyvsp[(1) - (1)].l_str)); ;}
    break;

  case 50:
#line 356 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_ident((yyvsp[(1) - (1)].l_str)); ;}
    break;

  case 51:
#line 357 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_int((yyvsp[(1) - (1)].l_int)); ;}
    break;

  case 52:
#line 358 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_string((yyvsp[(1) - (1)].l_str)); ;}
    break;

  case 53:
#line 359 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_ident(DUP("self")); ;}
    break;

  case 54:
#line 360 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_ident(DUP("this")); ;}
    break;

  case 55:
#line 361 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (yyvsp[(2) - (3)].l_node); ;}
    break;

  case 57:
#line 367 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LBRAC, (yyvsp[(1) - (4)].l_node), (yyvsp[(3) - (4)].l_node));
		;}
    break;

  case 58:
#line 370 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_func((yyvsp[(1) - (3)].l_node), NULL);
		;}
    break;

  case 59:
#line 374 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_func((yyvsp[(1) - (4)].l_node), (yyvsp[(3) - (4)].l_node));
		;}
    break;

  case 60:
#line 377 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_DOT, (yyvsp[(1) - (3)].l_node), dt_node_ident((yyvsp[(3) - (3)].l_str)));
		;}
    break;

  case 61:
#line 380 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_PTR, (yyvsp[(1) - (3)].l_node), dt_node_ident((yyvsp[(3) - (3)].l_str)));
		;}
    break;

  case 62:
#line 383 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP1(DT_TOK_POSTINC, (yyvsp[(1) - (2)].l_node));
		;}
    break;

  case 63:
#line 386 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP1(DT_TOK_POSTDEC, (yyvsp[(1) - (2)].l_node));
		;}
    break;

  case 64:
#line 390 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_offsetof((yyvsp[(3) - (6)].l_decl), (yyvsp[(5) - (6)].l_str));
		;}
    break;

  case 65:
#line 394 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_XLATE, dt_node_type((yyvsp[(3) - (7)].l_decl)), (yyvsp[(6) - (7)].l_node));
		;}
    break;

  case 67:
#line 401 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = OP1(DT_TOK_PREINC, (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 68:
#line 402 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = OP1(DT_TOK_PREDEC, (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 69:
#line 403 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = OP1((yyvsp[(1) - (2)].l_tok), (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 70:
#line 404 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = OP1(DT_TOK_SIZEOF, (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 71:
#line 405 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP1(DT_TOK_SIZEOF, dt_node_type((yyvsp[(3) - (4)].l_decl)));
		;}
    break;

  case 72:
#line 408 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP1(DT_TOK_STRINGOF, (yyvsp[(2) - (2)].l_node));
		;}
    break;

  case 73:
#line 413 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_ADDROF; ;}
    break;

  case 74:
#line 414 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_DEREF; ;}
    break;

  case 75:
#line 415 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_IPOS; ;}
    break;

  case 76:
#line 416 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_INEG; ;}
    break;

  case 77:
#line 417 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_BNEG; ;}
    break;

  case 78:
#line 418 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_LNEG; ;}
    break;

  case 80:
#line 423 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LPAR, dt_node_type((yyvsp[(2) - (4)].l_decl)), (yyvsp[(4) - (4)].l_node));
		;}
    break;

  case 82:
#line 430 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_MUL, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 83:
#line 433 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_DIV, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 84:
#line 436 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_MOD, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 86:
#line 443 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_ADD, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 87:
#line 446 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_SUB, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 89:
#line 453 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LSH, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 90:
#line 456 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_RSH, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 92:
#line 463 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LT, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 93:
#line 466 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_GT, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 94:
#line 469 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LE, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 95:
#line 472 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_GE, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 97:
#line 479 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_EQU, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 98:
#line 482 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_NEQ, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 100:
#line 489 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_BAND, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 102:
#line 496 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_XOR, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 104:
#line 503 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_BOR, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 106:
#line 510 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LAND, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 108:
#line 517 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LXOR, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 110:
#line 524 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_LOR, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 113:
#line 535 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = OP3((yyvsp[(1) - (5)].l_node), (yyvsp[(3) - (5)].l_node), (yyvsp[(5) - (5)].l_node)); ;}
    break;

  case 115:
#line 540 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2((yyvsp[(2) - (3)].l_tok), (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 116:
#line 546 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_ASGN; ;}
    break;

  case 117:
#line 547 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_MUL_EQ; ;}
    break;

  case 118:
#line 548 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_DIV_EQ; ;}
    break;

  case 119:
#line 549 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_MOD_EQ; ;}
    break;

  case 120:
#line 550 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_ADD_EQ; ;}
    break;

  case 121:
#line 551 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_SUB_EQ; ;}
    break;

  case 122:
#line 552 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_LSH_EQ; ;}
    break;

  case 123:
#line 553 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_RSH_EQ; ;}
    break;

  case 124:
#line 554 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_AND_EQ; ;}
    break;

  case 125:
#line 555 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_XOR_EQ; ;}
    break;

  case 126:
#line 556 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = DT_TOK_OR_EQ; ;}
    break;

  case 128:
#line 560 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = OP2(DT_TOK_COMMA, (yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 129:
#line 565 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_decl();
			dt_decl_free(dt_decl_pop());
			yybegin(YYS_CLAUSE);
		;}
    break;

  case 130:
#line 570 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = (yyvsp[(2) - (3)].l_node);
			dt_decl_free(dt_decl_pop());
			yybegin(YYS_CLAUSE);
		;}
    break;

  case 143:
#line 596 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_AUTO); ;}
    break;

  case 144:
#line 597 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_REGISTER); ;}
    break;

  case 145:
#line 598 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_STATIC); ;}
    break;

  case 146:
#line 599 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_EXTERN); ;}
    break;

  case 147:
#line 600 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_TYPEDEF); ;}
    break;

  case 149:
#line 605 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_SELF); ;}
    break;

  case 150:
#line 606 "libdtrace/dt_grammar.y"
    { dt_decl_class(DT_DC_THIS); ;}
    break;

  case 151:
#line 609 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_INTEGER, DUP("void")); ;}
    break;

  case 152:
#line 610 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_INTEGER, DUP("char")); ;}
    break;

  case 153:
#line 611 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_SHORT); ;}
    break;

  case 154:
#line 612 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_INTEGER, DUP("int")); ;}
    break;

  case 155:
#line 613 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_LONG); ;}
    break;

  case 156:
#line 614 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_FLOAT, DUP("float")); ;}
    break;

  case 157:
#line 615 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_FLOAT, DUP("double")); ;}
    break;

  case 158:
#line 616 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_SIGNED); ;}
    break;

  case 159:
#line 617 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_UNSIGNED); ;}
    break;

  case 160:
#line 618 "libdtrace/dt_grammar.y"
    {
			(yyval.l_decl) = dt_decl_spec(CTF_K_TYPEDEF, DUP("string"));
		;}
    break;

  case 161:
#line 621 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_TYPEDEF, (yyvsp[(1) - (1)].l_str)); ;}
    break;

  case 164:
#line 626 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_CONST); ;}
    break;

  case 165:
#line 627 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_RESTRICT); ;}
    break;

  case 166:
#line 628 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_attr(DT_DA_VOLATILE); ;}
    break;

  case 167:
#line 632 "libdtrace/dt_grammar.y"
    {
			(yyval.l_decl) = dt_scope_pop();
		;}
    break;

  case 168:
#line 635 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec((yyvsp[(1) - (2)].l_tok), (yyvsp[(2) - (2)].l_str)); ;}
    break;

  case 169:
#line 639 "libdtrace/dt_grammar.y"
    { dt_decl_sou((yyvsp[(1) - (2)].l_tok), NULL); ;}
    break;

  case 170:
#line 640 "libdtrace/dt_grammar.y"
    { dt_decl_sou((yyvsp[(1) - (3)].l_tok), (yyvsp[(2) - (3)].l_str)); ;}
    break;

  case 171:
#line 644 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = CTF_K_STRUCT; ;}
    break;

  case 172:
#line 645 "libdtrace/dt_grammar.y"
    { (yyval.l_tok) = CTF_K_UNION; ;}
    break;

  case 176:
#line 655 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = LINK((yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 177:
#line 661 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_decl();
			dt_decl_reset();
		;}
    break;

  case 178:
#line 668 "libdtrace/dt_grammar.y"
    {
			dt_decl_free(dt_decl_pop());
		;}
    break;

  case 180:
#line 675 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = (yyvsp[(2) - (2)].l_decl); ;}
    break;

  case 182:
#line 677 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = (yyvsp[(2) - (2)].l_decl); ;}
    break;

  case 185:
#line 686 "libdtrace/dt_grammar.y"
    { dt_decl_member(NULL); ;}
    break;

  case 186:
#line 687 "libdtrace/dt_grammar.y"
    { dt_decl_member((yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 187:
#line 688 "libdtrace/dt_grammar.y"
    {
			dt_decl_member((yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 188:
#line 694 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_scope_pop(); ;}
    break;

  case 189:
#line 695 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_spec(CTF_K_ENUM, (yyvsp[(2) - (2)].l_str)); ;}
    break;

  case 190:
#line 699 "libdtrace/dt_grammar.y"
    { dt_decl_enum(NULL); ;}
    break;

  case 191:
#line 700 "libdtrace/dt_grammar.y"
    { dt_decl_enum((yyvsp[(2) - (3)].l_str)); ;}
    break;

  case 195:
#line 709 "libdtrace/dt_grammar.y"
    { dt_decl_enumerator((yyvsp[(1) - (1)].l_str), NULL); ;}
    break;

  case 196:
#line 710 "libdtrace/dt_grammar.y"
    {
			dt_decl_enumerator((yyvsp[(1) - (3)].l_str), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 199:
#line 720 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_ident((yyvsp[(1) - (1)].l_str)); ;}
    break;

  case 200:
#line 721 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = (yyvsp[(2) - (3)].l_decl); ;}
    break;

  case 201:
#line 722 "libdtrace/dt_grammar.y"
    { dt_decl_array((yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 202:
#line 723 "libdtrace/dt_grammar.y"
    { dt_decl_func((yyvsp[(1) - (2)].l_decl), (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 203:
#line 726 "libdtrace/dt_grammar.y"
    { dt_decl_top()->dd_attr |= DT_DA_PAREN; ;}
    break;

  case 204:
#line 729 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_ptr(); ;}
    break;

  case 205:
#line 730 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_ptr(); ;}
    break;

  case 206:
#line 731 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_ptr(); ;}
    break;

  case 207:
#line 732 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = dt_decl_ptr(); ;}
    break;

  case 209:
#line 737 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = (yyvsp[(2) - (2)].l_decl); ;}
    break;

  case 211:
#line 742 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = dt_node_vatype(); ;}
    break;

  case 212:
#line 743 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = LINK((yyvsp[(1) - (3)].l_node), dt_node_vatype());
		;}
    break;

  case 214:
#line 749 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = LINK((yyvsp[(1) - (3)].l_node), (yyvsp[(3) - (3)].l_node));
		;}
    break;

  case 215:
#line 755 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_type(NULL);
		;}
    break;

  case 216:
#line 758 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_type(NULL);
		;}
    break;

  case 217:
#line 761 "libdtrace/dt_grammar.y"
    {
			(yyval.l_node) = dt_node_type(NULL);
		;}
    break;

  case 218:
#line 766 "libdtrace/dt_grammar.y"
    {
			(yyval.l_decl) = dt_decl_pop();
		;}
    break;

  case 219:
#line 769 "libdtrace/dt_grammar.y"
    {
			(yyval.l_decl) = dt_decl_pop();
		;}
    break;

  case 223:
#line 781 "libdtrace/dt_grammar.y"
    { (yyval.l_decl) = (yyvsp[(2) - (3)].l_decl); ;}
    break;

  case 224:
#line 782 "libdtrace/dt_grammar.y"
    { dt_decl_array((yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 225:
#line 783 "libdtrace/dt_grammar.y"
    { dt_decl_array((yyvsp[(1) - (1)].l_node)); (yyval.l_decl) = NULL; ;}
    break;

  case 226:
#line 784 "libdtrace/dt_grammar.y"
    { dt_decl_func((yyvsp[(1) - (2)].l_decl), (yyvsp[(2) - (2)].l_node)); ;}
    break;

  case 227:
#line 785 "libdtrace/dt_grammar.y"
    { dt_decl_func(NULL, (yyvsp[(1) - (1)].l_node)); ;}
    break;

  case 228:
#line 788 "libdtrace/dt_grammar.y"
    { yypcb->pcb_array_dimens = 1; ;}
    break;

  case 229:
#line 789 "libdtrace/dt_grammar.y"
    { dt_scope_push(NULL, CTF_ERR); ;}
    break;

  case 230:
#line 790 "libdtrace/dt_grammar.y"
    {
			dt_scope_pop();
			yypcb->pcb_array_dimens = 0;

			(yyval.l_node) = (yyvsp[(4) - (5)].l_node);
		;}
    break;

  case 231:
#line 799 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = NULL; ;}
    break;

  case 232:
#line 800 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (yyvsp[(1) - (1)].l_node); ;}
    break;

  case 233:
#line 801 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (yyvsp[(1) - (1)].l_node); ;}
    break;

  case 234:
#line 804 "libdtrace/dt_grammar.y"
    { dt_scope_push(NULL, CTF_ERR); ;}
    break;

  case 235:
#line 805 "libdtrace/dt_grammar.y"
    {
			dt_scope_pop();
			(yyval.l_node) = (yyvsp[(3) - (4)].l_node);
		;}
    break;

  case 236:
#line 812 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = NULL; ;}
    break;

  case 237:
#line 813 "libdtrace/dt_grammar.y"
    { (yyval.l_node) = (yyvsp[(1) - (1)].l_node); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3088 "/tmp/dt_grammar.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 816 "libdtrace/dt_grammar.y"


