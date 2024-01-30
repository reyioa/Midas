//   Copyright 2024 Reyioa
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#ifndef _MIDAS_MIDAS_AST_ASTNODE_HPP_
#define _MIDAS_MIDAS_AST_ASTNODE_HPP_

#include "midas/token/token.hpp"

namespace midas {
namespace ast {

class ASTNode {
public:
  enum ASTKind {
    ASTK_Node,
    ASTK_ProgramNode,
    ASTK_Declaration,
    ASTK_DeclarationFunction,
    ASTK_DeclarationEnum,
    ASTK_DeclarationInterface,
    ASTK_DeclarationMod,
    ASTK_DeclarationImport,

    ASTK_Statement,
    ASTK_StatementSwitch,
    ASTK_StatementIdentifier,
    ASTK_StatementReturn,
    ASTK_StatementIf,
    ASTK_StatementWhile,
    ASTK_StatementAssignment,
    ASTK_StatementVarible,
    ASTK_StatementExpression,

    ASTK_Expression,
    ASTK_ExpresionUnary,
    ASTK_ExpresionBinary,

    ASTK_ExpressionBooleanOr,
    ASTK_ExpressionBooleanAnd,
    ASTK_ExpressionWise,
    ASTK_ExpressionShift,
    ASTK_ExpressionAdditive,
    ASTK_ExpressionMultiplicative,
    ASTK_ExpressionPrimary,
    ASTK_ExpressionFunctionCall,
    ASTK_ExpressionStructCall,

    ASTK_ArgumentList,
    ASTK_EnumClause,
    ASTK_Elif,
    ASTK_Else,
    ASTK_ParameterList,
    ASTK_Parameter,

    ASTK_LiteralNode,
    ASTK_IdentifierName,
    ASTK_TokenNode,

    ASTK_ElifNode,
    ASTK_ElseNode,
  };

  ASTNode(const ASTKind &kind) : kind(kind){};
  virtual ~ASTNode() = default;
  virtual const char *toString() const = 0;

  static bool classof(const ASTKind &kind) { return kind == ASTK_Node; }

private:
  const ASTKind kind;
};

class ASTProgramNode;
class ASTDeclaration;
class ASTDeclarationFunction;
class ASTDeclarationEnum;
class ASTDeclarationInterface;
class ASTDeclarationMod;
class ASTDeclarationImport;

class ASTStatement;
class ASTStatementSwitch;
class ASTStatementIdentifier;
class ASTStatementReturn;
class ASTStatementIf;
class ASTStatementWhile;
class ASTStatementAssignment;
class ASTStatementVarible;
class ASTStatementExpression;

class ASTExpression;
class ASTExpresionUnary;
class ASTExpresionBinary;

class ASTExpressionBooleanOr;
class ASTExpressionBooleanAnd;
class ASTExpressionWise;
class ASTExpressionShift;
class ASTExpressionAdditive;
class ASTExpressionMultiplicative;
class ASTExpressionPrimary;
class ASTExpressionFunctionCall;
class ASTExpressionStructCall;

class ASTArgumentList;
class ASTEnumClause;
class ASTElif;
class ASTElse;
class ASTParameterList;
class ASTParameter;

class ASTLiteralNode;
class ASTIdentifierName;
class ASTTokenNode;

class ASTElifNode;
class ASTElseNode;

} // namespace ast
} // namespace midas

#endif
