// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "handlebars/Handlebars.y.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Handlebars.y.hh"

// User implementation prologue.

#line 51 "handlebars/Handlebars.y.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 32 "handlebars/Handlebars.y" // lalr1.cc:413

  #include <sstream>
  #include "HandlebarsFlex.h"
  #include "HandlebarsParsingContext.h"

  #undef yylex
  #define yylex flex.lex

  using std::move;

#line 64 "handlebars/Handlebars.y.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 19 "handlebars/Handlebars.y" // lalr1.cc:479
namespace Handlebars {
#line 150 "handlebars/Handlebars.y.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Bison::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Bison::Bison (Handlebars::ParsingContext & context_yyarg, Handlebars::Flex & flex_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      context (context_yyarg),
      flex (flex_yyarg)
  {}

  Bison::~Bison ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Bison::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Bison::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Bison::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Bison::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Bison::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Bison::symbol_number_type
  Bison::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Bison::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Bison::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 32: // block_open
        value.move< BlockHelperNode* > (that.value);
        break;

      case 22: // handlebars
      case 23: // expression
      case 25: // partial
      case 26: // helper
      case 27: // inner_helper
      case 30: // parameter
      case 31: // block
        value.move< Node* > (that.value);
        break;

      case 29: // parameters_hash
        value.move< NodeHash > (that.value);
        break;

      case 28: // parameters_list
      case 33: // block_inner
        value.move< NodeList > (that.value);
        break;

      case 3: // TEXT
      case 9: // IDENTIFIER
      case 10: // HELPER_IDENTIFIER
      case 11: // BLOCK_HELPER_IDENTIFIER
      case 12: // HASHKEY
      case 13: // STRING
      case 34: // block_end
        value.move< QString > (that.value);
        break;

      case 24: // dot_separated_identifiers
        value.move< QStringList > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Bison::stack_symbol_type&
  Bison::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 32: // block_open
        value.copy< BlockHelperNode* > (that.value);
        break;

      case 22: // handlebars
      case 23: // expression
      case 25: // partial
      case 26: // helper
      case 27: // inner_helper
      case 30: // parameter
      case 31: // block
        value.copy< Node* > (that.value);
        break;

      case 29: // parameters_hash
        value.copy< NodeHash > (that.value);
        break;

      case 28: // parameters_list
      case 33: // block_inner
        value.copy< NodeList > (that.value);
        break;

      case 3: // TEXT
      case 9: // IDENTIFIER
      case 10: // HELPER_IDENTIFIER
      case 11: // BLOCK_HELPER_IDENTIFIER
      case 12: // HASHKEY
      case 13: // STRING
      case 34: // block_end
        value.copy< QString > (that.value);
        break;

      case 24: // dot_separated_identifiers
        value.copy< QStringList > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Bison::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Bison::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 3: // TEXT

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 392 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;

      case 9: // IDENTIFIER

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 399 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;

      case 10: // HELPER_IDENTIFIER

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 406 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;

      case 11: // BLOCK_HELPER_IDENTIFIER

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 413 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;

      case 12: // HASHKEY

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 420 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;

      case 13: // STRING

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 427 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;

      case 34: // block_end

#line 75 "handlebars/Handlebars.y" // lalr1.cc:636
        { yyoutput << '"' << yysym.value.template as< QString > ().toStdString() << '"'; }
#line 434 "handlebars/Handlebars.y.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  Bison::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Bison::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Bison::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Bison::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Bison::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Bison::debug_level_type
  Bison::debug_level () const
  {
    return yydebug_;
  }

  void
  Bison::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Bison::state_type
  Bison::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Bison::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Bison::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Bison::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 32: // block_open
        yylhs.value.build< BlockHelperNode* > ();
        break;

      case 22: // handlebars
      case 23: // expression
      case 25: // partial
      case 26: // helper
      case 27: // inner_helper
      case 30: // parameter
      case 31: // block
        yylhs.value.build< Node* > ();
        break;

      case 29: // parameters_hash
        yylhs.value.build< NodeHash > ();
        break;

      case 28: // parameters_list
      case 33: // block_inner
        yylhs.value.build< NodeList > ();
        break;

