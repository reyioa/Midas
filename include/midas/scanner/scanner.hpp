#ifndef _MIDAS_SCANNER_SCANNER_HPP_
#define _MIDAS_SCANNER_SCANNER_HPP_

#include "../token/token.hpp"
#include "file.hpp"
#include <cstring>
#include <vector>
namespace midas {
namespace scanner {

struct Position {
  int line;
  int cursor;
  int current;
};

class Scanner {
public:
  Scanner(const char *data) : _data(data), _navigator(data) {
    _file = {};
    _position = {1, 0, 0};
    _tokens = {};
  };
  const Position getPosition() const { return _position; };
  const File getFile() const { return _file; };
  std::vector<token::Token> scanTokens();
  std::vector<token::Token> getTokens() const { return _tokens; };

private:
  void _scanToken();
  void _createString();
  void _createNumber();
  void _createIdentifier();
  void _createChar();

  File _file;
  Position _position;
  const char *_data;
  const char *_navigator = _data;
  std::vector<token::Token> _tokens;

  inline const bool isEnd(const int &pos) const {
    return pos >= std::strlen(_data);
  };

  inline char peek() {
    if (isEnd(this->_position.current + 1)) {
      return '\0';
    }

    return *(_navigator + 1);
  };
  inline char peek_next() {
    if (isEnd(this->_position.current + 2)) {
      return '\0';
    }

    return *(_navigator + 2);
  };

  inline char advance() {
    if (isEnd(this->_position.current)) {
      return '\0';
    }
    ++this->_navigator;
    ++this->_position.current;
    ++this->_position.cursor;
    return *this->_navigator;
  };

  inline bool match(const char &expected) {
    if (isEnd(this->_position.current + 1)) {
      return false;
    }
    if (*(this->_navigator + 1) != expected) {
      return false;
    }
    ++this->_navigator;
    ++this->_position.current;
    ++this->_position.cursor;
    return true;
  }
};

} // namespace scanner
} // namespace midas
#endif
