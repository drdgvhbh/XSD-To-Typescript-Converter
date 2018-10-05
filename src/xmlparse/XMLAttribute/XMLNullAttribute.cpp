#include "XMLNullAttribute.h"

namespace xmlparse {
  std::optional<std::string> XMLNullAttribute::value() const {
    return std::nullopt;
  }

  bool XMLNullAttribute::hasValue() const {
    return false;
  }
}
