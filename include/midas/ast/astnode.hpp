#ifndef _MIDAS_MIDAS_AST_ASTNODE_HPP_
#define _MIDAS_MIDAS_AST_ASTNODE_HPP_

#include "midas/token/token.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace midas {
namespace ast {

struct ASTNode {
  virtual ~ASTNode() = default;
};
struct ASTExpressionNode;
struct ASTTermExpressionNode;
struct ASTStructCallValuesNode;
struct ASTBitshiftExpressionNode;
struct ASTBitwiseExpressionNode;
struct ASTLiteralNode;
struct ASTTokenNode;
struct ASTElementNode;
struct ASTPrimaryNode;
struct ASTDefinitionNode;
struct ASTVaribleTypeNode;
struct ASTVaribleDefinitionNode;
struct ASTVaribleMutateNode;
struct ASTParameterListNode;
struct ASTTemplateNode;
struct ASTCallExpressionNode;
struct ASTFunctionDefinitionNode;
struct ASTFunctionCallExpressionNode;
struct ASTBooleanExpressionNode;
struct ASTAndExpressionNode;
struct ASTOrExpressionNode;
struct ASTControlIfNode;
struct ASTIfNode;
struct ASTElifControlIfNode;
struct ASTElseControlIfNode;
struct ASTForNode;
struct ASTWhileNode;
struct ASTDoNode;
struct ASTCaseNode;
struct ASTSwitchNode;
struct ASTStructDefinitionNode;
struct ASTStructCallExpressionNode;
struct ASTEnumDefinitionNode;
struct ASTInterfaceDefinitionNode;
struct ASTAsyncNode;
struct ASTAwaitNode;
struct ASTYieldNode;
struct ASTReturnNode;
struct ASTStatementNode;
struct ASTImportNode;
struct ASTBlockNode;
struct ASTStartNode;
struct ASTStructCallValuesNode : ASTNode {};
struct ASTStatementNode : ASTNode {};
struct ASTExpressionNode : ASTStatementNode {
  std::unique_ptr<ASTExpressionNode> Lhs;
  token::eToken Op;
  std::unique_ptr<ASTTermExpressionNode> Rhs;
  ASTExpressionNode(std::unique_ptr<ASTExpressionNode> Lhs, token::eToken Op,
                    std::unique_ptr<ASTTermExpressionNode> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)){};
};
struct ASTCallExpressionNode : ASTNode {};

struct ASTTermExpressionNode : ASTNode {
  std::unique_ptr<ASTTermExpressionNode> Lhs;
  token::eToken Op;
  std::unique_ptr<ASTBitshiftExpressionNode> Rhs;
  ASTTermExpressionNode(std::unique_ptr<ASTTermExpressionNode> Lhs,
                        token::eToken Op,
                        std::unique_ptr<ASTBitshiftExpressionNode> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)){};
};

struct ASTBitshiftExpressionNode : ASTNode {
  std::unique_ptr<ASTBitshiftExpressionNode> Lhs;
  token::eToken Op;
  std::unique_ptr<ASTBitwiseExpressionNode> Rhs;
  ASTBitshiftExpressionNode(std::unique_ptr<ASTBitshiftExpressionNode> Lhs,
                            token::eToken Op,
                            std::unique_ptr<ASTBitwiseExpressionNode> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)){};
};
struct ASTBitwiseExpressionNode : ASTNode {
  std::unique_ptr<ASTBitwiseExpressionNode> Lhs;
  token::eToken Op;
  std::unique_ptr<ASTElementNode> Rhs;
  ASTBitwiseExpressionNode(std::unique_ptr<ASTBitwiseExpressionNode> Lhs,
                           token::eToken Op,
                           std::unique_ptr<ASTElementNode> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)){};
};

struct ASTElementNode : ASTNode {
  std::unique_ptr<ASTNode> Node;
  ASTElementNode(std::unique_ptr<ASTNode> Node) : Node(std::move(Node)){};
};

struct ASTTokenNode : ASTNode {
  token::Token token;
  ASTTokenNode(const token::Token &token) : token(token){};
};

struct ASTDefinitionNode : ASTNode {
  std::vector<token::Token> definitions;
  ASTDefinitionNode(const std::vector<token::Token> &definitions)
      : definitions(definitions){};
};

