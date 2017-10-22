#include "XMLValidator.H"
#include "ValidChildren.H"
#include "Builder.H"
#include "Attr.H"

ValidChildren * XMLValidator::addSchemaElement(std::string element)
{
	std::vector<ValidChildren *>::iterator	schemaElementIterator	= findSchemaElement(element);

	if (schemaElementIterator != schema.end())
	{
		schema.erase(schemaElementIterator);
		delete *schemaElementIterator;
	}

	ValidChildren *	schemaElement	= 0;
	schema.push_back(schemaElement = new ValidChildren(element, this));
	return schemaElement;
}

std::vector<ValidChildren *>::iterator XMLValidator::findSchemaElement(std::string element)
{
	for (std::vector<ValidChildren *>::iterator i = schema.begin(); i != schema.end(); i++)
		if (((*i)->getThisElement().size() == 0 && element.size() == 0) ||
		  ((*i)->getThisElement().size() > 0 && (*i)->getThisElement().compare(element) == 0))
			return i;

	return schema.end();
}

void XMLValidator::update(Subject* changedSubject)
{
	// Make sure Subject is of type Builder... it should be
	Builder* builderSubject = dynamic_cast<Builder*>(changedSubject);
	if (builderSubject != NULL)
	{
		dom::Node * newNode = builderSubject->getRecentNode();
		ValidChildren* schemaElement	= *findSchemaElement(newNode->getParentNode()->getNodeName());
		if (schemaElement != NULL)
		{
			bool isAttr = (dynamic_cast<dom::Attr*>(newNode) != NULL);
			if(!schemaElement->childIsValid(newNode->getNodeName(), isAttr))
			{
				throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid child node " + newNode->getNodeName() + ".");
			}
		}
	}
}

// Share validation info from one ValidChildren object with all others
void XMLValidator::shareValidationInfo(const std::string& child, bool isValid)
{
	for (ValidChildren* schemaElement : schema)
	{
		schemaElement->shareValidationInfo(child, isValid);
	}
}
