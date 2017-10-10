#include "Text.H"
#include <stdexcept>

dom::Text::Text(const std::string value, dom::Document * document) : dom::Node("", dom::Node::TEXT_NODE), textImpl(new Text_Impl(value, document)) {}

void dom::Text::serialize(std::fstream * writer, WhitespaceStrategy * whitespace)	{textImpl->serialize(writer, whitespace); }

const std::string &	dom::Text::getName(void)							{textImpl->getName(); }
const std::string &	dom::Text::getData(void)							{textImpl->getData(); }
const std::string &	dom::Text::getValue(void)							{textImpl->getValue(); }
void			dom::Text::setData(const std::string & value)				{textImpl->setData(value); }
void			dom::Text::setValue(const std::string & value)				{textImpl->setValue(value); }
int			dom::Text::getLength(void)							{textImpl->getLength(); }
const std::string &	dom::Text::substringData(int offset, int count)				{textImpl->substringData(offset, count); }
void			dom::Text::appendData(const std::string & arg)				{textImpl->appendData(arg); }
void			dom::Text::insertData(int offset, const std::string & arg)			{textImpl->insertData(offset, arg); }
void			dom::Text::deleteData(int offset, int count)				{textImpl->deleteData(offset, count); }
void			dom::Text::replaceData(int offset, int count, const std::string & arg)	{textImpl->replaceData(offset, count, arg); }
dom::Text *			dom::Text::splitText(int offset)						{textImpl->splitText(offset); }

dom::Text_Impl::Text_Impl(const std::string value, dom::Document * document) : Node_Impl("", dom::Node::TEXT_NODE)
{
	Node_Impl::document	= document;
}

dom::Text_Impl::~Text_Impl()
{
}

void dom::Text_Impl::serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
{
	whitespace->prettyIndentation(writer);
	*writer << getData();
	whitespace->newLine(writer);
}

const std::string &	dom::Text_Impl::getName(void)
{
	return getNodeName();
}

const std::string &	dom::Text_Impl::getData(void)
{
	return getNodeValue();
}

const std::string &	dom::Text_Impl::getValue(void)
{
	return getData();
}

void			dom::Text_Impl::setData(const std::string & value)
{
	setNodeValue(value);
}

void			dom::Text_Impl::setValue(const std::string & value)
{
	setNodeValue(value);
}

int			dom::Text_Impl::getLength(void)
{
	return getValue().size();
}

const std::string &	dom::Text_Impl::substringData(int offset, int count)
{
	try
	{
		const std::string &	value	= getValue().substr(offset, count);

		return value;
	}
	catch (std::out_of_range &)
	{
		throw dom::DOMException(dom::DOMException::INDEX_SIZE_ERR, "Index larger than Text node's value.");
	}
}

void			dom::Text_Impl::appendData(const std::string & arg)
{
	std::string	value	= getValue();

	setValue(value.append(arg));
}

void			dom::Text_Impl::insertData(int offset, const std::string & arg)
{
	std::string	value	= getValue();

	setValue(value.insert(offset, arg));
}

void			dom::Text_Impl::deleteData(int offset, int count)
{
	std::string	value	= getValue();

	setValue(value.erase(offset, count));
}

void			dom::Text_Impl::replaceData(int offset, int count, const std::string & arg)
{
	std::string	value	= getValue();

	setValue(value.erase(offset, count).insert(offset, arg));
}

dom::Text *		dom::Text_Impl::splitText(int offset)
{
	try
	{
		dom::Text *	text	= new Text(substringData(offset, getLength() - offset), document);

		setValue(substringData(0, offset));

		if (getParentNode() != 0)
			insertBefore(text, getNextSibling());

		return text;
	}
	catch (std::out_of_range &)
	{
		throw dom::DOMException(dom::DOMException::INDEX_SIZE_ERR, "Index larget than Text node's value.");
	}
}
