/*
 * token.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */



#include <stdio.h>

FILE * infile;
//int main(int argc, char **argv)
//{
//
//   infile=fopen("scanner.cpp","r");
//   char c=' ';
//   while(c!= EOF)
//   {
//      putchar(c);
//      c=getc(infile);
//   }
//   fclose(infile);
//   return 0;
//}



//////////////////////////////////////////////////////////////////////////////////
//
//  Lexical Analyzer module for BCBASIC
//
//  wrcooke
//  Feb 12, 2012
//
//////////////////////////////////////////////////////////////////////////////////

#ifndef SCANNER_H
#define SCANNER_H

#include <stdint.h>
#include <stdio.h>

enum {STRING_SIZE=256};


typedef enum
{
    TOK_UNDEF, TOK_IDENT, TOK_CHAR, TOK_INT, TOK_STRING, TOK_PLUS, TOK_MINUS,
    TOK_STAR, TOK_SLASH, TOK_PERCENT, TOK_LESS, TOK_GREATER, TOK_LESSEQ,
    TOK_GREATEQ, TOK_SHL, TOK_SHR, TOK_NOTEQ, TOK_DOLLAR, TOK_AMP, TOK_CARET,
    TOK_PIPE, TOK_EQ, TOK_LPAREN, TOK_RPAREN, TOK_COMMA, TOK_COLON, TOK_SEMI,
    TOK_QUOTE, TOK_APOST, TOK_TICK, TOK_TILDE, TOK_EXCLAM, TOK_DOT, TOK_AT,
    TOK_POUND, TOK_UNDER, TOK_BACKSL, TOK_LBRACK, TOK_RBRACK, TOK_LBRACE,
    TOK_RBRACE

}    token_t;

class Token
{
 public:
   Token(void);
   ~Token();
   int scan(void);
   static int file_read(char *fname);



private:
   token_t  m_typ;
   uint32_t m_line_num;
   uint32_t m_column_num;
   char    *m_chars;
   uint32_t m_length;

   static FILE *s_fname;
   static char s_chars[STRING_SIZE];



};

#endif

