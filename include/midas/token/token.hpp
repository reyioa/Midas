#ifndef _MIDAS_MIDAS_TOKEN_TOKEN_HPP_
#define _MIDAS_MIDAS_TOKEN_TOKEN_HPP_
#include <string>
#include <unordered_map>

namespace midas {
namespace token {

enum eToken {

  TK_EOF,
  TK_Null,
  TK_Iden,
  TK_Int,
  TK_Float,
  TK_Char,
  TK_String,

  TK_Add,  //+
  TK_Sub,  //-
  TK_Mult, // *
  TK_Quo,  // /
  TK_Rem,  // %

  TK_AddAssign,  // +=
  TK_SubAssign,  // -=
  TK_MultAssign, // *=
  TK_QuoAssign,  // /=
  TK_RemAssign,  // %=

  TK_And, // &
  TK_Or,  // |
  TK_Xor, // ^
  TK_Shl, // <<
  TK_Shr, // >>

  TK_AndAssign, // &=
  TK_OrAssign,  // |=
  TK_XorAssign, // ^=
  TK_ShlAssign, // <<=
  TK_ShrAssign, // >>=

  TK_LogOr,    // ||
  TK_LogAnd,   // &&
  TK_Arrow,    // ->
  TK_BigArrow, // =>
  TK_Inc,      // ++
  TK_Dec,      // --

  TK_Equal,   // ==
  TK_Less,    // <
  TK_Greater, // >
  TK_Not,     // !

  TK_LessEqual,    // <=
  TK_GreaterEqual, // >=
  TK_NotEqual,     // !=

  TK_Assign, // =

  TK_LParen, // (
  TK_LBrack, // {
  TK_LBrace, // [

  TK_RParen, // )
  TK_RBrack, // }
  TK_RBrace, // ]

  TK_Comma,     // ,
  TK_Ellipsis,  // ...
  TK_Semicolon, // ;
  TK_Colon,     // :
  TK_Period,    // .

  // Keywords
  TK_If,   // if
  TK_Elif, // elif
  TK_Else, // else

  TK_For,   // for
  TK_While, // while
  TK_Do,    // do
  TK_In,

  TK_Switch,      // switch
  TK_Case,        // case
  TK_Break,       // break
  TK_Continue,    // continue
  TK_Default,     // default
  TK_Fallthrough, // Fallthrough

  TK_Fun,      // fun
  TK_Static,   // static
  TK_Implicit, // implicit
  TK_Explicit, // explicit
  TK_Extern,   // extern

  TK_Struct,    // struct
  TK_Interface, // interface
  TK_Enum,      // enum
  TK_Public,    // public
  TK_Private,   // private

  TK_Mutable, // mut
  TK_Const,   // const

  TK_True,  // true
  TK_False, // false

  TK_Import, // import
  TK_API,    // api
  TK_As,     // as

  // Reserved
  TK_Async, // async
  TK_Await, // await
  TK_Yield, // yield
};
struct Token {
  Token(const eToken &_token_type, const char *_txt, const int &_line,
        const int &_pos)
      : token_type(_token_type), txt(_txt), line(_line), pos(_pos) {}
  eToken token_type;
  std::string txt;
  int line;
  int pos;
};

inline std::unordered_map<std::string, eToken> get_keywords() {
  return {
      {"if", TK_If},
      {"elif", TK_Elif},
      {"else", TK_Else},

      {"for", TK_For},
      {"while", TK_While},
      {"do", TK_Do},
      {"in", TK_In},

      {"switch", TK_Switch},
      {"case", TK_Case},
      {"break", TK_Break},
      {"continue", TK_Continue},
      {"default", TK_Default},
      {"fallthrough", TK_Fallthrough},

      {"fun", TK_Fun},
      {"static", TK_Static},
      {"implicit", TK_Implicit},
      {"explicit", TK_Explicit},
      {"extern", TK_Extern},

      {"struct", TK_Struct},
      {"interface", TK_Interface},
      {"enum", TK_Enum},
      {"public", TK_Public},
      {"private", TK_Private},

      {"mut", TK_Mutable},
      {"const", TK_Const},

      {"true", TK_True},
      {"false", TK_False},

      {"import", TK_Import},
      {"api", TK_API},
      {"as", TK_As},

      // Reserved
      {"async", TK_Async},
      {"await", TK_Await},
      {"yield", TK_Yield},
  };
}

} // namespace token
} // namespace midas

#endif
