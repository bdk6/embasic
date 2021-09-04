/*
 * symbol.h
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */

////////////////////////////////////////////////////////////////////////////////////////
///  Copyright (c) 2013 William R Cooke
////////////////////////////////////////////////////////////////////////////////////////
///  @file symbol.h
///  @brief Symbol and symbol table definitions for embasic
////////////////////////////////////////////////////////////////////////////////////////


#ifndef SYMBOL_H
#define SYMBOL_H

#include "scanner.h"
#include <stdint.h>

enum SYM_TYPE
{
   SYM_UNDEF     =  0,        // undefined symbol
   SYM_BYTE,                  //
   SYM_INT,
   SYM_WORD,
   SYM_LONG,
   SYM_SINGLE,
   SYM_DOUBLE,
   SYM_STRING,
   SYM_LABEL,

   SYM_FINAL
};

enum SYM_STORAGE
{
   SYM_UNKNOWN       = 0,     // Don't know yet
   SYM_REGISTER,
   SYM_STACK,
   SYM_FLASH,
   SYM_EEPROM,
   SYM_RAM
};



class Symbol
{
public:

   Symbol();  // constructor
   ~Symbol();  // destructor
   static Symbol *insert(Token &tok);
   static Symbol *find(Token &tok);   // find a symbol in the table
   static uint32_t s_num_syms;
   static uint32_t s_num_inserts;

   static uint32_t ident_hash( char *id);



private:

   enum{TABLE_SIZE=257};  // prime number 257,509,1009

   char *m_name;
   SYM_TYPE m_type;  // byte, word, int, fn, array, proc, etc
   bool m_is_proc;
   bool m_is_fn;
   bool m_is_array;
   bool m_is_param;
   bool m_is_constant;
   bool m_is_builtin;
   bool m_is_temp;           // Compiler generated temporary
   bool m_is_label;
   bool m_is_literal;

   bool m_defined;          // has the definition been seen?
   uint32_t m_dims_params;  // dim of array, # params
   Symbol *m_parent;        // NULL for global,
   Symbol *m_child;         // first parameter or dimension
   Symbol *m_brother;       // next parameter or dimension
   SYM_STORAGE m_location;  // Where it is located
   uint32_t m_address;      // reg num, memory address, stack offset
   Symbol *m_link;                // Next symbol in table



   static Symbol *s_table[TABLE_SIZE];  // The hash buckets
   static uint32_t s_temp_counter;
   static uint32_t s_label_counter;

public:
   char *get_name(){ return m_name; }
   bool is_proc(){ return m_is_proc;}
   void set_proc( bool proc ){ m_is_proc = proc;}
   bool is_function(){ return m_is_fn; }
   void set_function(bool fn ){ m_is_fn = fn;}
   bool is_array(){ return m_is_array; }
   void set_array( bool array ){ m_is_array = array; };
   bool is_param(){ return m_is_param; }
   void set_param(bool param){ m_is_param = param;}
   bool is_constant(){ return m_is_constant; }
   void set_constant( bool con ){ m_is_constant = con; }
   bool is_builtin(){ return m_is_builtin; }
   void set_builtin(bool builtin){ m_is_builtin = builtin; }
   bool is_temp(){ return m_is_temp; }
   void set_temp( bool temp ){ m_is_temp = temp; }
   bool is_label(){ return m_is_label; }
   void set_label( bool lbl ){ m_is_label = lbl; }
   bool is_literal(){ return m_is_literal;}
   void set_literal( bool lit ){ m_is_literal = lit;}

   bool is_defined(){ return m_defined; }
   bool set_defined( bool def ){ return (m_defined = def); }

   static Symbol *make_temp();
   static Symbol *make_label();
   static void clear_table();
   static void print_table();


};






#endif