      case 3: // TEXT
      case 9: // IDENTIFIER
      case 10: // HELPER_IDENTIFIER
      case 11: // BLOCK_HELPER_IDENTIFIER
      case 12: // HASHKEY
      case 13: // STRING
      case 34: // block_end
        yylhs.value.build< QString > ();
        break;

      case 24: // dot_separated_identifiers
        yylhs.value.build< QStringList > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 81 "handlebars/Handlebars.y" // lalr1.cc:859
    { context.addNode( yystack_[0].value.as< Node* > () ); }
#line 691 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 4:
#line 85 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new StringNode( yystack_[0].value.as< QString > () ); }
#line 697 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 5:
#line 86 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[0].value.as< Node* > (); }
#line 703 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 6:
#line 87 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[0].value.as< Node* > (); }
#line 709 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 7:
#line 88 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[0].value.as< Node* > (); }
#line 715 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 8:
#line 89 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[0].value.as< Node* > (); }
#line 721 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 9:
#line 90 "handlebars/Handlebars.y" // lalr1.cc:859
    { yyerrok; }
#line 727 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 10:
#line 91 "handlebars/Handlebars.y" // lalr1.cc:859
    { yyerrok; }
#line 733 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 11:
#line 95 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new PropertyNode( move( yystack_[1].value.as< QStringList > () )); yylhs.value.as< Node* > ()->setEscape(); }
#line 739 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 12:
#line 96 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new PropertyNode( move( yystack_[1].value.as< QStringList > () )); }
#line 745 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 13:
#line 100 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< QStringList > () += yystack_[0].value.as< QString > (); }
#line 751 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 14:
#line 101 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< QStringList > ().swap( yystack_[2].value.as< QStringList > () ); yylhs.value.as< QStringList > () += yystack_[0].value.as< QString > (); }
#line 757 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 15:
#line 102 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< QStringList > ().swap( yystack_[2].value.as< QStringList > () ); yylhs.value.as< QStringList > () += yystack_[0].value.as< QString > (); }
#line 763 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 16:
#line 106 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new PartialNode( yystack_[1].value.as< QString > () ); yylhs.value.as< Node* > ()->setEscape(); }
#line 769 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 17:
#line 107 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new PartialNode( yystack_[1].value.as< QString > () ); }
#line 775 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 18:
#line 111 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[1].value.as< Node* > (); yylhs.value.as< Node* > ()->setEscape(); }
#line 781 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 19:
#line 112 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[1].value.as< Node* > (); }
#line 787 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 20:
#line 117 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new HelperNode( yystack_[2].value.as< QString > (), move( yystack_[1].value.as< NodeList > () ), move( yystack_[0].value.as< NodeHash > () )); }
#line 793 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 21:
#line 121 "handlebars/Handlebars.y" // lalr1.cc:859
    {}
#line 799 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 22:
#line 122 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< NodeList > ().swap( yystack_[1].value.as< NodeList > () ); yylhs.value.as< NodeList > () += yystack_[0].value.as< Node* > (); }
#line 805 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 23:
#line 126 "handlebars/Handlebars.y" // lalr1.cc:859
    {}
#line 811 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 24:
#line 127 "handlebars/Handlebars.y" // lalr1.cc:859
    {
                          yylhs.value.as< NodeHash > ().swap( yystack_[2].value.as< NodeHash > () );
                          yylhs.value.as< NodeHash > ().insert( yystack_[1].value.as< QString > (), yystack_[0].value.as< Node* > () );
                        }
#line 820 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 25:
#line 133 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = new StringNode( yystack_[0].value.as< QString > () ); }
#line 826 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 26:
#line 135 "handlebars/Handlebars.y" // lalr1.cc:859
    { // Try to detect integer
                          if( yystack_[0].value.as< QStringList > ().size() == 1 ) {
                            bool ok;
                            qint64 number { yystack_[0].value.as< QStringList > ().at(0).toLongLong( &ok, 0 ) };
                            if( ok ) {
                              yylhs.value.as< Node* > () = new IntegerNode( number );
                              break;
                            }
                          }
                          yylhs.value.as< Node* > () = new PropertyNode( move( yystack_[0].value.as< QStringList > () ));
                        }
#line 842 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 27:
#line 146 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< Node* > () = yystack_[1].value.as< Node* > (); }
#line 848 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 28:
#line 151 "handlebars/Handlebars.y" // lalr1.cc:859
    {
                          if( yystack_[2].value.as< BlockHelperNode* > ()->name() != yystack_[0].value.as< QString > () ) {
                            std::ostringstream msg;
                            msg << "Block mismatch {{#" << yystack_[2].value.as< BlockHelperNode* > ()->name().toStdString() << "}}";
                            error( yystack_[2].location, msg.str() );
                            msg.seekp( 0 );
                            msg << "Block mismatch {{/" << yystack_[0].value.as< QString > ().toStdString() << "}}";
                            error( yystack_[0].location, msg.str() );
                            YYABORT;
                          }
                          yystack_[2].value.as< BlockHelperNode* > ()->setInnerBlock( move( yystack_[1].value.as< NodeList > () ));
                          yylhs.value.as< Node* > () = yystack_[2].value.as< BlockHelperNode* > ();
                        }
#line 866 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 29:
#line 165 "handlebars/Handlebars.y" // lalr1.cc:859
    {
                          if( yystack_[4].value.as< BlockHelperNode* > ()->name() != yystack_[0].value.as< QString > () ) {
                            std::ostringstream msg;
                            msg << "Block mismatch {{#" << yystack_[4].value.as< BlockHelperNode* > ()->name().toStdString() << "}}";
                            error( yystack_[4].location, msg.str() );
                            msg.seekp( 0 );
                            msg << "Block mismatch {{else}}";
                            error( yystack_[2].location, msg.str() );
                            msg.seekp( 0 );
                            msg << "Block mismatch {{/" << yystack_[0].value.as< QString > ().toStdString() << "}}";
                            error( yystack_[0].location, msg.str() );
                            YYABORT;
                          }
                          yystack_[4].value.as< BlockHelperNode* > ()->setInnerBlocks( move( yystack_[3].value.as< NodeList > () ), move( yystack_[1].value.as< NodeList > () ));
                          yylhs.value.as< Node* > () = yystack_[4].value.as< BlockHelperNode* > ();
                        }
#line 887 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 30:
#line 185 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< BlockHelperNode* > () = new BlockHelperNode( yystack_[3].value.as< QString > (), move( yystack_[2].value.as< NodeList > () ), move( yystack_[1].value.as< NodeHash > () )); }
#line 893 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 31:
#line 189 "handlebars/Handlebars.y" // lalr1.cc:859
    {}
#line 899 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 32:
#line 190 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< NodeList > ().swap( yystack_[1].value.as< NodeList > () ); yylhs.value.as< NodeList > () += yystack_[0].value.as< Node* > (); }
#line 905 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;

