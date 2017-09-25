
#ifndef XML_BUILDER_H
#define XML_BUILDER_H
class XMLBuilder
{
public:
  void beginDocument();
  void endDocument();
  void newElement();
  void closeElement();
  void newAttribute();
  Node * getDOM();
};

class XMLParser
{
private:
  XMLBuilder * builder;
public:
  XMLParser(XMLBuilder* builder) : 
    builder(builder);
  ~XMLParser() {if (builder != 0) delete builder;}

  Node * parseFile(std::string fileName);
  {
    XMLTokenizer	tokenizer(fileName);

	XMLTokenizer::XMLToken *	token	= 0;

	do
	{
	    if (token != 0)
	    {
		  delete	token;
         }
		token	= tokenizer.getNextToken();
		std::string attrName = "";
		switch (token->getTokenType())
        {
		  case XMLTokenizer::XMLToken::NULL_TOKEN:
		  	     break;
		  case XMLTokenizer::XMLToken::PROLOG_START:
		  	     break;
		  case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
		  	     builder->beginDocument();
		  	     break;
		  case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
		  	     builder->addAttribute(attrName, token->getToken());
                  attrName = "";
		  	     break;
		  case XMLTokenizer::XMLToken::PROLOG_END:
		  	     break;
		  case XMLTokenizer::XMLToken::TAG_START:
		  	     break;
		  case XMLTokenizer::XMLToken::ELEMENT:
		  	     break;
		  case XMLTokenizer::XMLToken::ATTRIBUTE:
		  	     attrName = token->getToken();
		  	     break;				   				   				   				   				   				   				 	     					        
		  case XMLTokenizer::XMLToken::NULL_TAG_END:
		  	     break;
		  case XMLTokenizer::XMLToken::TAG_CLOSE_START:
		  	     break;
		  case XMLTokenizer::XMLToken::VALUE:
		  	     break;
		  case XMLTokenizer::XMLToken::TAG_END:
		  	     break;
          default:
            break;
        }
	} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);
    builder->endDocument();
	delete	token;
  }
};
#endif // XML_BUILDER_H