/*
 * quadruple.h
 *
 *  Created on: Apr 26, 2019
 *      Author: wrcooke
 */
/////////////////////////////////////////////////////////////////////////////
/// Copyright (c) 2013 William R Cooke
/////////////////////////////////////////////////////////////////////////////
///  @file quadruple.h
///
/////////////////////////////////////////////////////////////////////////////

#ifndef QUADRUPLE_H
#define QUADRUPLE_H


/////////////////////////////////////////////////////////////////////////////
/// The operators

enum operator_t
{
   OP_UNDEF     = 0,
   OP_ADD,
   OP_SUB,
   OP_MUL,
   OP_DIV,
   OP_MOD,
   OP_OR,
   OP_AND,
   OP_XOR,
   OP_BRANCH,
   OP_CALL,
   OP_MOVE,



   OP_END
};





class Quadruple
{
public:
   operator_t oper;
   Symbol     *opnd1;
   Symbol     *opnd2;
   Symbol     *opnd3;

   Quadruple(operator_t op, Symbol *left, Symbol *right, Symbol *result);
   ~Quadruple();
   uint32_t enter( operator_t op, Symbol *left, Symbol *right, Symbol *res );




};







#endif /* QUADRUPLE_H_ */
