/*
 * scanner.h
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */
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

enum {
   STRING_SIZE=256,
   BUFF_SIZE = 32768
};


typedef enum
{
   TOK_EOF           = -1,
    TOK_UNDEF        = 0,
    TOK_AMP          = '&',
    TOK_APOST        = '\'',
    TOK_ATSIGN       = '@',
    TOK_BACKSL       = '\\',
    TOK_CARET        = '^',
    TOK_COLON        = ':',
    TOK_COMMA        = ',',
    TOK_DOLLAR       = '$',
    TOK_DOT          = '.',
    TOK_EQ           = '=',
    TOK_EXCLAM       = '!',
    TOK_GREATER      = '>',
    TOK_LBRACE       = '{',
    TOK_LBRACK       = '[',
    TOK_LESS         = '<',
    TOK_LPAREN       = '(',
    TOK_MINUS        = '-',
    TOK_PERCENT      = '%',
    TOK_PIPE         = '|',
    TOK_PLUS         = '+',
    TOK_POUND        = '#',
    TOK_QUOTE        = '"',
    TOK_RBRACE       = '}',
    TOK_RBRACK       = ']',
    TOK_RPAREN       = ')',
    TOK_SEMI         = ';',
    TOK_SLASH        = '/',
    TOK_STAR         = '*',
    TOK_TICK         = '`',
    TOK_TILDE        = '~',
    TOK_UNDER        = '_',

    TOK_GREATEQ       = 256,
    TOK_LESSEQ,
    TOK_NOTEQ,
    TOK_SHL,
    TOK_SHR,


    TOK_IDENT,   // Identifiers are letter {letter | digit} [typechar]
    TOK_CHAR,
    TOK_FLOAT,
    TOK_INT,   // [-] digit{digit} [basechar]
    TOK_STRING,   //

    TOK_AND,
    TOK_AT,
    TOK_CONSTANT,
    TOK_DIM,
    TOK_EEPROM,
    TOK_ELSE,
    TOK_END,
    TOK_FOR,
    TOK_FUNCTION,
    TOK_IF,
    TOK_IMPORT,
    TOK_INTERRUPT,
    TOK_MOD,
    TOK_NEXT,
    TOK_NOT,
    TOK_OR,
    TOK_PROC,
    TOK_RAM,
    TOK_ROM,
    TOK_REPEAT,
    TOK_RETURN,
    TOK_STATIC,
    TOK_STEP,
    TOK_THEN,
    TOK_TO,
    TOK_UNTIL,
    TOK_VARIABLE,
    TOK_VOLATILE,
    TOK_WHILE,
    TOK_XOR

}    token_t;



class Token
{
 public:
   Token(void);
   ~Token();
   uint32_t scan(void);
   int32_t file_read(char *fname);
   static int32_t push_file( char *file_name);
   static int32_t pop_file();
   token_t get_type() { return m_type;}
   uint32_t get_line_number() { return m_line_number; }
   uint32_t get_column_number() { return m_column_number; }
   char *   get_chars() { return m_chars; }
   uint32_t get_length() { return m_length; }




//private:
   token_t  m_type;
   uint32_t m_line_number;
   uint32_t m_column_number;
   char    *m_chars;
   uint32_t m_length;
   static char s_put_back_char;
   static bool s_put_back;


   static FILE *s_file_name;
   static char s_chars[STRING_SIZE];
   static char s_stringspace[BUFF_SIZE];
   static uint32_t s_buff_index;
   static uint32_t s_current_line;
   static uint32_t s_current_column;
   int   next_char();
   int   put_back( int ch );
   token_t get_keyword( char *string);




};


#endif
