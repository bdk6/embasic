/*
 * parser.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */




/////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 William R cooke
/////////////////////////////////////////////////////////////////////////////
///
///  @file parser.cpp
///  @brief implements parser for embasic
/////////////////////////////////////////////////////////////////////////////

#include "scanner.h"
#include "symbol.h"
#include "parser.h"


int parse_error(int code)
{
   printf("\nParse error %d\n\n", code);
   //exit(1);
   return 0;
}

/////////////////////////////////////////////////////////////////////////////
///Production

Production::Production()
{

}

Production::~Production()
{
}

/////////////////////////////////////////////////////////////////////////////
/// Progam

Program::Program()
{
   Token curr_tok;
   curr_tok.scan();
   ST_list main(curr_tok);
   Sub_list subs(curr_tok);
}

Program::~Program()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class ST_list : public Production

ST_list::ST_list(Token &tok)
{
}
ST_list::~ST_list()
{
}
// //

/////////////////////////////////////////////////////////////////////////////
///  class Sub_list : public Production

Sub_list::Sub_list(Token &tok)
{
}
Sub_list::~Sub_list()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Statement : public Production

Statement::Statement(Token &tok)
{
   // parse a statement
   switch(tok.get_type())
   {
      case TOK_IF:
      {
         tok.scan();  // get the next token
         ST_if if_st(tok);
         break;
      }
      case TOK_WHILE:
      {
         tok.scan();
         ST_while while_st(tok);
         break;
      }


      case TOK_IDENT:
      {
         // save ident
         tok.scan();
         // do array index
         if(tok.get_type() == '=')
         {
            tok.scan();  // do the assignment
            Exp expr(tok);
         }
         else
         {
            // error or procedure call
         }
      }
      default:
      {
         parse_error(0);
         break;
      }
   }
}

Statement::~Statement()
{

}

/////////////////////////////////////////////////////////////////////////////
/// class ST_if : public Production

ST_if::ST_if(Token &tok)
{
   // if exp then stlist [else stlist] end
   Exp ex(tok);
   if(tok.m_type != TOK_THEN)
   {
      parse_error(99);
   }
   tok.scan();
   ST_list st_list(tok);
   if(tok.m_type == TOK_ELSE)
   {
      // do else here
   }
   if(tok.m_type != TOK_END)
   {
      parse_error(99);
   }
   tok.scan();
}

ST_if::~ST_if()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class ST_for : public Production

ST_for::ST_for(Token &tok)
{
}

ST_for::~ST_for()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class ST_while : public Production

ST_while::ST_while(Token &tok)
{
}

ST_while::~ST_while()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class ST_repeat : public Production

ST_repeat::ST_repeat(Token &tok)
{
}
ST_repeat::~ST_repeat()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Exp : public Production

Exp::Exp(Token &tok)
{
   bool again = false;
   do
   {
      Lterm lterm(tok);
      token_t current = tok.get_type();
      if( current == TOK_OR || current == TOK_XOR )
      {
         again = true;
         tok.scan();      // get the next token
         current = tok.get_type();
      }
      else
      {
         again = false;
      }
   } while (again);
}

Exp::~Exp()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Lterm : public Production

Lterm::Lterm(Token &tok)
{
   bool again = false;
   do
   {
      Lfactor lfactor(tok);
      if( tok.get_type() == TOK_AND )
      {
         again = true;
         tok.scan();
      }
      else
      {
         again = false;
      }
   } while (again);
}

Lterm::~Lterm()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Lfactor : public Production

Lfactor::Lfactor(Token &tok)
{
   bool again = false;
   do
   {
      Simpexp simp(tok);
      token_t current = tok.get_type();
      if( current == TOK_EQ || current == TOK_NOTEQ || current == TOK_LESS || current == TOK_GREATER ||
         current == TOK_LESSEQ || current == TOK_GREATEQ )
      {
         again = true;
         tok.scan();
         current = tok.get_type();
      }
      else
      {
         again = false;
      }
   } while (again);
}

Lfactor::~Lfactor()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Simpexp : public Production

Simpexp::Simpexp(Token &tok)
{
   bool again = false;
   do
   {
      Term term(tok);
      token_t current = tok.get_type();
      if(current == TOK_PLUS || current == TOK_MINUS )
      {
         again = true;
         tok.scan();
      }
      else
      {
         again = false;
      }
   } while(again);
}

Simpexp::~Simpexp()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Term : public Production

Term::Term(Token &tok)
{
   bool again = false;
   Symbol *left = NULL, *right = NULL, *result = NULL;
   Factor fac(tok);
   result = fac.get_symbol();
   do
   {
      current_tok_type = tok.get_type();
      if(current_tok_type == TOK_STAR || current_tok_type == TOK_SLASH || current_tok_type == TOK_MOD)
      {
         token_t op = current_tok_type;
         again = true;
         tok.scan();
         //factor again
         Factor fac2(tok);
         right = fac2.get_symbol();
         // result = result op factor.sym
         // generate quad op result right newtemp
         Symbol *tmp = Symbol::make_temp();
         switch(op)
         {
            case TOK_STAR:

            	break;

            case TOK_SLASH:

            	break;

            case TOK_MOD:

            	break;

         }

         // result = newtemp
         current_tok_type = tok.get_type();
      }
      else
      {
         again = false;
      }
   } while (again);
}

Term::~Term()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Factor : public Production

Factor::Factor(Token &tok)
{
   token_t current = tok.get_type();
   switch (current)
   {
      case TOK_INT:
      case TOK_FLOAT:
      case TOK_CHAR:
      case TOK_STRING:
      {
         Literal literal(tok);
         break;
      }
      case TOK_IDENT:
      {
         Token id = tok;
         tok.scan();
         token_t type = tok.get_type();
         if(type == TOK_LPAREN)
         {
            // function call or subscripted var
         }
         else
         {
            // simple name
         }
         // do constant, variable, funcall
         break;
      }
      case TOK_MINUS:
      case TOK_NOT:
      {
         break;
      }

      default:
      {
         parse_error(99);
      }
   }
}

Factor::~Factor()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Literal : public Production

Literal::Literal(Token &tok)
{
   current_tok_type = tok.get_type();
   sym = Symbol::insert(tok);
   sym->set_literal(true);
   tok.scan();

}

Literal::~Literal()
{

}

/////////////////////////////////////////////////////////////////////////////
/// class Constant : public Production

Constant::Constant(Token &tok)
{
   current_tok_type = tok.get_type();
   sym = Symbol::insert(tok);
   tok.scan();
}

Constant::~Constant()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Variable : public Production

Variable::Variable(Token &tok)
{
   current_tok_type = tok.get_type();
   sym = Symbol::insert(tok);
   // see if it is an array
   if( sym->is_defined() && sym->is_array() )
   {
      tok.scan();
      if( tok.get_type() != TOK_LPAREN )
      {
         // parse error expected "("
      }
      tok.scan();
      // do dimensions
   }
   // need subscripts
   tok.scan();
}

Variable::~Variable()
{
}

/////////////////////////////////////////////////////////////////////////////
/// class Funcall : public Production

Funcall::Funcall(Token &tok)
{
}

Funcall::~Funcall()
{
}
