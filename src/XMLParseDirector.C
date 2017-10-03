#include "XMLParseDirector.H"
#include "XMLTokenizer.H"

dom::Document * XMLParseDirector::parseFile(const std::string& fileName)
{
	XMLTokenizer	tokenizer(fileName);

	XMLTokenizer::XMLToken *	token	= 0;
	dom::Document * document = 0;
	dom::Element * currElt = 0;
	bool done = false;
	std::string eltName = "";

	do
	{
		if (token != 0)
		{
			delete	token;
		}
		token	= tokenizer.getNextToken();

		// Director just begins document and adds root element, that's all
		switch (token->getTokenType())
		{
			case XMLTokenizer::XMLToken::PROLOG_END:
				document = XMLBuilder::getInstance()->beginDocument();
				break;

				// Add root element to start, but nothing else
			case XMLTokenizer::XMLToken::ELEMENT:
				eltName = token->getToken();
				break;

			case XMLTokenizer::XMLToken::TAG_END:
				XMLBuilder::getInstance()->addElement(document, eltName, fileName, tokenizer.getFileOffset());
				done = true;
				break;

			default:
				break;
		}
	} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN && !done);
	delete	token;
	return document;
}
