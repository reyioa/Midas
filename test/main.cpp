#include "midas/scanner/scanner.hpp"
#include "midas/token/token.hpp"
#include <iostream>
#include <stdexcept>

int main() {
  try {
    midas::scanner::Scanner s(
        "fun main() -> string {if (true) {\n return \"Hello World\"\n} else "
        "{\n return \"Why\"");
    s.scanTokens();
    auto _tokens = s.get_tokens();
    for (const auto &t : _tokens) {
      std::cout << t.token_type << '\t' << t.pos << '\t' << t.line << '\t'
                << t.txt << '\n';
    }
  } catch (const std::runtime_error &e) {
    std::cout << e.what() << '\n';
  }
}
