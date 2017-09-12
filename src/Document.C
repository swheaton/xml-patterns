#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"
#include "NodeList.H"

Document_Impl::Document_Impl(void) : Node_Impl("", dom::Node::DOCUMENT_NODE)
{
	Node_Impl::document	= this;
}

Document_Impl::~Document_Impl() {}

dom::Element *	Document_Impl::createElement(const std::string & tagName)
{
	return new Element_Impl(tagName, this);
}

dom::Text *	Document_Impl::createTextNode(const std::string & data)
{
	return new Text_Impl(data, this);
}

dom::Attr *	Document_Impl::createAttribute(const std::string & name)
{
	return new Attr_Impl(name, this);
}

dom::Element *	Document_Impl::createElement(const std::string & tagName)
{
	return new new Element_Impl(tagName, this);
}

dom::Element *	Document_Impl::createValidatedElement(const std::string & tagName, ValidChildren*)
{
	return new ValidationElementDecorator(new Element_Impl(tagName, this));
}

dom::Element *	Document_Impl::createValidatedDocument(ValidChildren*)
{
	return new ValidationDocumentDecorator(new Document_Impl);
}

dom::Element * Document_Impl::getDocumentElement()
{
	for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
		if (dynamic_cast<dom::Element *>(*i.operator->()) != 0)
			return dynamic_cast<dom::Element *>(*i.operator->());

	return 0;
}

std::string Document_Impl::toString()
{
	std::string outString = "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
	outString += this->getDocumentElement()->toString();
	return outString;
}

DocumentDecorator::DocumentDecorator(dom::Document * document) :
	decoratedDocument(document) {}

dom::Node * DocumentDecorator::appendChild(dom::Element * newChild)
{
	return decoratedDocument->appendChild(newChild);
}

dom::DOMException ValidationDocumentDecorator::makeValidationException()
{
	return dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
								"Invalid against given schema");	
}

ValidationDocumentDecorator::ValidationDocumentDecorator(dom::Document * document, XMLValidator* _validator) :
	DocumentDecorator(document),
	validator(_validator) {}
dom::Node * ValidationDocumentDecorator::appendChild(dom::Element * newChild)
{
	// Do validation here
	if (!validator.canRootElement(newChild->getTagName()))
	{
		
		throw ValidationDocumentDecorator::makeValidationException();
	}
	return DocumentDecorator::appendChild(newChild);
}