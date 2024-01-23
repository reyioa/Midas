#ifndef _MIDAS_MIDAS_AST_ASTNODE_HPP_
#define _MIDAS_MIDAS_AST_ASTNODE_HPP_

#include "midas/token/token.hpp"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
namespace midas {
namespace midas {
namespace ast {
struct ASTNode {
  virtual ~ASTNode() = default;
};
struct ASTExprNode;
struct ASTTermNode;
struct ASTBitshiftNode;
struct ASTBitwiseNode;
struct ASTLiteralNode;
struct ASTElementNode;
struct ASTPrimaryNode;
struct ASTDefinitionNode;
struct ASTVaribleType;
struct ASTVaribleDefinitionNode;
struct ASTVaribleMutateNode;
struct ASTParameterListNode;
struct ASTTemplateNode;
struct ASTFunctionDefinitionNode;
struct ASTFunctionDeclarationNode;
struct ASTBooleanExpressionNode;
struct ASTAndExpressionNode;
struct ASTOrExpressionNode;
struct ASTIfNode;
struct ASTElifNode;
struct ASTElseNode;
struct ASTForNode;
struct ASTWhileNode;
struct ASTDoNode;
struct ASTCaseNode;
struct ASTSwitchNode;
struct ASTStructDefinitionNode;
struct ASTStructDeclarationNode;
struct ASTEnumDefinitionNode;
struct ASTInterfaceDefinitionNode;
struct ASTAsyncNode;
struct ASTAwaitNode;
struct ASTYieldNode;
struct ASTReturnNode;
struct ASTStatementNode;
struct ASTImportNode;
struct ASTBlockNode;

struct ASTExprNode : ASTNode {
  std::unique_ptr<ASTExprNode> lhs;
  token::eToken op;
  std::unique_ptr<ASTTermNode> rhs;
  ASTExprNode(std::unique_ptr<ASTExprNode> lhs, token::eToken op,
              std::unique_ptr<ASTTermNode> rhs)
      : lhs(std::move(lhs)), op(op), rhs(std::move(rhs)){};
};

struct ASTTermNode : ASTNode {
  std::unique_ptr<ASTTermNode> lhs;
  token::eToken op;
  std::unique_ptr<ASTBitshiftNode> rhs;
  ASTTermNode(std::unique_ptr<ASTTermNode> lhs, token::eToken op,
              std::unique_ptr<ASTBitshiftNode> rhs)
      : lhs(std::move(lhs)), op(op), rhs(std::move(rhs)){};
};

struct ASTBitshiftNode : ASTNode {
  std::unique_ptr<ASTBitshiftNode> lhs;
  token::eToken op;
  std::unique_ptr<ASTBitwiseNode> rhs;
  ASTBitshiftNode(std::unique_ptr<ASTBitshiftNode> lhs, token::eToken op,
                  std::unique_ptr<ASTBitwiseNode> rhs)
      : lhs(std::move(lhs)), op(op), rhs(std::move(rhs)){};
};
struct ASTBitwiseNode : ASTNode {
  std::unique_ptr<ASTBitwiseNode> lhs;
  token::eToken op;
  std::unique_ptr<ASTElementNode> rhs;
  ASTBitwiseNode(std::unique_ptr<ASTBitwiseNode> lhs, token::eToken op,
                 std::unique_ptr<ASTElementNode> rhs)
      : lhs(std::move(lhs)), op(op), rhs(std::move(rhs)){};
};

struct ASTElementNode : ASTNode {};
} // namespace ast
} // namespace midas
} // namespace midas

#endif
