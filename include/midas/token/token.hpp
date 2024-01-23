#ifndef _MIDAS_MIDAS_TOKEN_TOKEN_HPP_
#define _MIDAS_MIDAS_TOKEN_TOKEN_HPP_
#include <string>
#include <unordered_map>

namespace midas {
namespace midas {
namespace token {

enum eToken {

  kEOF,
  kNull,
  kIden,
  kInt,
  kFloat,
  kChar,
  kString,

  kAdd,  //+
  kSub,  //-
  kMult, // *
  kQuo,  // /
  kRem,  // %

  kAddAssign,  // +=
  kSubAssign,  // -=
  kMultAssign, // *=
  kQuoAssign,  // /=
  kRemAssign,  // %=

  kAnd, // &
  kOr,  // |
  kXor, // ^
  kShl, // <<
  kShr, // >>

  kAndAssign, // &=
  kOrAssign,  // |=
  kXorAssign, // ^=
  kShlAssign, // <<=
  kShrAssign, // >>=

  kLogOr,    // ||
  kLogAnd,   // &&
  kArrow,    // ->
  kBigArrow, // =>
  kInc,      // ++
  kDec,      // --

  kEqual,   // ==
  kLess,    // <
  kGreater, // >
  kNot,     // !

  kLessEqual,    // <=
  kGreaterEqual, // >=
  kNotEqual,     // !=

  kAssign, // =

  kLParen, // (
  kLBrack, // {
  kLBrace, // [

  kRParen, // )
  kRBrack, // }
  kRBrace, // ]

  kComma,     // ,
  kEllipsis,  // ...
  kSemicolon, // ;
  kColon,     // :
  kPeriod,    // .

  // Keywords
  kIf,   // if
  kElif, // elif
  kElse, // else

  kFor,   // for
  kWhile, // while
  kDo,    // do
  kIn,

  kSwitch,      // switch
  kCase,        // case
  kBreak,       // break
  kContinue,    // continue
  kDefault,     // default
  kFallthrough, // Fallthrough

  kFun,      // fun
  kStatic,   // static
  kImplicit, // implicit
  kExplicit, // explicit
  kExtern,   // extern

  kStruct,    // struct
  kInterface, // interface
  kEnum,      // enum
  kPublic,    // public
  kPrivate,   // private

  kMutable, // mut
  kConst,   // const

  kTrue,  // true
  kFalse, // false

  kImport, // import
  kAPI,    // api
  kAs,     // as

  // Reserved
  kAsync, // async
  kAwait, // await
  kYield, // yield
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
      {"if", kIf},
      {"elif", kElif},
      {"else", kElse},

      {"for", kFor},
      {"while", kWhile},
      {"do", kDo},
      {"in", kIn},

      {"switch", kSwitch},
      {"case", kCase},
      {"break", kBreak},
      {"continue", kContinue},
      {"default", kDefault},
      {"fallthrough", kFallthrough},

      {"fun", kFun},
      {"static", kStatic},
      {"implicit", kImplicit},
      {"explicit", kExplicit},
      {"extern", kExtern},

      {"struct", kStruct},
      {"interface", kInterface},
      {"enum", kEnum},
      {"public", kPublic},
      {"private", kPrivate},

      {"mut", kMutable},
      {"const", kConst},

      {"true", kTrue},
      {"false", kFalse},

      {"import", kImport},
      {"api", kAPI},
      {"as", kAs},

      // Reserved
      {"async", kAsync},
      {"await", kAwait},
      {"yield", kYield},
  };
}

} // namespace token
} // namespace midas
} // namespace midas

#endif
