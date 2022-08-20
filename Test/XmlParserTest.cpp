//
// Created by Olcay Taner YILDIZ on 24.05.2022.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/XmlDocument.h"

TEST_CASE("XmlParserTest") {
    auto* doc = new XmlDocument("test.xml");
    doc->parse();
    XmlElement* root = doc->getFirstChild();
    REQUIRE("frameset" == root->getName());
    XmlElement* firstChild = root->getFirstChild();
    REQUIRE("role" == firstChild->getName());
    REQUIRE("ali veli \"deneme yapmak\" = anlamında > bir deyim" == firstChild->getPcData());
    XmlElement* secondChild = firstChild->getNextSibling();
    REQUIRE("perceiver, alien \"x3\" to whom?" == secondChild->getAttributeValue("descr"));
    REQUIRE("PAG" == secondChild->getAttributeValue("f"));
    REQUIRE("2" == secondChild->getAttributeValue("n"));
}
