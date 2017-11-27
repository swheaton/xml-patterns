#include "Visitor.H"

#include "Attr.H"
#include "Element.H"
#include "Text.H"
#include "Document.H"
#include "XMLSerializer.H"

void SerializeVisitor::visitAttr(dom::Attr* attr)
{
    *writer << " " << attr->getName() << "=\"" << attr->getValue() << "\"";
}
void SerializeVisitor::visitDocument(dom::Document* doc)
{
	*writer << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    whitespace->newLine(writer);
    doc->getDocumentElement()->accept(*this);
}
void SerializeVisitor::visitElement(dom::Element* elt)
{
    whitespace->prettyIndentation(writer);
	*writer << "<" << elt->getTagName();

	int	attrCount	= 0;

	for (dom::NamedNodeMap::iterator i = elt->getAttributes()->begin(); i != elt->getAttributes()->end(); i++)
	{
		(*i)->accept(*this);
		attrCount++;
	}

	if (attrCount > 0)
		*writer << " ";

	if (elt->getChildNodes()->size() == 0)
	{
		*writer << "/>";
		whitespace->newLine(writer);
	}
	else
	{
		*writer << ">";
		whitespace->newLine(writer);
		whitespace->incrementIndentation();

		for (dom::NodeList::iterator i = elt->getChildNodes()->begin(); i != elt->getChildNodes()->end(); i++)
			if (dynamic_cast<dom::Element *>(*i) != 0 || dynamic_cast<dom::Text *>(*i) != 0)
				(*i)->accept(*this);

		whitespace->decrementIndentation();
		whitespace->prettyIndentation(writer);
		*writer << "</" << elt->getTagName() + ">";
		whitespace->newLine(writer);
	}
}
void SerializeVisitor::visitText(dom::Text* t)
{
	whitespace->prettyIndentation(writer);
	*writer << t->getData();
	whitespace->newLine(writer);
}