#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void XMLSerializer::serializePretty(dom::Node * node)
{
	node->setPrettyPrintStrategy();
	file << node->toString();
}

void XMLSerializer::serializeMinimal(dom::Node * node)
{
	node->setMinimalPrintStrategy();
	file << node->toString();
}
