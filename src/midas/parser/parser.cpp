#include "midas/parser/parser.hpp"
#include "midas/ast/astnode.hpp"
#include "midas/token/token.hpp"
#include <memory>
#include <vector>

namespace midas {
namespace midas {
namespace parser {

std::unique_ptr<ast::ASTTermNode> parseExpression(){};
std::unique_ptr<ast::ASTTermNode> parseTerm(){};
std::unique_ptr<ast::ASTBitshiftNode> parseBitshift(){};
std::unique_ptr<ast::ASTBitwiseNode> parseBitwise(){};
std::unique_ptr<ast::ASTPrimaryNode> parsePrimary(){};
std::unique_ptr<ast::ASTElementNode> parseElement(){};

std::unique_ptr<ast::ASTLiteralNode> parseLiteral(){};
std::unique_ptr<ast::ASTDefinitionNode> parseDefinition(){};
std::unique_ptr<ast::ASTVaribleDefinitionNode> parseVaribleDefinition(){};
std::unique_ptr<ast::ASTVaribleMutateNode> parseVaribleMutate(){};
std::unique_ptr<ast::ASTParameterListNode> parseParameterList(){};
std::unique_ptr<ast::ASTTemplateNode> parseTemplate(){};

std::unique_ptr<ast::ASTFunctionDefinitionNode> parseFunctionDefinition(){};
std::unique_ptr<ast::ASTFunctionDeclarationNode> parseFunctionDeclaration(){};
std::unique_ptr<ast::ASTBooleanExpressionNode> parseBooleanExpression(){};
std::unique_ptr<ast::ASTAndExpressionNode> parseAndExpression(){};
std::unique_ptr<ast::ASTOrExpressionNode> parseOrExpression(){};

std::unique_ptr<ast::ASTIfNode> parseIf(){};
std::unique_ptr<ast::ASTElifNode> parseElif(){};
std::unique_ptr<ast::ASTElseNode> parseElse(){};

std::unique_ptr<ast::ASTWhileNode> parseWhile(){};
std::unique_ptr<ast::ASTDoNode> parseDo(){};
std::unique_ptr<ast::ASTCaseNode> parseCase(){};
std::unique_ptr<ast::ASTSwitchNode> parseSwitch(){};

std::unique_ptr<ast::ASTStructDefinitionNode> Parser::parseStructDefinition(){};
std::unique_ptr<ast::ASTStructDeclarationNode>
Parser::parseStructDeclaration(){};
std::unique_ptr<ast::ASTEnumDefinitionNode> Parser::parseEnumDefinition(){};

std::unique_ptr<ast::ASTInterfaceDefinitionNode>
Parser::parseInterfaceDefinition() {
  if (this->peekToken().token_type != token::eToken::kInterface) {
    return nullptr;
  };

  (void)this->nextToken();

  std::unique_ptr<ast::ASTDefinitionNode> def = parseDefinition();
  if (def == nullptr) {
    // error
    return nullptr;
  };

  if (this->peekToken().token_type != token::eToken::kLBrack) {
    return nullptr;
  };

  (void)this->nextToken();

  std::vector<std::unique_ptr<ast::ASTFunctionDeclarationNode>> func_defs;

  while (this->_terminals[this->_terminal_counter].token_type !=
         token::eToken::kRBrack) {

    std::unique_ptr<ast::ASTFunctionDeclarationNode> node =
        parseFunctionDeclaration();
    func_defs.push_back(node);
  }
  return std::unique_ptr<ast::ASTInterfaceDefinitionNode>(
      new ast::ASTInterfaceDefinitionNode(def.get(), func_defs));
};

std::unique_ptr<ast::ASTAsyncNode> Parser::parseAsync() {
  if (this->peekToken().token_type != token::eToken::kAsync) {
    return nullptr;
  };

  (void)this->nextToken();

  std::unique_ptr<ast::ASTExprNode> node;
  if (node == nullptr) { // error
    return nullptr;
  };
  std::unique_ptr<ast::ASTAsyncNode> async(new ast::ASTAsyncNode(node.get()));

  return async;
};
std::unique_ptr<ast::ASTAwaitNode> Parser::parseAwait() {
  if (this->peekToken().token_type != token::eToken::kAwait) {
    return nullptr;
  };

  (void)this->nextToken();

  std::unique_ptr<ast::ASTExprNode> node = parseExpression();
  if (node == nullptr) { // error
    return nullptr;
  };
  std::unique_ptr<ast::ASTAwaitNode> await(new ast::ASTAwaitNode(node.get()));

  return await;
};
std::unique_ptr<ast::ASTYieldNode> Parser::parseYield() {

  if (this->peekToken().token_type != token::eToken::kYield) {
    return nullptr;
  };

  (void)this->nextToken();

  std::unique_ptr<ast::ASTExprNode> node;
  if (node == nullptr) { // error
    return nullptr;
  };
  std::unique_ptr<ast::ASTYieldNode> yield(new ast::ASTYieldNode(node.get()));

  return yield;
};

std::unique_ptr<ast::ASTStatementNode> Parser::parseStatement() {
  ast::ASTNode *node;
  std::unique_ptr<ast::ASTStatementNode> statement;
  node = parseExpression().get();
  if (node != nullptr) {
    if (this->peekToken().token_type != token::eToken::kSemicolon) {
      // error
      return nullptr;
    };
    this->nextToken();

    return statement;
  };

  node = parseVaribleDefinition().get();
  if (node != nullptr) {
    if (this->peekToken().token_type != token::eToken::kSemicolon) {
      // error
      return nullptr;
    };
    this->nextToken();
    return statement;
  };
  node = parseFunctionDefinition().get();
  if (node != nullptr) {
    return statement;
  };

  node = parseVaribleMutate().get();
  if (node != nullptr) {
    if (this->peekToken().token_type != token::eToken::kSemicolon) {
      // error
      return nullptr;
    };
    this->nextToken();
    return statement;
  };

  node = parseIf().get();
  if (node != nullptr) {
    return statement;
  }

  node = parseWhile().get();
  if (node != nullptr) {
    return statement;
  }

  node = parseDo().get();
  if (node != nullptr) {
    return statement;
  }

  node = parseSwitch().get();
  if (node != nullptr) {
    return statement;
  }

  return nullptr;
};
std::unique_ptr<ast::ASTBlockNode> Parser::parseBlock() {
  std::vector<ast::ASTStatementNode *> statements;

  std::unique_ptr<ast::ASTStatementNode> statement = parseStatement();
  while (statement != nullptr) {
    statements.push_back(statement.get());
    statement = parseStatement();
  };
  std::unique_ptr<ast::ASTBlockNode> block(new ast::ASTBlockNode(statements));

  return block;
};

std::unique_ptr<ast::ASTNode> Parser::parseImport(){};

std::unique_ptr<ast::ASTNode> Parser::parseStart() { return parseBlock(); };
} // namespace parser
} // namespace midas
} // namespace midas
