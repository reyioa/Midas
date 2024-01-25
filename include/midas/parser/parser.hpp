#ifndef _MIDAS_MIDAS_PARSER_PARSER_HPP_
#define _MIDAS_MIDAS_PARSER_PARSER_HPP_

#include "../ast/astnode.hpp"
#include "../token/token.hpp"
#include <memory>
#include <vector>
namespace midas {
namespace parser {

class Parser {
public:
  Parser() {
    _terminals = {};
    _nonterminals = {};

    _terminal_counter = 0;
    _nonterminal_counter = 0;
  }

private:
  inline token::Token nextToken() {
    return this->_terminals[++this->_terminal_counter];
  };
  inline token::Token peekToken() {
    return this->_terminals[this->_terminal_counter + 1];
  };

  std::unique_ptr<ast::ASTTermNode> parseExpression();
  std::unique_ptr<ast::ASTTermNode> parseTerm();
  std::unique_ptr<ast::ASTBitshiftNode> parseBitshift();
  std::unique_ptr<ast::ASTBitwiseNode> parseBitwise();
  std::unique_ptr<ast::ASTPrimaryNode> parsePrimary();
  std::unique_ptr<ast::ASTElementNode> parseElement();

  std::unique_ptr<ast::ASTLiteralNode> parseLiteral();
  std::unique_ptr<ast::ASTDefinitionNode> parseDefinition();
  std::unique_ptr<ast::ASTVaribleDefinitionNode> parseVaribleDefinition();
  std::unique_ptr<ast::ASTVaribleMutateNode> parseVaribleMutate();
  std::unique_ptr<ast::ASTParameterListNode> parseParameterList();
  std::unique_ptr<ast::ASTTemplateNode> parseTemplate();

  std::unique_ptr<ast::ASTFunctionDefinitionNode> parseFunctionDefinition();
  std::unique_ptr<ast::ASTFunctionDeclarationNode> parseFunctionDeclaration();
  std::unique_ptr<ast::ASTBooleanExpressionNode> parseBooleanExpression();
  std::unique_ptr<ast::ASTAndExpressionNode> parseAndExpression();
  std::unique_ptr<ast::ASTOrExpressionNode> parseOrExpression();

  std::unique_ptr<ast::ASTIfNode> parseIf();
  std::unique_ptr<ast::ASTElifNode> parseElif();
  std::unique_ptr<ast::ASTElseNode> parseElse();

  std::unique_ptr<ast::ASTWhileNode> parseWhile();
  std::unique_ptr<ast::ASTDoNode> parseDo();
  std::unique_ptr<ast::ASTCaseNode> parseCase();
  std::unique_ptr<ast::ASTSwitchNode> parseSwitch();

  std::unique_ptr<ast::ASTStructDefinitionNode> parseStructDefinition();
  std::unique_ptr<ast::ASTStructDeclarationNode> parseStructDeclaration();
  std::unique_ptr<ast::ASTEnumDefinitionNode> parseEnumDefinition();
  std::unique_ptr<ast::ASTInterfaceDefinitionNode> parseInterfaceDefinition();

  std::unique_ptr<ast::ASTAsyncNode> parseAsync();
  std::unique_ptr<ast::ASTAwaitNode> parseAwait();
  std::unique_ptr<ast::ASTYieldNode> parseYield();

  std::unique_ptr<ast::ASTStatementNode> parseStatement();
  std::unique_ptr<ast::ASTBlockNode> parseBlock();

  std::unique_ptr<ast::ASTNode> parseImport();

  std::unique_ptr<ast::ASTNode> parseStart();
  std::vector<token::Token> _terminals;
  std::vector<ast::ASTNode> _nonterminals;

  int _terminal_counter;
  int _nonterminal_counter;
};

} // namespace parser
} // namespace midas

#endif
