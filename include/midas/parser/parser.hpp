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

  std::vector<token::Token> _Terminals;
  std::vector<ast::ASTNode> _Nonterminals;

  int _NonterminalCounter;
  int _TerminalCounter;
};

} // namespace parser
} // namespace midas

#endif
