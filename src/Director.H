#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include "XMLTokenizer.H"

class Builder;

class Director
{
private:
	class State
	{
	public:
		virtual State *	processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
		  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder)	= 0;
	};

	class BeforeProlog : public State
	{
	public:
		virtual State *	processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
		  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder);
	};

	class AfterProlog : public State
	{
	public:
		virtual State *	processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
		  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder);
	};

	class ParsingElement : public State
	{
	public:
		virtual State *	processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
		  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder);
	};

	class InNonnullElement : public State
	{
	public:
		virtual State *	processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
		  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder);
	};

	class End : public State
	{
	public:
		virtual State *	processToken(XMLTokenizer::XMLToken * token, XMLTokenizer::XMLToken::TokenTypes lastToken,
		  XMLTokenizer::XMLToken::TokenTypes currentToken, Builder * builder);
	};
public:
	Director(const std::string & filename, Builder * builder);
};

#endif // DIRECTOR_H
