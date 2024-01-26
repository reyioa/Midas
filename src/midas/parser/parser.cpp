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

std::unique_ptr<ast::ASTStructCallValuesNode> Parser::parseStructValues(){};
std::unique_ptr<ast::ASTStructCallExpressionNode>
Parser::parseStructDeclaration() {
  std::unique_ptr<std::vector<ast::ASTVaribleTypeNode>> Template;
  std::unique_ptr<ast::ASTStructCallValuesNode> StructsValues;
};
std::unique_ptr<ast::ASTStructDefinitionNode> Parser::parseStructDefinition() {
  if (this->parseToken().get()->token.token_type != token::eToken::TK_Struct)
    return nullptr;

  std::unique_ptr<ast::ASTDefinitionNode> DefinitionNode =
      this->parseDefinition();
  std::unique_ptr<ast::ASTTemplateNode> TemplateNode = this->parseTemplate();

  std::unique_ptr<std::vector<ast::ASTTokenNode>> TokenNodes;
  std::unique_ptr<std::vector<ast::ASTDefinitionNode>> DefinitionNodes;
  if (this->_Terminals[this->_TerminalCounter].token_type ==
      token::eToken::TK_Colon) {
    std::unique_ptr<ast::ASTTokenNode> TokenNode =
        this->parseToken(this->_Terminals[this->_TerminalCounter]);

    while (TokenNode->token.token_type == token::eToken::TK_Public ||
           TokenNode->token.token_type == token::eToken::TK_Private) {

      TokenNodes->push_back(*TokenNode.get());
      std::unique_ptr<ast::ASTTokenNode> TokenNode =
          this->parseToken(this->_Terminals[this->_TerminalCounter]);

      std::unique_ptr<ast::ASTDefinitionNode> PrivacyDefinitionNode =
          this->parseDefinition();
      assert((DefinitionNode != nullptr) && "Expected Statement 'Definition'");
      DefinitionNodes->push_back(*PrivacyDefinitionNode.get());
    }

    assert((DefinitionNodes->size() == TokenNodes->size()) &&
           "Expecting Definition and Visiblitity to be the same amount");
    this->nextToken();
  }

  this->nextToken();
  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_LBrace) &&
         "Expected '{'");

  std::unique_ptr<ast::ASTBlockNode> BlockNode = this->parseBlock();

  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_RBrace) &&
         "Expected '}'");
  return std::make_unique<ast::ASTStructDefinitionNode>(
      std::move(DefinitionNode), std::move(TemplateNode), std::move(TokenNodes),
      std::move(DefinitionNodes), std::move(BlockNode));
};
std::unique_ptr<ast::ASTEnumDefinitionNode> Parser::parseEnumDefinition() {

  if (this->parseToken().get()->token.token_type != token::eToken::TK_Enum)
    return nullptr;

  std::unique_ptr<ast::ASTDefinitionNode> DefinitionNode =
      this->parseDefinition();

  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_LBrace) &&
         "Expected '{'");
  std::unique_ptr<std::vector<ast::ASTStructCallValuesNode>> EnumDefintions;
  std::unique_ptr<ast::ASTStructCallValuesNode> EnumDefintion =
      this->parseStructValues();
  while (EnumDefintion != nullptr) {

    EnumDefintions->push_back(*EnumDefintion.get());
    std::unique_ptr<ast::ASTStructCallValuesNode> EnumDefintion =
        this->parseStructValues();
  }
  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_LBrace) &&
         "Expected '}'");
  return std::make_unique<ast::ASTEnumDefinitionNode>(
      std::move(DefinitionNode), std::move(EnumDefintions));
};

std::unique_ptr<ast::ASTInterfaceDefinitionNode>
Parser::parseInterfaceDefinition() {

  if (this->parseToken().get()->token.token_type != token::eToken::TK_Interface)
    return nullptr;

  std::unique_ptr<ast::ASTDefinitionNode> DefinitionNode =
      this->parseDefinition();

  assert((DefinitionNode != nullptr) && "Expected Statement 'Definition'");
  std::unique_ptr<ast::ASTTemplateNode> TemplateNode = this->parseTemplate();

  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_LBrace) &&
         "Expected '{'");

  std::unique_ptr<std::vector<ast::ASTFunctionDefinitionNode>> FuncDefinitions;
  std::unique_ptr<ast::ASTFunctionDefinitionNode> FuncDefinition =
      this->parseFunctionDefinition();
  while (FuncDefinition != nullptr) {

    FuncDefinitions->push_back(*FuncDefinition.get());
    std::unique_ptr<ast::ASTFunctionDefinitionNode> FuncDefinition =
        this->parseFunctionDefinition();
  }
  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_LBrace) &&
         "Expected '}'");
  return std::make_unique<ast::ASTInterfaceDefinitionNode>(
      std::move(DefinitionNode), std::move(TemplateNode),
      std::move(FuncDefinitions));
};

std::unique_ptr<ast::ASTAsyncNode> Parser::parseAsync() {
  std::unique_ptr<ast::ASTTokenNode> Node = this->parseToken();
  if (!Node || Node.get()->token.token_type != token::eToken::TK_Async) {
    return nullptr;
  }
  std::unique_ptr<ast::ASTExpressionNode> Expr = this->parseExpression();
  assert((Expr != nullptr) && "Expected Statement 'Expr'");
  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_Semicolon) &&
         "Expected ';'");
  return std::make_unique<ast::ASTAsyncNode>(std::move(Expr));
};
std::unique_ptr<ast::ASTAwaitNode> Parser::parseAwait() {
  std::unique_ptr<ast::ASTTokenNode> Node = this->parseToken();
  if (!Node || Node.get()->token.token_type != token::eToken::TK_Await) {
    return nullptr;
  }
  std::unique_ptr<ast::ASTExpressionNode> Expr = this->parseExpression();
  assert((Expr != nullptr) && "Expected Statement 'Expr'");
  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_Semicolon) &&
         "Expected ';'");
  return std::make_unique<ast::ASTAwaitNode>(std::move(Expr));
};
std::unique_ptr<ast::ASTYieldNode> Parser::parseYield() {
  std::unique_ptr<ast::ASTTokenNode> Node = this->parseToken();
  if (!Node || Node.get()->token.token_type != token::eToken::TK_Async) {
    return nullptr;
  }
  std::unique_ptr<ast::ASTExpressionNode> Expr = this->parseExpression();
  assert((Expr != nullptr) && "Expected Statement 'Expr'");
  assert((this->parseToken().get()->token.token_type ==
          token::eToken::TK_Semicolon) &&
         "Expected ';'");
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
    Nodes->push_back(*Node.get());
    std::unique_ptr<ast::ASTStatementNode> Node = this->parseStatement();
  }
  return std::make_unique<ast::ASTBlockNode>(std::move(Nodes));
};

} // namespace parser
} // namespace midas
