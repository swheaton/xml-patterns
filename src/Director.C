#include "Director.H"
#include "Builder.H"

Director::Director(const std::string & filename, Builder * builder)
{
	XMLTokenizer				tokenizer(filename);
	State *					documentLocation	= new BeforeProlog;
	XMLTokenizer::XMLToken::TokenTypes	lastToken		= XMLTokenizer::XMLToken::NULL_TOKEN;
	XMLTokenizer::XMLToken::TokenTypes	currentToken		= XMLTokenizer::XMLToken::NULL_TOKEN;
	XMLTokenizer::XMLToken *		token			= 0;

	do
	{
		token		= tokenizer.getNextToken();
		currentToken	= token->getTokenType();
		documentLocation= documentLocation->processToken(token, lastToken, currentToken, builder);
		lastToken	= currentToken;

		if (token != 0)
			delete token;
	} while(currentToken != XMLTokenizer::XMLToken::NULL_TOKEN);

	delete documentLocation;
}

Director::State * Director::BeforeProlog::processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder)
{
	State *	documentLocation	= this;

	switch(lastToken)
	{
	case XMLTokenizer::XMLToken::NULL_TOKEN:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::PROLOG_START:
			builder->createProlog();
			delete documentLocation;
			documentLocation	= new AfterProlog;
			break;
		default:
			break;
		}
	default:
		// Shouldn't be able to get here.
		break;
	}

	return documentLocation;
}

Director::State * Director::AfterProlog::processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder)
{
	State *	documentLocation	= this;

	switch(lastToken)
	{
	case XMLTokenizer::XMLToken::PROLOG_START:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
			builder->identifyProlog(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::PROLOG_END:
			builder->endProlog();
			delete documentLocation;
			documentLocation	= new ParsingElement;
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			builder->valueAttribute(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::PROLOG_END:
			builder->endProlog();
			delete documentLocation;
			documentLocation	= new ParsingElement;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return documentLocation;
}

Director::State * Director::ParsingElement::processToken(XMLTokenizer::XMLToken * token,
  XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder)
{
	State *	documentLocation	= this;

	switch(lastToken)
	{
	case XMLTokenizer::XMLToken::TAG_START:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ELEMENT:
			builder->createElement(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ELEMENT:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_END:
			delete documentLocation;
			documentLocation	= new InNonnullElement;
			builder->pushElement();
			break;
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			builder->valueAttribute(token->getToken());
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			builder->createAttribute(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_END:
			delete documentLocation;
			documentLocation	= new InNonnullElement;
			builder->pushElement();
			break;
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::PROLOG_END:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_START:
			// Actually create element when we read tag name.
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::NULL_TAG_END:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_START:
			// Actually create element when we read tag name.
			break;
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			delete documentLocation;
			documentLocation	= new InNonnullElement;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return documentLocation;
}

Director::State * Director::InNonnullElement::processToken(XMLTokenizer::XMLToken * token,
  XMLTokenizer::XMLToken::TokenTypes lastToken, XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder)
{
	State *	documentLocation	= this;

	switch(lastToken)
	{
	case XMLTokenizer::XMLToken::ELEMENT:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_END:
			if (!builder->popElement())
			{
				delete documentLocation;
				documentLocation	= new End;
			}
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::TAG_END:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_START:
			delete documentLocation;
			documentLocation	= new ParsingElement;
			// Actually create element when we read tag name.
			break;
		case XMLTokenizer::XMLToken::VALUE:
			builder->addValue(token->getToken());
			break;
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			break;
		default:
			break;
		}
		break;
	case XMLTokenizer::XMLToken::VALUE:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			break;
		default:
			break;
		}
	case XMLTokenizer::XMLToken::TAG_CLOSE_START:
		switch(currentToken)
		{
		case XMLTokenizer::XMLToken::ELEMENT:
			builder->confirmElement(token->getToken());
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return documentLocation;
}

Director::State * Director::End::processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder)
{
	State *	documentLocation	= this;

	switch(currentToken)
	{
	case XMLTokenizer::XMLToken::NULL_TOKEN:
		break;
	default:
		break;
	}

	return documentLocation;
}
