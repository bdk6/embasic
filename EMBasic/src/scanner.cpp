/*
 * scanner.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */



#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <assert.h>


#include "scanner.h"

///  symbol only needed for test code printing hashes
#include "symbol.h"


struct KW
{
   char * keyword;
   token_t type;
};


struct KW keywords[] =
{
   {"AND",       TOK_AND},
   {"AT",        TOK_AT},
   {"CONSTANT",  TOK_CONSTANT},
   {"DIM",       TOK_DIM },
   {"EEPROM",    TOK_EEPROM },
   {"ELSE",      TOK_ELSE },
   {"END",       TOK_END },
   {"FOR",       TOK_FOR },
   {"FUNCTION",  TOK_FUNCTION },
   {"IF",        TOK_IF },
   {"IMPORT",    TOK_IMPORT},
   {"INTERRUPT", TOK_INTERRUPT},
   {"MOD",       TOK_MOD},
   {"NEXT",      TOK_NEXT},
   {"NOT",       TOK_NOT},
   {"OR",        TOK_OR},
   {"PROCEDURE", TOK_PROC},
   {"RAM",       TOK_RAM},
   {"ROM",       TOK_ROM},
   {"REPEAT",    TOK_REPEAT},
   {"RETURN",    TOK_RETURN},
   {"STATIC",    TOK_STATIC},
   {"STEP",      TOK_STEP},
   {"THEN",      TOK_THEN},
   {"TO",        TOK_TO},
   {"UNTIL",     TOK_UNTIL},
   {"VARIABLE",  TOK_VARIABLE},
   {"VOLATILE",  TOK_VOLATILE},
   {"WHILE",     TOK_WHILE},
   {"XOR",       TOK_XOR}

};
uint32_t const NUM_KW = 30;  // Number of keywords in above table

int main(int argc, char **argv)
{
   /*
   FILE *infile;
   infile=fopen("scanner.cpp","r");
   char c=' ';
   while(c!= EOF)
   {
      putchar(c);
      c=getc(infile);
   }
   //printf("\nEOF is %d and c is %d\n", EOF, c);
   fclose(infile);
   */
   Symbol::clear_table();

   Token tok;
   do
   {
      tok.scan();
      if(tok.m_type == TOK_IDENT)
      {
         //printf("\nIdentifier: %s",tok.get_chars());
         //printf("   HASH = %d", Symbol::ident_hash(tok.get_chars()));
         Symbol::insert(tok);
      }
      else
      {
         //printf("\nOther %d", tok.m_type);
      }

   } while (tok.m_type != TOK_EOF);

   printf("\n\n Number of symbols inserted into table %d\n", Symbol::s_num_syms);
   printf("\n Number of calls to insert() %d\n", Symbol::s_num_inserts);
   Symbol::print_table();
   return 0;
}



//////////////////////////////////////////////////////////////////////////////////
//
//  Lexical Analyzer module for BCBASIC
//
//  wrcooke
//  Feb 12, 2012
//
//////////////////////////////////////////////////////////////////////////////////

char Token::s_put_back_char = ' ';
bool Token::s_put_back = false;
char Token::s_stringspace[BUFF_SIZE];
uint32_t Token::s_buff_index = 0;

