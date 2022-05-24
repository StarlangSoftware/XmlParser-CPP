cmake_minimum_required(VERSION 3.12)
project(XmlParser)

set(CMAKE_CXX_STANDARD 20)

add_library(XmlParser XmlTextType.h XmlTokenType.h XmlAttribute.cpp XmlAttribute.h XmlElement.cpp XmlElement.h XmlDocument.cpp XmlDocument.h)

add_executable(Test XmlTextType.h XmlTokenType.h XmlAttribute.cpp XmlAttribute.h XmlElement.cpp XmlElement.h XmlDocument.cpp XmlDocument.h Test/catch.hpp Test/XmlParserTest.cpp)