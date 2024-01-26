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

#include "midas/scanner/scanner.hpp"
#include "midas/token/token.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
void midas::scanner::Scanner::_createString() {
  std::string s;

  while (peek() != '"' && !isEnd(_position.current)) {
    s += advance();
  }

  if (isEnd(_position.current) || peek() == '\n') {
    throw std::runtime_error("Unterminated String");
  }

  (void)advance();
  this->_tokens.emplace_back(token::eToken::TK_String, s.c_str(),
                             _position.line, _position.cursor);
}
void midas::scanner::Scanner::_createChar() {
  std::string s;
  if (isEnd(_position.current)) {
    return;
  }
  s += advance();
  (void)advance();
  this->_tokens.emplace_back(token::eToken::TK_Char, s.c_str(), _position.line,
                             _position.cursor);
}

void midas::scanner::Scanner::_createNumber() {
  std::string s;
  s += *(_navigator);
  while (std::isdigit(peek())) {
    s += advance();
  }

  if (peek() == '.' && std::isdigit(peek_next())) {
    s += advance();

    while (std::isdigit(peek())) {
      s += advance();
    }
    this->_tokens.emplace_back(token::eToken::TK_Float, s.c_str(),
                               _position.line, _position.cursor);

    return;
  }
  this->_tokens.emplace_back(token::eToken::TK_Int, s.c_str(), _position.line,
                             _position.cursor);
}

void midas::scanner::Scanner::_createIdentifier() {
  std::string s;
  s += *(_navigator);

  while (std::isalnum(peek()) || peek() == '_') {
    s += advance();
  }
  if (token::get_keywords().find(s) == token::get_keywords().end()) {
    this->_tokens.emplace_back(token::eToken::TK_Iden, s.c_str(),
                               _position.line, _position.cursor);
    return;
  }
  this->_tokens.emplace_back(token::get_keywords().find(s)->second,
                             token::get_keywords().find(s)->first.c_str(),
                             _position.line, _position.cursor);
  return;
}
std::vector<midas::token::Token> midas::scanner::Scanner::scanTokens() {
  this->_tokens = {};
  while (!this->isEnd(this->_position.current)) {
    _scanToken();
  }
  return this->_tokens;
}

void midas::scanner::Scanner::_scanToken() {
  switch (*_navigator) {
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    ++_position.line;
    _position.cursor = 0;
    break;
  case '+':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::TK_AddAssign
                               : this->match('+') ? token::eToken::TK_Inc
                                                  : token::eToken::TK_Add,
                               "", _position.line, _position.cursor);
    break;
  case '-':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::TK_SubAssign
                               : this->match('-') ? token::eToken::TK_Dec
                               : this->match('>') ? token::eToken::TK_Arrow
                                                  : token::eToken::TK_Sub,
                               "", _position.line, _position.cursor);

    break;
  case '*':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::TK_MultAssign
                                                : token::eToken::TK_Mult,
                               "", _position.line, _position.cursor);
    break;
  case '/':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::TK_QuoAssign
                                                : token::eToken::TK_Quo,
                               "", _position.line, _position.cursor);
    break;
  case '%':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::TK_RemAssign
                                                : token::eToken::TK_Rem,
                               "", _position.line, _position.cursor);
    break;
  case '=':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::TK_Equal
                               : this->match('>') ? token::eToken::TK_BigArrow
                                                  : token::eToken::TK_Assign,
                               "", _position.line, _position.cursor);
    break;
  case '&':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::TK_AndAssign
                               : this->match('&') ? token::eToken::TK_LogAnd
                                                  : token::eToken::TK_And,
                               "", _position.line, _position.cursor);
    break;
  case '|':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::TK_OrAssign
                               : this->match('|') ? token::eToken::TK_LogOr
                                                  : token::eToken::TK_OrAssign,
                               "", _position.line, _position.cursor);
    break;
  case '^':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::TK_Xor
                                                : token::eToken::TK_XorAssign,
                               "", _position.line, _position.cursor);
    break;
  case '>':
    this->_tokens.emplace_back(
        this->match('=')   ? token::eToken::TK_GreaterEqual
        : this->match('>') ? (this->match('=') ? token::eToken::TK_ShrAssign
                                               : token::eToken::TK_Shr)
                           : token::eToken::TK_Greater,
        "", _position.line, _position.cursor);
    break;
  case '<':
    this->_tokens.emplace_back(
        this->match('=')   ? token::eToken::TK_LessEqual
        : this->match('<') ? (this->match('=') ? token::eToken::TK_ShlAssign
                                               : token::eToken::TK_Shl)
                           : token::eToken::TK_Less,
        "", _position.line, _position.cursor);
    break;
  case '!':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::TK_Not
                                                : token::eToken::TK_NotEqual,
                               "", _position.line, _position.cursor);
    break;

  case '.':
    this->_tokens.emplace_back(
        this->match('.')
            ? this->match('.')
                  ? token::eToken::TK_Ellipsis
                  : throw std::runtime_error("kEllipsis is not right")
            : token::eToken::TK_Period,
        "", _position.line, _position.cursor);
    break;

  case '(':
    this->_tokens.emplace_back(token::eToken::TK_LParen, "", _position.line,
                               _position.cursor);
    break;
  case '[':
    this->_tokens.emplace_back(token::eToken::TK_LBrace, "", _position.line,
                               _position.cursor);
    break;
  case '{':
    this->_tokens.emplace_back(token::eToken::TK_LBrack, "", _position.line,
                               _position.cursor);
    break;
  case ')':
    this->_tokens.emplace_back(token::eToken::TK_RParen, "", _position.line,
                               _position.cursor);
    break;
  case ']':
    this->_tokens.emplace_back(token::eToken::TK_RBrace, "", _position.line,
                               _position.cursor);
    break;
  case '}':
    this->_tokens.emplace_back(token::eToken::TK_RBrack, "", _position.line,
                               _position.cursor);
    break;
  case ',':
    this->_tokens.emplace_back(token::eToken::TK_Comma, "", _position.line,
                               _position.cursor);
    break;
  case ';':
    this->_tokens.emplace_back(token::eToken::TK_Semicolon, "", _position.line,
                               _position.cursor);
  case ':':
    this->_tokens.emplace_back(token::eToken::TK_Colon, "", _position.line,
                               _position.cursor);
    break;
  case '#':
    while (peek() != '\n' && !isEnd(this->_position.current)) {
      this->advance();
    };
  case '"':
    _createString();
    break;
  case '\'':
    _createChar();
    break;
  default:
    if (std::isdigit(*_navigator)) {
      _createNumber();
      break;
    };

    if (std::isalpha(*_navigator) || *_navigator == '_') {
      _createIdentifier();
      break;
    };
    throw std::runtime_error("Unexpected Character");
    break;
  }
  (void)this->advance();
}