Token::Token(void)
{
  m_type = TOK_UNDEF;
  m_line_number = 0;
  m_column_number = 0;
  m_chars = NULL;
  m_length = 0;

}
uint32_t Token::scan(void)
{
   uint32_t count = 0;
   char *buff = m_chars;
   char ch = ' ';
   bool is_white = false;

   // skip whitespace
   do
   {
      //ch = getc(infile);
      // use iscntl for whitespace

      ch = next_char();


      switch(ch)
      {
	 case ' ':
	 case '\t':
	 case '\n':
	 case '\r':
	    is_white = true;
	    break;
	 default:
	    is_white = false;
	    break;
      }
   }
   while(is_white && ch != EOF);

   // Now we have the first character, start building token
   if( isalpha(ch) || ch == '_')        // identifier
   {
      m_type = TOK_IDENT;
      m_chars = &s_stringspace[s_buff_index]; // use current buffer pointer
      s_stringspace[s_buff_index++] = ch;
      ch = next_char();
      while(isalnum(ch) || '_' == ch)
      {
	 s_stringspace[s_buff_index++] = ch;
	 ch = next_char();
	 assert(s_buff_index < BUFF_SIZE - 3);  // make sure we aren't out of room
      }
      if( ch=='%' || ch=='@' || ch=='!' || ch=='#' || ch=='$' || ch=='&')
      {
         // These are the type id characters and part of the identifier
         s_stringspace[s_buff_index++] = ch;
         assert(s_buff_index < BUFF_SIZE - 3);
      }
      else
      {
         put_back(ch);
      }
      s_stringspace[s_buff_index++] = 0;  // and the terminator
      token_t ident_type = get_keyword( m_chars );
      if(ident_type != TOK_UNDEF)
      {
         m_type = ident_type;
      }

   }
   else if( isdigit(ch) )
   {
      m_type = TOK_INT;
      m_chars = &s_stringspace[s_buff_index];
      do
      {
	 s_stringspace[s_buff_index++] = ch;
	 ch = next_char();
	 assert(s_buff_index < BUFF_SIZE - 3);
      }while (isxdigit(ch));
      if(ch == 'h' || ch== 'H' || ch == 'b' || ch == 'B')
      {
	 s_stringspace[s_buff_index++] = ch;
	 ch = next_char();
      }
      else
      {
         put_back(ch);
      }
      s_stringspace[s_buff_index++] = 0;

   }
   else if( ch ==  '<' )
   {
      ch = next_char();
      if( ch == '=')
      {
	 m_type = TOK_LESSEQ;
      }
      else if( ch == '>')
      {
	 m_type = TOK_NOTEQ;
      }
      else
      {
	 m_type = TOK_GREATER;
	 put_back(ch);
      }
   }
   else if( ch == '>')
   {
      ch = next_char();
      if(ch == '=')
      {
	 m_type = TOK_GREATEQ;
      }
      else
      {
	 m_type = TOK_GREATER;
	 put_back(ch);
      }

   }
   else if( ch == '\'' ) // single quote
   {
      m_type = TOK_CHAR;
      ch = next_char();
      // store it
      ch = next_char();
      if( ch != '\'' )  //error
      {
	 // do whatever error processing here
      }
   }
   else if( ch == '"' )
   {
      m_type = TOK_STRING;
      do
      {
	 ch = next_char();
	 // store it
      } while (ch != '"');
   }
   else if( iscntrl(ch) )
   {
      m_type = TOK_UNDEF;
   }
   else
   {
      m_type = (token_t) ch;
   }

   return 0;
}




Token::~Token()
{


}

int32_t Token::file_read(char *fname)
{


   return getchar();
}


int Token::next_char()
{
   char c;
   if( s_put_back )
   {
      c = s_put_back_char;
      s_put_back = false;
   }
   else
   {
      c = getchar();
   }
   return c;
}
int Token::put_back( int ch )
{
   s_put_back_char = ch;
   s_put_back = true;
}


token_t Token::get_keyword( char * string)
{
   uint32_t low = 0;
   uint32_t high = NUM_KW-1;
   uint32_t test = 0;
   token_t type = TOK_UNDEF;
   do
   {
      test = (high + low)/2;
      // since we know the details of both strings we can take liberties
      // we want to check upper case.  Input strings have passed ident pattern
      uint32_t index = 0;
      //printf("\ntest = %d",test);
      while( keywords[test].keyword[index] != 0 && string[index] != 0
         && keywords[test].keyword[index] == (string[index] & ~0x20) )
      {
         ++index;
      }
      int32_t diff = (string[index] & ~0x20) - keywords[test].keyword[index];
      if( diff < 0)
      {
         high = test;
      }
      else if( diff > 0 )
      {
         low = test+1;
      }
      else
      {
         type = keywords[test].type;
      }
      //printf( "\ndiff= %d index = %d type = %d low= %d high = %d",diff, index, type, low, high);
      // if > low = test+1 else high = test-1
   } while( type == TOK_UNDEF && low < high);

   return type;
}





