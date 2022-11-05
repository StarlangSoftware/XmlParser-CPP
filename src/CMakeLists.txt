cmake_minimum_required(VERSION 3.12)
project(XmlParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(XmlParser src/XmlTextType.h src/XmlTokenType.h src/XmlAttribute.cpp src/XmlAttribute.h src/XmlElement.cpp src/XmlElement.h src/XmlDocument.cpp src/XmlDocument.h)

add_executable(Test src/XmlTextType.h src/XmlTokenType.h src/XmlAttribute.cpp src/XmlAttribute.h src/XmlElement.cpp src/XmlElement.h src/XmlDocument.cpp src/XmlDocument.h Test/catch.hpp Test/XmlParserTest.cpp)