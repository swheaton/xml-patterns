#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void XMLSerializer::serializePretty(void)
{
	delete whitespace;
	whitespace	= new PrettyWhitespaceStrategy;
}

void XMLSerializer::serializeMinimal(void)
{
	delete whitespace;
	whitespace	= new MinimalWhitespaceStrategy;
}

void XMLSerializer::VisitDocument(dom::Document * document)
{
	*file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
	whitespace->newLine(file);
	document->getDocumentElement()->Accept(this);
}

void XMLSerializer::VisitElement(dom::Element * element)
{
	whitespace->prettyIndentation(file);
	*file << "<" << element->getTagName();

	int	attrCount	= 0;

	for (dom::NamedNodeMap::iterator i = element->getAttributes()->begin(); i != element->getAttributes()->end(); i++)
	{
		(*i)->Accept(this);
		attrCount++;
	}

	if (attrCount > 0)
		*file << " ";

	if (element->getChildNodes()->size() == 0)
	{
		*file << "/>";
		whitespace->newLine(file);
	}
	else
	{
		*file << ">";
		whitespace->newLine(file);
		whitespace->incrementIndentation();

		for (dom::NodeList::iterator i = element->getChildNodes()->begin(); i != element->getChildNodes()->end(); i++)
			if (dynamic_cast<dom::Element *>(*i) != 0 || dynamic_cast<dom::Text *>(*i) != 0)
				(*i)->Accept(this);

		whitespace->decrementIndentation();
		whitespace->prettyIndentation(file);
		*file << "</" << element->getTagName() + ">";
		whitespace->newLine(file);
	}
}

void XMLSerializer::VisitAttribute(dom::Attr * attr)
{
	*file << " " << attr->getName() << "=\"" << attr->getValue() << "\"";
}

void XMLSerializer::VisitText(dom::Text * text)
{
	whitespace->prettyIndentation(file);
	*file << text->getData();
	whitespace->newLine(file);
}