struct ASTVaribleTypeNode : ASTNode {
  std::unique_ptr<ASTNode> Node;
  ASTVaribleTypeNode(std::unique_ptr<ASTNode> Node) : Node(std::move(Node)){};
};
struct ASTVaribleDefinitionNode : ASTStatementNode {
  token::Token VarType;
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<ASTVaribleTypeNode> Type;
  std::unique_ptr<ASTExpressionNode> Expr;

  ASTVaribleDefinitionNode(token::Token VarType,
                           std::unique_ptr<ASTDefinitionNode> Name,
                           std::unique_ptr<ASTVaribleTypeNode> Type,
                           std::unique_ptr<ASTExpressionNode> Expr)
      : VarType(VarType), Name(std::move(Name)), Type(std::move(Type)),
        Expr(std::move(Expr)){};
};
struct ASTVaribleMutateNode : ASTStructCallValuesNode, ASTStatementNode {

  std::unique_ptr<ASTDefinitionNode> Name;
  token::eToken Op;
  std::unique_ptr<ASTExpressionNode> Expr;

  ASTVaribleMutateNode(std::unique_ptr<ASTDefinitionNode> Name,
                       token::eToken Op,
                       std::unique_ptr<ASTExpressionNode> Expr)
      : Name(std::move(Name)), Op(Op), Expr(std::move(Expr)){};
};
struct ASTParameterListNode : ASTNode {
  std::unique_ptr<std::vector<std::pair<ASTVaribleTypeNode, ASTTokenNode>>>
      params;

  ASTParameterListNode(
      std::unique_ptr<std::vector<std::pair<ASTVaribleTypeNode, ASTTokenNode>>>
          params)
      : params(std::move(params)){};
};

struct ASTTemplateNode : ASTNode {
  bool isdot;
  std::unique_ptr<std::vector<ASTTokenNode>> indentifier;
  ASTTemplateNode(const bool &isdot,
                  std::unique_ptr<std::vector<ASTTokenNode>> indentifier)
      : isdot(isdot), indentifier(std::move(indentifier)){};
};
struct ASTFunctionDefinitionNode : ASTCallExpressionNode, ASTStatementNode {
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<ASTParameterListNode> params;
  std::unique_ptr<ASTTemplateNode> templ;
  std::unique_ptr<ASTVaribleTypeNode> VarType;

  ASTFunctionDefinitionNode(std::unique_ptr<ASTDefinitionNode> Name,
                            std::unique_ptr<ASTParameterListNode> params,
                            std::unique_ptr<ASTTemplateNode> templ,
                            std::unique_ptr<ASTVaribleTypeNode> VarType)
      : Name(std::move(Name)), params(std::move(params)),
        templ(std::move(templ)), VarType(std::move(VarType)){};
};
struct ASTFunctionCallExpressionNode : ASTCallExpressionNode, ASTStatementNode {
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<std::vector<ASTVaribleTypeNode>> Type;
  std::unique_ptr<std::vector<ASTExpressionNode>> Exprs;

  ASTFunctionCallExpressionNode(
      std::unique_ptr<ASTDefinitionNode> Name,
      std::unique_ptr<std::vector<ASTVaribleTypeNode>> Type,
      std::unique_ptr<std::vector<ASTExpressionNode>> Exprs)
      : Name(std::move(Name)), Type(std::move(Type)), Exprs(std::move(Exprs)){};
};
struct ASTBooleanExpressionNode : ASTNode {
  std::unique_ptr<std::vector<ASTExpressionNode>> Lhs;
  token::eToken Op;
  std::unique_ptr<std::vector<ASTExpressionNode>> Rhs;
  ASTBooleanExpressionNode(std::unique_ptr<std::vector<ASTExpressionNode>> Lhs,
                           const token::eToken &Op,
                           std::unique_ptr<std::vector<ASTExpressionNode>> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)) {}
};
struct ASTAndExpressionNode : ASTNode {
  std::unique_ptr<ASTAndExpressionNode> Lhs;
  token::eToken Op;
  std::unique_ptr<ASTOrExpressionNode> Rhs;
  ASTAndExpressionNode(std::unique_ptr<ASTAndExpressionNode> Lhs,
                       token::eToken Op,
                       std::unique_ptr<ASTOrExpressionNode> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)) {}
};
struct ASTOrExpressionNode : ASTNode {
  std::unique_ptr<ASTOrExpressionNode> Lhs;
  token::eToken Op;
  std::unique_ptr<ASTBooleanExpressionNode> Rhs;
  ASTOrExpressionNode(std::unique_ptr<ASTOrExpressionNode> Lhs,
                      token::eToken Op,
                      std::unique_ptr<ASTBooleanExpressionNode> Rhs)
      : Lhs(std::move(Lhs)), Op(Op), Rhs(std::move(Rhs)){};
};
struct ASTControlIfNode : ASTNode {};

