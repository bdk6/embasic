/*
 * symbol.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */




/////////////////////////////////////////////////////////////////////////////
///  Copyright (c) 2013 William R Cooke
////////////////////////////////////////////////////////////////////////////
///  @file symbol.cpp
///  @brief implements symbol table handling for embasic
/////////////////////////////////////////////////////////////////////////////



#include "symbol.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>



Symbol *Symbol::s_table[TABLE_SIZE];  // the symbol table
uint32_t Symbol::s_num_syms = 0;
uint32_t Symbol::s_num_inserts = 0;
uint32_t Symbol::s_temp_counter = 0;
uint32_t Symbol::s_label_counter = 0;

void Symbol::print_table()
{
   uint32_t i = 0;
   Symbol * sym;
   for( i=0; i<TABLE_SIZE; ++i)
   {
      printf("\n%5d  **********************************************\n",i);
      sym = s_table[i];
      if(sym == NULL)
      {
         printf("--\n");
      }

      while( sym != NULL )
      {
         printf( "%s  \n", sym->m_name );
         sym = sym->m_link;
      }
   }
}
void Symbol::clear_table()
{
   uint32_t i;
   for(i=0;i<TABLE_SIZE;++i)
   {
      s_table[i] = NULL;
   }
}


/////////////////////////////////////////////////////////////////////////////
///
Symbol::Symbol():
m_name(NULL), m_type(SYM_UNDEF), m_is_proc(false), m_is_fn(false), m_is_array(false), m_is_param(false),
m_is_constant(false), m_is_builtin(false), m_is_temp(false), m_defined(false), m_dims_params(0),
m_location(SYM_UNKNOWN), m_address(0), m_link(NULL)
{

}

Symbol::~Symbol()
{

}

Symbol *Symbol::insert( Token &tok)
{
   char *ident = tok.get_chars();
   uint32_t hash = ident_hash(ident);
   Symbol *sym = s_table[hash];
   while(sym != NULL && strcmp(ident, sym->m_name) != 0)
   {
      sym = sym->m_link;
   }
   if(sym == NULL)
   {
      sym = new Symbol;
      if(sym == NULL)
      {
         // error
         assert(0);
      }
      sym->m_name = ident;
      sym->m_link = s_table[hash];
      s_table[hash] = sym;
      printf("inserted %s at %d\n", s_table[hash]->m_name, hash);
      Symbol::print_table();
      ++s_num_syms;
   }
   ++s_num_inserts;
   //printf("\nInserted %s at %d\n", sym->m_name, hash);
   return sym;
}

Symbol *Symbol::find( Token &tok)
{
   char *ident = tok.get_chars();
   uint32_t hash = ident_hash(ident);
   Symbol *sym = s_table[hash];
   while(sym != NULL && strcmp(ident, sym->m_name) != 0)
   {
      sym = sym->m_link;

   }
   // check parent

   return sym;
}



uint32_t Symbol::ident_hash( char *id)
{
   uint32_t hash = 0;
   uint32_t index = 0;
   while(id[index] != 0)
   {
      hash = (hash << 1) + id[index];
      ++index;
   }
   hash %= TABLE_SIZE;
   return hash;
}

Symbol *Symbol::make_temp()
{
   Token tok;
   // tok.set_chars( name );
   char name[11];
   sprintf(name, "$%8X", s_temp_counter );
   ++s_temp_counter;
   Symbol *sym = insert(tok);
   sym->set_temp( true );


   return sym;
}

Symbol *Symbol::make_label()
{
   Token tok;
   char name[11];
   sprintf(name, "@%8X", s_label_counter );
   ++s_label_counter;
   Symbol *sym = insert(tok);
   sym->set_label( true );

   return sym;
}