  case 33:
#line 195 "handlebars/Handlebars.y" // lalr1.cc:859
    { yylhs.value.as< QString > ().swap( yystack_[1].value.as< QString > () ); }
#line 911 "handlebars/Handlebars.y.cc" // lalr1.cc:859
    break;


#line 915 "handlebars/Handlebars.y.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Bison::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Bison::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Bison::yypact_ninf_ = -9;

  const signed char Bison::yytable_ninf_ = -1;

  const signed char
  Bison::yypact_[] =
  {
      -9,    32,    -9,    19,    -9,    -3,    -1,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    15,    -8,     5,
      23,    30,    14,    44,    37,     8,    38,    -9,    -9,    42,
      45,    -9,    47,    -9,    -9,    -5,    -9,    -9,    -9,    -9,
      46,    35,    41,    -9,    -9,     8,    -9,    -9,    -9,    48,
      43,    39,     8,    11,    51,    -9,    -9,    -9,    -9,    -9
  };

  const unsigned char
  Bison::yydefact_[] =
  {
       2,     0,     1,     0,     4,     0,     0,     3,     5,     6,
       7,     8,    31,     9,    10,    13,    21,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,    21,    11,     0,
       0,    18,     0,    12,    19,     0,    31,    32,    28,    25,
       0,    26,    20,    22,    16,    23,    14,    15,    17,     0,
       0,     0,     0,     0,     0,    29,    27,    24,    30,    33
  };

