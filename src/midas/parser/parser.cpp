#include "midas/parser/parser.hpp"
#include "midas/ast/astnode.hpp"
#include "midas/token/token.hpp"
#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

namespace midas {
namespace parser {

token::Token Parser::nextToken() {
  return this->_Terminals[++this->_TerminalCounter];
};
token::Token Parser::peekToken() {
  return this->_Terminals[this->_TerminalCounter + 1];
};

std::unique_ptr<ast::ASTExpressionNode> Parser::parseExpression(){

};
std::unique_ptr<ast::ASTTermExpressionNode> Parser::parseTerm(){};
std::unique_ptr<ast::ASTBitshiftExpressionNode> Parser::parseBitshift(){};
std::unique_ptr<ast::ASTBitwiseExpressionNode> Parser::parseBitwise(){};
std::unique_ptr<ast::ASTPrimaryNode> Parser::parsePrimary(){};
std::unique_ptr<ast::ASTElementNode> Parser::parseElement(){};

std::unique_ptr<ast::ASTLiteralNode> Parser::parseLiteral(){};
std::unique_ptr<ast::ASTDefinitionNode> Parser::parseDefinition(){};
std::unique_ptr<ast::ASTVaribleDefinitionNode>
Parser::parseVaribleDefinition(){};
std::unique_ptr<ast::ASTVaribleMutateNode> Parser::parseVaribleMutate(){};
std::unique_ptr<ast::ASTParameterListNode> Parser::parseParameterList(){};
std::unique_ptr<ast::ASTTemplateNode> Parser::parseTemplate(){};

std::unique_ptr<ast::ASTFunctionDefinitionNode>
Parser::parseFunctionDefinition(){};
std::unique_ptr<ast::ASTFunctionCallExpressionNode>
Parser::parseFunctionDeclaration(){};
std::unique_ptr<ast::ASTBooleanExpressionNode>
Parser::parseBooleanExpression(){};
std::unique_ptr<ast::ASTAndExpressionNode> Parser::parseAndExpression(){};
std::unique_ptr<ast::ASTOrExpressionNode> Parser::parseOrExpression(){};

std::unique_ptr<ast::ASTIfNode> Parser::parseIf(){};
std::unique_ptr<ast::ASTElifControlIfNode> Parser::parseElif(){};
std::unique_ptr<ast::ASTElifControlIfNode> Parser::parseElse(){};

std::unique_ptr<ast::ASTWhileNode> Parser::parseWhile(){};
std::unique_ptr<ast::ASTDoNode> Parser::parseDo(){};
std::unique_ptr<ast::ASTCaseNode> Parser::parseCase(){};
std::unique_ptr<ast::ASTSwitchNode> Parser::parseSwitch(){};

std::unique_ptr<ast::ASTStructDefinitionNode> Parser::parseStructDefinition(){};
std::unique_ptr<ast::ASTStructCallExpressionNode>
Parser::parseStructDeclaration(){};
std::unique_ptr<ast::ASTEnumDefinitionNode> Parser::parseEnumDefinition(){};
std::unique_ptr<ast::ASTInterfaceDefinitionNode>
Parser::parseInterfaceDefinition(){};

std::unique_ptr<ast::ASTAsyncNode> Parser::parseAsync() {
  std::unique_ptr<ast::ASTTokenNode> Node = this->parseToken();
  if (!Node || Node.get()->token.token_type != token::eToken::TK_Async) {
    return nullptr;
  }
  std::unique_ptr<ast::ASTExpressionNode> Expr = this->parseExpression();
  assert(Expr != nullptr);
  return std::make_unique<ast::ASTAsyncNode>(std::move(Expr));
};
std::unique_ptr<ast::ASTAwaitNode> Parser::parseAwait() {
  std::unique_ptr<ast::ASTTokenNode> Node = this->parseToken();
  if (!Node || Node.get()->token.token_type != token::eToken::TK_Await) {
    return nullptr;
  }
  std::unique_ptr<ast::ASTExpressionNode> Expr = this->parseExpression();
  assert(Expr != nullptr);
  return std::make_unique<ast::ASTAwaitNode>(std::move(Expr));
};
std::unique_ptr<ast::ASTYieldNode> Parser::parseYield() {
  std::unique_ptr<ast::ASTTokenNode> Node = this->parseToken();
  if (!Node || Node.get()->token.token_type != token::eToken::TK_Async) {
    return nullptr;
  }
  std::unique_ptr<ast::ASTExpressionNode> Expr = this->parseExpression();
  assert(Expr != nullptr);
  return std::make_unique<ast::ASTYieldNode>(std::move(Expr));
};

std::unique_ptr<ast::ASTStatementNode> Parser::parseStatement() {
  std::vector<std::function<std::unique_ptr<ast::ASTStatementNode>()>> Parsers =
      {
          [this]() { return this->parseVaribleMutate(); },
          [this]() { return this->parseFunctionDefinition(); },
          [this]() { return this->parseIf(); },
          [this]() { return this->parseWhile(); },
          [this]() { return this->parseSwitch(); },
          [this]() { return this->parseInterfaceDefinition(); },
          [this]() { return this->parseStructDefinition(); },
          [this]() { return this->parseVaribleDefinition(); },
          [this]() { return this->parseAsync(); },
          [this]() { return this->parseAwait(); },
          [this]() { return this->parseYield(); },
      };
  for (const auto &Parser : Parsers) {
    std::unique_ptr<ast::ASTStatementNode> node = Parser();
    if (node != nullptr)
      return node;
  }
  return nullptr;
};
std::unique_ptr<ast::ASTBlockNode> Parser::parseBlock() {
  std::unique_ptr<std::vector<ast::ASTStatementNode>> Nodes;
  std::unique_ptr<ast::ASTStatementNode> Node = this->parseStatement();
  while (Nodes != nullptr) {
    std::unique_ptr<ast::ASTStatementNode> Node = this->parseStatement();
    Nodes->push_back(*Node.get());
  }
  return std::make_unique<ast::ASTBlockNode>(std::move(Nodes));
};

} // namespace parser
} // namespace midas
