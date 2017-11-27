#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

#include "Visitor.H"

void XMLSerializer::serializePretty(dom::Node * node)
{
	WhitespaceStrategy *	ws	= new PrettyWhitespaceStrategy;
	SerializeVisitor visitor(file, ws);
	node->accept(visitor);
	delete ws;
}

void XMLSerializer::serializeMinimal(dom::Node * node)
{
	WhitespaceStrategy *	ws	= new MinimalWhitespaceStrategy;
	SerializeVisitor visitor(file, ws);
	node->accept(visitor);
	delete ws;
}
