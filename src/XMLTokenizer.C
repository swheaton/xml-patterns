#include "XMLTokenizer.H"
#include <boost/cregex.hpp>

const char *	XMLTokenizer::PROLOG_START	= "<\\?";
const char *	XMLTokenizer::PROLOG_IDENTIFIER	= "[[:space:]]*xml";
const char *	XMLTokenizer::ATTRIBUTE_VALUE	= "\"[^\"]*\"";
const char *	XMLTokenizer::PROLOG_END	= "[[:space:]]*\\?>";
const char *	XMLTokenizer::TAG_START		= "[[:space:]]*<";
const char *	XMLTokenizer::ELEMENT		= "[[:space:]]*[[:alpha:]]([[:alnum:]_-]|:)*";
const char *	XMLTokenizer::ATTRIBUTE		= "[[:space:]]+[[:alpha:]]([[:alnum:]_-]|:)*[[:space:]]*=";
const char *	XMLTokenizer::NULL_TAG_END	= "[[:space:]]*/>";
const char *	XMLTokenizer::TAG_CLOSE_START	= "[[:space:]]*</";
const char *	XMLTokenizer::VALUE		= "[^<]*";
const char *	XMLTokenizer::TAG_END		= "[[:space:]]*>";
const char *	XMLTokenizer::SPACE_TO_EOL	= "[[:space:]]*";

XMLTokenizer::XMLToken::XMLToken(const std::string & t, TokenTypes tt) : token(t), token_type(tt) {}

const char *	XMLTokenizer::XMLToken::toString(void)
{
	switch(token_type)
	{
	case NULL_TOKEN:
		return "NULL";
	case PROLOG_START:
		return "PROLOG_START";
	case PROLOG_IDENTIFIER:
		return "PROLOG_IDENTIFIER";
	case ATTRIBUTE_VALUE:
		return "ATTRIBUTE_VALUE";
	case PROLOG_END:
		return "PROLOG_END";
	case TAG_START:
		return "TAG_START";
	case ELEMENT:
		return "ELEMENT";
	case ATTRIBUTE:
		return "ATTRIBUTE";
	case NULL_TAG_END:
		return "NULL_TAG_END";
	case TAG_CLOSE_START:
		return "TAG_CLOSE_START";
	case VALUE:
		return "VALUE";
	case TAG_END:
		return "TAG_END";
	default:
		return "NULL";
	}
}

XMLTokenizer::XMLTokenizer(const std::string & filename) :
  file(filename.c_str(), std::ios_base::in),
  line_number(0),
  index(0),
  inside_tag(false),
  prolog_start(PROLOG_START),
  prolog_identifier(PROLOG_IDENTIFIER),
  attribute_value(ATTRIBUTE_VALUE),
  prolog_end(PROLOG_END),
  tag_start(TAG_START),
  element(ELEMENT),
  attribute(ATTRIBUTE),
  null_tag_end(NULL_TAG_END),
  tag_close_start(TAG_CLOSE_START),
  value(VALUE),
  tag_end(TAG_END),
  space_to_eol(SPACE_TO_EOL)
{
}

XMLTokenizer::XMLToken *	XMLTokenizer::getNextToken(void)
{
	if (line.size() == 0)
	{
		std::getline(file, line);
		index	= 0;
		line_number++;

		if (line.size() == 0)
			return new XMLToken(std::string(""), XMLToken::NULL_TOKEN);
	}

	if (prolog_start.Search(line) && prolog_start.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, prolog_start.Length()), XMLToken::PROLOG_START);
		inside_tag		= true;
		update_matchers(prolog_start);
		return	token;
	}

	if (prolog_end.Search(line) && prolog_end.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, prolog_end.Length()), XMLToken::PROLOG_END);
		inside_tag		= false;
		update_matchers(prolog_end);
		return	token;
	}

	if (tag_close_start.Search(line) && tag_close_start.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, tag_close_start.Length()), XMLToken::TAG_CLOSE_START);
		inside_tag		= true;
		update_matchers(tag_close_start);
		return	token;
	}

	if (tag_start.Search(line) && tag_start.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, tag_start.Length()), XMLToken::TAG_START);
		inside_tag		= true;
		update_matchers(tag_start);
		return	token;
	}

	if (tag_end.Search(line) && tag_end.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, tag_end.Length()), XMLToken::TAG_END);
		inside_tag		= false;
		update_matchers(tag_end);
		return	token;
	}

	if (null_tag_end.Search(line) && null_tag_end.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, null_tag_end.Length()), XMLToken::NULL_TAG_END);
		inside_tag		= false;
		update_matchers(null_tag_end);
		return	token;
	}

	if (inside_tag)
	{
		if (attribute.Search(line) && attribute.Position() == 0)
		{
			XMLToken *	token	= new XMLToken(line.substr(0, attribute.Length()), XMLToken::ATTRIBUTE);
			update_matchers(attribute);
			return	token;
		}

		if (attribute_value.Search(line) && attribute_value.Position() == 0)
		{
			XMLToken *	token	= new XMLToken(line.substr(0, attribute_value.Length()), XMLToken::ATTRIBUTE_VALUE);
			update_matchers(attribute_value);
			return	token;
		}

		if (prolog_identifier.Search(line) && prolog_identifier.Position() == 0)
		{
			XMLToken * token = new XMLToken(line.substr(0, prolog_identifier.Length()), XMLToken::PROLOG_IDENTIFIER);
			update_matchers(prolog_identifier);
			return	token;
		}

		if (element.Search(line) && element.Position() == 0)
		{
			XMLToken *	token	= new XMLToken(line.substr(0, element.Length()), XMLToken::ELEMENT);
			update_matchers(element);
			return	token;
		}

	}
	if (value.Search(line) && value.Position() == 0)
	{
		XMLToken *	token	= new XMLToken(line.substr(0, value.Length()), XMLToken::VALUE);
		update_matchers(value);
		return	token;
	}

	if (space_to_eol.Search(line) && space_to_eol.Position() == 0)
	{
		update_matchers(space_to_eol);
		return	getNextToken();
	}

	return new XMLToken(std::string(""), XMLToken::NULL_TOKEN);
}

void		XMLTokenizer::update_matchers(boost::RegEx & matcher)
{
	if (matcher.Length() >= line.size())
	{
		line.clear();
		return;
	}

	line	= line.substr(matcher.Length());
	index	+= matcher.Length();
}
