/*
 * parser.h
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */

/////////////////////////////////////////////////////////////////////////////////////////
/// Copyright 2013 William R Cooke
/// parser.h
/// @file parser.h
/// @brief   header for  embasic parser
////////////////////////////////////////////////////////////////////////////////////////


#ifndef PARSER_H
#define PARSER_H


#include "scanner.h"
#include "symbol.h"


class Production
{
public:
   Production();
   ~Production();
   Symbol *get_symbol(){ return sym; }
   uint32_t get_quad(){ return quad_number; }
protected:
   Symbol *sym;
   uint32_t quad_number;
   token_t current_tok_type;

private:
};

class Program
{
public:
   Program();
   ~Program();
};

class ST_list : public Production
{
public:
   ST_list(Token &tok);
   ~ST_list();
};

class Sub_list : public Production
{
public:
   Sub_list(Token &tok);
   ~Sub_list();
};

class Statement : public Production
{
public:
   Statement(Token &tok);
   ~Statement();

};

class ST_if : public Production
{
public:
   ST_if(Token &tok);
   ~ST_if();
};

class ST_for : public Production
{
public:
   ST_for(Token &tok);
   ~ST_for();
};

class ST_while : public Production
{
public:
   ST_while(Token &tok);
   ~ST_while();
};

class ST_repeat : public Production
{
public:
   ST_repeat(Token &tok);
   ~ST_repeat();
};

class Exp : public Production
{
public:
   Exp(Token &tok);
   ~Exp();
};

class Lterm : public Production
{
public:
   Lterm(Token &tok);
   ~Lterm();
};

class Lfactor : public Production
{
public:
   Lfactor(Token &tok);
   ~Lfactor();
};

class Simpexp : public Production
{
public:
   Simpexp(Token &tok);
   ~Simpexp();
};

class Term : public Production
{
public:
   Term(Token &tok);
   ~Term();
};

class Factor : public Production
{
public:
   Factor(Token &tok);
   ~Factor();
};

class Literal : public Production
{
public:
   Literal(Token &tok);
   ~Literal();
};

class Constant : public Production
{
public:
   Constant(Token &tok);
   ~Constant();
};

class Variable : public Production
{
public:
   Variable(Token &tok);
   ~Variable();
};

class Funcall : public Production
{
public:
   Funcall(Token &tok);
   ~Funcall();
};



#endif