struct ASTIfNode : ASTStatementNode {
  std::unique_ptr<ASTAndExpressionNode> Expr;
  std::unique_ptr<ASTBlockNode> Block;
  std::unique_ptr<std::vector<ASTControlIfNode>> Nodes;

  ASTIfNode(std::unique_ptr<ASTAndExpressionNode> Expr,
            std::unique_ptr<ASTBlockNode> Block,
            std::unique_ptr<std::vector<ASTControlIfNode>> Nodes)
      : Expr(std::move(Expr)), Block(std::move(Block)),
        Nodes(std::move(Nodes)){};
};

struct ASTElifControlIfNode : ASTControlIfNode {
  std::unique_ptr<ASTAndExpressionNode> Expr;
  std::unique_ptr<ASTBlockNode> Block;
  std::unique_ptr<std::vector<ASTControlIfNode>> Nodes;

  ASTElifControlIfNode(std::unique_ptr<ASTAndExpressionNode> Expr,
                       std::unique_ptr<ASTBlockNode> Block,
                       std::unique_ptr<std::vector<ASTControlIfNode>> Nodes)
      : Expr(std::move(Expr)), Block(std::move(Block)),
        Nodes(std::move(Nodes)){};
};

struct ASTElseControlIfNode : ASTControlIfNode {

  std::unique_ptr<ASTBlockNode> Block;

  ASTElseControlIfNode(std::unique_ptr<ASTBlockNode> Block)
      : Block(std::move(Block)){};
};

struct ASTForNode : ASTStatementNode {

  std::unique_ptr<ASTVaribleTypeNode> Type;
  std::unique_ptr<ASTTokenNode> Identifier;
  std::unique_ptr<ASTExpressionNode> Expr;
  std::unique_ptr<ASTBlockNode> Block;

  ASTForNode(std::unique_ptr<ASTVaribleTypeNode> Type,
             std::unique_ptr<ASTTokenNode> Identifier,
             std::unique_ptr<ASTExpressionNode> Expr,
             std::unique_ptr<ASTBlockNode> Block)
      : Type(std::move(Type)), Identifier(std::move(Identifier)),
        Expr(std::move(Expr)), Block(std::move(Block)){};
};

struct ASTWhileNode : ASTStatementNode {
  std::unique_ptr<ASTAndExpressionNode> Expr;
  std::unique_ptr<ASTBlockNode> Block;
  ASTWhileNode(std::unique_ptr<ASTAndExpressionNode> Expr,
               std::unique_ptr<ASTBlockNode> Block)
      : Expr(std::move(Expr)), Block(std::move(Block)){};
};

struct ASTCaseNode : ASTNode {
  std::unique_ptr<token::Token> Type;
  std::unique_ptr<ASTExpressionNode> Expr;
  std::unique_ptr<ASTBlockNode> Block;
  ASTCaseNode(std::unique_ptr<token::Token> Type,
              std::unique_ptr<ASTExpressionNode> Expr,
              std::unique_ptr<ASTBlockNode> Block)
      : Type(std::move(Type)), Expr(std::move(Expr)), Block(std::move(Block)){};
};

struct ASTSwitchNode : ASTStatementNode {
  std::unique_ptr<std::vector<ASTCaseNode>> Cases;
  ASTSwitchNode(std::unique_ptr<std::vector<ASTCaseNode>> Cases)
      : Cases(std::move(Cases)){};
};

