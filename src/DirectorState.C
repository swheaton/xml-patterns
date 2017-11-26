#include "DirectorState.H"

void DirectorState::changeState(Director* director, DirectorState* state)
{
    director->changeState(state);
}

void InsideElement::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_END)
    {
        if (!builder->popElement())
			changeState(director, &End::getInstance());
    }
}

void NonnullElement::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_START)
    {
        // Actually create element when we read tag name.
        changeState(director, &ParseElement::getInstance());
    }
    else if (token->getTokenType() == XMLTokenizer::XMLToken::VALUE)
    {
        builder->addValue(token->getToken());
        changeState(director, &ElementValue::getInstance());
    }
    else if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_CLOSE_START)
    {
        changeState(director, &ElementTagCloseStart::getInstance());
    }
}

void NullTagEnd::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_START)
    {
        // Actually create element when we read tag name.
        changeState(director, &ParseElement::getInstance());
    }
    else if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_CLOSE_START)
    {
        changeState(director, &ElementTagCloseStart::getInstance());
    }
}

void PrologAttribute::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::ATTRIBUTE_VALUE)
    {
     	builder->valueAttribute(token->getToken());
     	changeState(director, &PrologIdentifier::getInstance());
    }
}

void ParseAttribute::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::ATTRIBUTE_VALUE)
    {
        builder->valueAttribute(token->getToken());
        changeState(director, &ParseElement::getInstance());
    }
}

void ParseElement::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::ATTRIBUTE)
    {
        builder->createAttribute(token->getToken());
        changeState(director, &ParseAttribute::getInstance());
    }
    else if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_END)
    {
        builder->pushElement();
        changeState(director, &NonnullElement::getInstance());
    }
    else if (token->getTokenType() == XMLTokenizer::XMLToken::NULL_TAG_END)
    {
        changeState(director, &NullTagEnd::getInstance());
    }
}

void TagStart::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::ELEMENT)
    {
        builder->createElement(token->getToken());
        changeState(director, &ParseElement::getInstance());
    }
}

void AfterProlog::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_START)
    {
        // Actually create element when we read tag name.
        changeState(director, &TagStart::getInstance());
    }
}

void PrologIdentifier::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::ATTRIBUTE)
    {
        builder->createAttribute(token->getToken());
        changeState(director, &PrologAttribute::getInstance());
    }
    else if (token->getTokenType() == XMLTokenizer::XMLToken::PROLOG_END)
    {
        builder->endProlog();
        changeState(director, &AfterProlog::getInstance());
    }
}

void PrologStart::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::PROLOG_IDENTIFIER)
    {
		builder->identifyProlog(token->getToken());
		changeState(director, &PrologIdentifier::getInstance());
    }
}

void BeforePrologState::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::PROLOG_START)
    {
		builder->createProlog();
		changeState(director, &PrologStart::getInstance());
    }
}

void ElementValue::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::TAG_CLOSE_START)
    {
        changeState(director, &ElementTagCloseStart::getInstance());
    }
}

void ElementTagCloseStart::parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
{
    if (token->getTokenType() == XMLTokenizer::XMLToken::ELEMENT)
    {
        builder->confirmElement(token->getToken());
        changeState(director, &InsideElement::getInstance());
    }
}