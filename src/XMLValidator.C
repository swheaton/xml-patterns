#include "XMLValidator.H"
#include "ValidChildren.H"
#include "Subject.H"

ValidChildren * XMLValidator::addSchemaElement(std::string element)
{
	std::vector<ValidChildren *>::iterator	schemaElementIterator	= findSchemaElement(element);

	if (schemaElementIterator != schema.end())
	{
		schema.erase(schemaElementIterator);
		if (subject != 0)
			subject->detach(*schemaElementIterator);
		delete *schemaElementIterator;
	}

	ValidChildren *	schemaElement	= 0;
	schema.push_back(schemaElement = new ValidChildren(element, this));
	if (subject != 0)
		subject->attach(schemaElement);
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

void XMLValidator::validation(std::string & thisElement, const std::string &child, bool isAttribute)
{
	//
	// Some arbitrary decision algorithm.  In this case, halt validation when we encounter attribute2.
	//
	if (isAttribute && thisElement == "element" && child == "attribute2")
		for (std::vector<ValidChildren *>::iterator i = schema.begin(); i != schema.end(); i++)
			(*i)->deactivate();
}
