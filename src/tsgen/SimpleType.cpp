#include <sstream>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <tinyxml2.h>
#include "SimpleType.h"
#include "../xmlparse/XMLElementNameToCamelCaseConverter.h"
#include "../xmlparse/MissingXMLAttributeException.h"

const std::string NAME = "name";

namespace tsgen {
  template<typename T>
  SimpleType<T>::SimpleType(
      const xmlparse::XMLElement &simpleTypeElement
  ) {

    auto nameAttr = simpleTypeElement.findAttribute(NAME);
    if (nameAttr == nullptr) {
      throw xmlparse::MissingXMLAttributeException(NAME);
    }
    auto rawName = std::string(nameAttr->value().value());
    this->name_ = xmlparse::XMLElementNameToCamelCaseConverter(rawName).getCamelCaseName();

    auto restrictionElement = simpleTypeElement.firstChildElement("xs:restriction");
    auto restriction = restrictionElement->findAttribute("base");
    auto restrictionValue = restriction->value();

    if (restrictionValue == "xs:string") {
      this->type_ = "string";
    } else {
      this->type_ = "number";
    }
  }

  template<typename T>
  std::string SimpleType<T>::toTypescriptDefinition() const {
    std::stringstream tsDefBuilder;
    tsDefBuilder << "type "
                 << this->name_
                 << " = "
                 << this->type_
                 << ";";

    return tsDefBuilder.str();
  }
}

