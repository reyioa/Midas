#include "midas/scanner/scanner.hpp"
#include "midas/token/token.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
void midas::midas::scanner::Scanner::_create_string() {
  std::string s;

  while (peek() != '"' && !isEnd(_position.current)) {
    s += advance();
  }

  if (isEnd(_position.current) || peek() == '\n') {
    throw std::runtime_error("Unterminated String");
  }

  (void)advance();
  this->_tokens.emplace_back(token::eToken::kString, s.c_str(), _position.line,
                             _position.cursor);
}
void midas::midas::scanner::Scanner::_create_char() {
  std::string s;
  if (isEnd(_position.current)) {
    return;
  }
  s += advance();
  (void)advance();
  this->_tokens.emplace_back(token::eToken::kChar, s.c_str(), _position.line,
                             _position.cursor);
}

void midas::midas::scanner::Scanner::_create_number() {
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
    this->_tokens.emplace_back(token::eToken::kFloat, s.c_str(), _position.line,
                               _position.cursor);

    return;
  }
  this->_tokens.emplace_back(token::eToken::kInt, s.c_str(), _position.line,
                             _position.cursor);
}

void midas::midas::scanner::Scanner::_create_identifier() {
  std::string s;
  s += *(_navigator);

  while (std::isalnum(peek()) || peek() == '_') {
    s += advance();
  }
  if (token::get_keywords().find(s) == token::get_keywords().end()) {
    this->_tokens.emplace_back(token::eToken::kIden, s.c_str(), _position.line,
                               _position.cursor);
    return;
  }
  this->_tokens.emplace_back(token::get_keywords().find(s)->second,
                             token::get_keywords().find(s)->first.c_str(),
                             _position.line, _position.cursor);
  return;
}
std::vector<midas::midas::token::Token>
midas::midas::scanner::Scanner::scanTokens() {
  this->_tokens = {};
  while (!this->isEnd(this->_position.current)) {
    _scanToken();
  }
  return this->_tokens;
}

void midas::midas::scanner::Scanner::_scanToken() {
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
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::kAddAssign
                               : this->match('+') ? token::eToken::kInc
                                                  : token::eToken::kAdd,
                               "", _position.line, _position.cursor);
    break;
  case '-':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::kSubAssign
                               : this->match('-') ? token::eToken::kDec
                               : this->match('>') ? token::eToken::kArrow
                                                  : token::eToken::kSub,
                               "", _position.line, _position.cursor);

    break;
  case '*':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::kMultAssign
                                                : token::eToken::kMult,
                               "", _position.line, _position.cursor);
    break;
  case '/':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::kQuoAssign
                                                : token::eToken::kQuo,
                               "", _position.line, _position.cursor);
    break;
  case '%':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::kRemAssign
                                                : token::eToken::kRem,
                               "", _position.line, _position.cursor);
    break;
  case '=':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::kEqual
                               : this->match('>') ? token::eToken::kBigArrow
                                                  : token::eToken::kAssign,
                               "", _position.line, _position.cursor);
    break;
  case '&':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::kAndAssign
                               : this->match('&') ? token::eToken::kLogAnd
                                                  : token::eToken::kAnd,
                               "", _position.line, _position.cursor);
    break;
  case '|':
    this->_tokens.emplace_back(this->match('=')   ? token::eToken::kOrAssign
                               : this->match('|') ? token::eToken::kLogOr
                                                  : token::eToken::kOrAssign,
                               "", _position.line, _position.cursor);
    break;
  case '^':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::kXor
                                                : token::eToken::kXorAssign,
                               "", _position.line, _position.cursor);
    break;
  case '>':
    this->_tokens.emplace_back(
        this->match('=')   ? token::eToken::kGreaterEqual
        : this->match('>') ? (this->match('=') ? token::eToken::kShrAssign
                                               : token::eToken::kShr)
                           : token::eToken::kGreater,
        "", _position.line, _position.cursor);
    break;
  case '<':
    this->_tokens.emplace_back(
        this->match('=')   ? token::eToken::kLessEqual
        : this->match('<') ? (this->match('=') ? token::eToken::kShlAssign
                                               : token::eToken::kShl)
                           : token::eToken::kLess,
        "", _position.line, _position.cursor);
    break;
  case '!':
    this->_tokens.emplace_back(this->match('=') ? token::eToken::kNot
                                                : token::eToken::kNotEqual,
                               "", _position.line, _position.cursor);
    break;

  case '.':
    this->_tokens.emplace_back(
        this->match('.')
            ? this->match('.')
                  ? token::eToken::kEllipsis
                  : throw std::runtime_error("kEllipsis is not right")
            : token::eToken::kPeriod,
        "", _position.line, _position.cursor);
    break;

  case '(':
    this->_tokens.emplace_back(token::eToken::kLParen, "", _position.line,
                               _position.cursor);
    break;
  case '[':
    this->_tokens.emplace_back(token::eToken::kLBrace, "", _position.line,
                               _position.cursor);
    break;
  case '{':
    this->_tokens.emplace_back(token::eToken::kLBrack, "", _position.line,
                               _position.cursor);
    break;
  case ')':
    this->_tokens.emplace_back(token::eToken::kRParen, "", _position.line,
                               _position.cursor);
    break;
  case ']':
    this->_tokens.emplace_back(token::eToken::kRBrace, "", _position.line,
                               _position.cursor);
    break;
  case '}':
    this->_tokens.emplace_back(token::eToken::kRBrack, "", _position.line,
                               _position.cursor);
    break;
  case ',':
    this->_tokens.emplace_back(token::eToken::kComma, "", _position.line,
                               _position.cursor);
    break;
  case ';':
    this->_tokens.emplace_back(token::eToken::kSemicolon, "", _position.line,
                               _position.cursor);
  case ':':
    this->_tokens.emplace_back(token::eToken::kColon, "", _position.line,
                               _position.cursor);
    break;
  case '#':
    while (peek() != '\n' && !isEnd(this->_position.current)) {
      this->advance();
    };
  case '"':
    _create_string();
    break;
  case '\'':
    _create_char();
    break;
  default:
    if (std::isdigit(*_navigator)) {
      _create_number();
      break;
    };

    if (std::isalpha(*_navigator) || *_navigator == '_') {
      _create_identifier();
      break;
    };
    throw std::runtime_error("Unexpected Character");
    break;
  }
  (void)this->advance();
}