struct ASTStructDefinitionNode : ASTStatementNode {
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<ASTTemplateNode> Template;
  std::unique_ptr<std::vector<ASTTokenNode>> Privacy;
  std::unique_ptr<std::vector<ASTDefinitionNode>> Definitions;
  std::unique_ptr<ASTBlockNode> Calls;
  ASTStructDefinitionNode(
      std::unique_ptr<ASTDefinitionNode> Name,
      std::unique_ptr<ASTTemplateNode> Template,
      std::unique_ptr<std::vector<ASTTokenNode>> Privacy,
      std::unique_ptr<std::vector<ASTDefinitionNode>> Definitions,
      std::unique_ptr<ASTBlockNode> Calls)
      : Name(std::move(Name)), Template(std::move(Template)),
        Privacy(std::move(Privacy)), Definitions(std::move(Definitions)),
        Calls(std::move(Calls)){};
};

struct ASTStructCallExpressionNode : ASTCallExpressionNode {
  std::unique_ptr<std::vector<ASTVaribleTypeNode>> Template;
  std::unique_ptr<ASTStructCallValuesNode> StructsValues;
  ASTStructCallExpressionNode(
      std::unique_ptr<std::vector<ASTVaribleTypeNode>> Template,
      std::unique_ptr<ASTStructCallValuesNode> StructsValues)
      : Template(std::move(Template)),
        StructsValues(std::move(StructsValues)){};
};

struct ASTEnumDefinitionNode : ASTStatementNode {
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<std::vector<ASTStructCallValuesNode>> Values;

  ASTEnumDefinitionNode(
      std::unique_ptr<ASTDefinitionNode> Name,
      std::unique_ptr<std::vector<ASTStructCallValuesNode>> Values)
      : Name(std::move(Name)), Values(std::move(Values)){};
};

struct ASTInterfaceDefinitionNode : ASTStatementNode {
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<ASTTemplateNode> Template;
  std::unique_ptr<std::vector<ASTFunctionDefinitionNode>> Definitions;

  ASTInterfaceDefinitionNode(
      std::unique_ptr<ASTDefinitionNode> Name,
      std::unique_ptr<ASTTemplateNode> Template,
      std::unique_ptr<std::vector<ASTFunctionDefinitionNode>> Definitions)
      : Name(std::move(Name)), Template(std::move(Template)),
        Definitions(std::move(Definitions)){};
};

struct ASTAsyncNode : ASTStatementNode {
  std::unique_ptr<ASTExpressionNode> Expr;

  ASTAsyncNode(std::unique_ptr<ASTExpressionNode> Expr)
      : Expr(std::move(Expr)){};
};

struct ASTYieldNode : ASTStatementNode {
  std::unique_ptr<ASTExpressionNode> Expr;

  ASTYieldNode(std::unique_ptr<ASTExpressionNode> Expr)
      : Expr(std::move(Expr)){};
};

struct ASTAwaitNode : ASTStatementNode {
  std::unique_ptr<ASTExpressionNode> Expr;

  ASTAwaitNode(std::unique_ptr<ASTExpressionNode> Expr)
      : Expr(std::move(Expr)){};
};

struct ASTImportNode : ASTStatementNode {
  std::unique_ptr<ASTDefinitionNode> Name;
  std::unique_ptr<ASTTokenNode> Api;
  std::unique_ptr<ASTDefinitionNode> AsDefinition;
  ASTImportNode(std::unique_ptr<ASTDefinitionNode> Name,
                std::unique_ptr<ASTTokenNode> Api,
                std::unique_ptr<ASTDefinitionNode> AsDefinition)
      : Name(std::move(Name)), Api(std::move(Api)),
        AsDefinition(std::move(AsDefinition)){};
};

struct ASTBlockNode : ASTStatementNode {
  std::unique_ptr<std::vector<ASTStatementNode>> Statements;
  ASTBlockNode(std::unique_ptr<std::vector<ASTStatementNode>> Statements)
      : Statements(std::move(Statements)){};
};

struct ASTStartNode : ASTNode {
  std::unique_ptr<ASTBlockNode> Block;
  ASTStartNode(std::unique_ptr<ASTBlockNode> Block) : Block(std::move(Block)){};
};

} // namespace ast
} // namespace midas

#endif
