#include "Facade.H"

#include <fstream>
#include <ios>
#include <stdio.h>
#include <iostream>

#include "XMLSerializer.H"
#include "Builder.H"
#include "Director.H"
#include "Document.H"
#include "Interpreter.H"

void DomFacade::serialize(dom::Node* node, const std::string& fileName, bool minimal)
{
    std::fstream *	file = new std::fstream(fileName.c_str(), std::ios_base::out);
	XMLSerializer	xmlSerializer(file);

    if (minimal)
    {
    	xmlSerializer.serializeMinimal();
    }

	node->Accept(&xmlSerializer);
	delete file;
}

dom::Document* DomFacade::parseDocument(const std::string& fileName)
{
    dom::Document *	document = new Document_Impl;
	Builder builder(document);
	Director director(fileName, &builder);
}

double DomFacade::evaluateArithmeticXml(const std::string& fileName)
{
    ArithmeticInterpreter interpreter(fileName);
    return interpreter.evaluate();
}

dom::Node* DomFacade::findNodeByName(dom::Node* root, const std::string& name)
{
    dom::Node* foundNode = 0;
    for (dom::NodeList::iterator it = root->getChildNodes()->begin(); it != root->getChildNodes()->end(); it++)
    {
        if ((*it.operator->())->getNodeName() == name)
        {
            foundNode = (*it.operator->());
            break;
        }
        // recurse with this child.
        //  If foundNode is nonnull after this, then break because we found it
        else if ((foundNode = findNodeByName((*it.operator->()), name)) != 0)
        {
            break;
        }
    }
    return foundNode;
}

std::string DomFacade::getAttributeValue(dom::Node* root, const std::string& elementName, const std::string& attrName)
{
    dom::Node* foundElement = DomFacade::findNodeByName(root, elementName);
    if (foundElement != 0 && dynamic_cast<dom::Element*>(foundElement))
    {
        return dynamic_cast<dom::Element*>(foundElement)->getAttribute(attrName);
    }
    
    return "";
}