  const signed char
  Bison::yypgoto_[] =
  {
      -9,    -9,    59,    -9,    -4,    -9,    -9,    -6,    34,    17,
      12,    -9,    -9,    27,    16
  };

  const signed char
  Bison::yydefgoto_[] =
  {
      -1,     1,    37,     8,    41,     9,    10,    20,    25,    42,
      43,    11,    12,    24,    38
  };

  const unsigned char
  Bison::yytable_[] =
  {
      23,    19,    22,    27,    15,    16,    15,    16,    15,    16,
      49,    17,    28,    17,    18,    21,    18,    15,    58,    29,
      30,    39,    33,    52,    26,    40,    13,    14,    29,    30,
      31,    19,     2,     3,    51,     4,     5,     6,     3,    32,
       4,    35,     6,    36,     3,    44,     4,    35,     6,    29,
      30,    46,    34,    52,    47,    48,    16,    56,    59,    54,
       7,    45,    53,    50,    57,     0,    55
  };

  const signed char
  Bison::yycheck_[] =
  {
       6,     5,     6,    11,     9,    10,     9,    10,     9,    10,
      15,    16,     7,    16,    19,    16,    19,     9,     7,    14,
      15,    13,     8,    12,     9,    17,     7,     8,    14,    15,
       7,    35,     0,     1,    40,     3,     4,     5,     1,     9,
       3,     4,     5,     6,     1,     7,     3,     4,     5,    14,
      15,     9,     8,    12,     9,     8,    10,    18,     7,    11,
       1,    27,    45,    36,    52,    -1,    50
  };

  const unsigned char
  Bison::yystos_[] =
  {
       0,    21,     0,     1,     3,     4,     5,    22,    23,    25,
      26,    31,    32,     7,     8,     9,    10,    16,    19,    24,
      27,    16,    24,    27,    33,    28,     9,    11,     7,    14,
      15,     7,     9,     8,     8,     4,     6,    22,    34,    13,
      17,    24,    29,    30,     7,    28,     9,     9,     8,    15,
      33,    27,    12,    29,    11,    34,    18,    30,     7,     7
  };

  const unsigned char
  Bison::yyr1_[] =
  {
       0,    20,    21,    21,    22,    22,    22,    22,    22,    22,
      22,    23,    23,    24,    24,    24,    25,    25,    26,    26,
      27,    28,    28,    29,    29,    30,    30,    30,    31,    31,
      32,    33,    33,    34
  };

  const unsigned char
  Bison::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     1,     3,     3,     4,     4,     3,     3,
       3,     0,     2,     0,     3,     1,     1,     3,     3,     5,
       6,     0,     2,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Bison::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "TEXT", "OPEN2", "OPEN3",
  "ELSE", "CLOSE2", "CLOSE3", "IDENTIFIER", "HELPER_IDENTIFIER",
  "BLOCK_HELPER_IDENTIFIER", "HASHKEY", "STRING", "'.'", "'/'", "'>'",
  "'('", "')'", "'#'", "$accept", "template", "handlebars", "expression",
  "dot_separated_identifiers", "partial", "helper", "inner_helper",
  "parameters_list", "parameters_hash", "parameter", "block", "block_open",
  "block_inner", "block_end", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Bison::yyrline_[] =
  {
       0,    80,    80,    81,    85,    86,    87,    88,    89,    90,
      91,    95,    96,   100,   101,   102,   106,   107,   111,   112,
     116,   121,   122,   126,   127,   133,   134,   146,   150,   164,
     184,   189,   190,   194
  };

  // Print the state stack on the debug stream.
  void
  Bison::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Bison::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 19 "handlebars/Handlebars.y" // lalr1.cc:1167
} // Handlebars
#line 1321 "handlebars/Handlebars.y.cc" // lalr1.cc:1167
#line 198 "handlebars/Handlebars.y" // lalr1.cc:1168


void
Handlebars::Bison::error( const location_type& loc, const std::string & msg )
{
  std::ostringstream output;
  output << loc << ':' << msg;
  context.error( QString::fromStdString( output.str() ));
}
