#include "Command.H"

void ParseFileCommand::execute()
{
    dom::Document *	document	= new Document_Impl;
    Builder		builder(document);

	Director	director(fileName, &builder);
	rootNode = document;
}

void SerializeCommand::execute()
{
    XMLSerializer	xmlSerializer(file);
    xmlSerializer.serializePretty(node);
}

void AddAttributeCommand::execute()
{
    node->setAttribute(attrName, attrValue);
}