#ifndef XML_PARSE_DIRECTOR_H
#define XML_PARSE_DIRECTOR_H

#include "Document.H"
#include "XMLBuilder.H"

// Director for XML Parsing and DOM building. Uses builder passed to it
class XMLParseDirector
{
private:
  XMLBuilder * builder;
public:
  XMLParseDirector(){}
  ~XMLParseDirector() {}

  dom::Document * parseFile(const std::string& fileName);
};

#endif