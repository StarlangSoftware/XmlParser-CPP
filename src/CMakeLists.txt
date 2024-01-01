cmake_minimum_required(VERSION 3.12)
project(XmlParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

add_library(XmlParser XmlTextType.h XmlTokenType.h XmlAttribute.cpp XmlAttribute.h XmlElement.cpp XmlElement.h XmlDocument.cpp XmlDocument.h)
