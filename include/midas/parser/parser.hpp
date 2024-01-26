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
    _Terminals = {};
    _Nonterminals = {};

    _TerminalCounter = 0;
    _NonterminalCounter = 0;
  }

private:
  token::Token nextToken();
  token::Token peekToken();

  std::unique_ptr<ast::ASTExpressionNode> parseExpression();
  std::unique_ptr<ast::ASTTermExpressionNode> parseTerm();
  std::unique_ptr<ast::ASTBitshiftExpressionNode> parseBitshift();
  std::unique_ptr<ast::ASTBitwiseExpressionNode> parseBitwise();
  std::unique_ptr<ast::ASTTokenNode> parseToken();
  std::unique_ptr<ast::ASTTokenNode> parseToken(const token::Token &Token);
  std::unique_ptr<ast::ASTElementNode> parseElement();

  std::unique_ptr<ast::ASTLiteralNode> parseLiteral();
  std::unique_ptr<ast::ASTDefinitionNode> parseDefinition();
  std::unique_ptr<ast::ASTVaribleDefinitionNode> parseVaribleDefinition();
  std::unique_ptr<ast::ASTVaribleMutateNode> parseVaribleMutate();
  std::unique_ptr<ast::ASTParameterListNode> parseParameterList();
  std::unique_ptr<ast::ASTTemplateNode> parseTemplate();

  std::unique_ptr<ast::ASTFunctionDefinitionNode> parseFunctionDefinition();
  std::unique_ptr<ast::ASTFunctionCallExpressionNode>
  parseFunctionDeclaration();
  std::unique_ptr<ast::ASTBooleanExpressionNode> parseBooleanExpression();
  std::unique_ptr<ast::ASTAndExpressionNode> parseAndExpression();
  std::unique_ptr<ast::ASTOrExpressionNode> parseOrExpression();

  std::unique_ptr<ast::ASTIfNode> parseIf();
  std::unique_ptr<ast::ASTElifControlIfNode> parseElif();
  std::unique_ptr<ast::ASTElifControlIfNode> parseElse();

  std::unique_ptr<ast::ASTWhileNode> parseWhile();
  std::unique_ptr<ast::ASTDoNode> parseDo();
  std::unique_ptr<ast::ASTCaseNode> parseCase();
  std::unique_ptr<ast::ASTSwitchNode> parseSwitch();

  std::unique_ptr<ast::ASTStructCallValuesNode> parseStructValues();
  std::unique_ptr<ast::ASTStructDefinitionNode> parseStructDefinition();
  std::unique_ptr<ast::ASTStructCallExpressionNode> parseStructDeclaration();
  std::unique_ptr<ast::ASTEnumDefinitionNode> parseEnumDefinition();
  std::unique_ptr<ast::ASTInterfaceDefinitionNode> parseInterfaceDefinition();

  std::unique_ptr<ast::ASTAsyncNode> parseAsync();
  std::unique_ptr<ast::ASTAwaitNode> parseAwait();
  std::unique_ptr<ast::ASTYieldNode> parseYield();

  std::unique_ptr<ast::ASTStatementNode> parseStatement();
  std::unique_ptr<ast::ASTBlockNode> parseBlock();

  std::unique_ptr<ast::ASTNode> parseImport();
  std::unique_ptr<ast::ASTNode> parseStart();

  std::vector<token::Token> _Terminals;
  std::vector<ast::ASTNode> _Nonterminals;

  int _NonterminalCounter;
  int _TerminalCounter;
};

} // namespace parser
} // namespace midas

#endif
