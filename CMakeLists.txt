cmake_minimum_required(VERSION 3.12)
project(XmlParser)

set(CMAKE_CXX_STANDARD 17)
add_library(XmlParser XmlTextType.h XmlTokenType.h XmlAttribute.cpp XmlAttribute.h XmlElement.cpp XmlElement.h XmlDocument.cpp XmlDocument.h)
add_executable(TestXmlParser XmlTextType.h XmlTokenType.h XmlAttribute.cpp XmlAttribute.h XmlElement.cpp XmlElement.h XmlDocument.cpp XmlDocument.h TestXmlParser.cpp)