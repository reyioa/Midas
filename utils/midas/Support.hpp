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
#ifndef _MIDAS_UTILS_SUPPORT_HPP_
#define _MIDAS_UTILS_SUPPORT_HPP_
#include <typeinfo>
namespace midas {

template <typename T, typename K> inline bool instanceof (const K &value) {
  return typeid(T).hash_code() == typeid(K).hash_code();
}

} // namespace midas
#endif
