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

std::vector<ValidChildren *> XMLValidator::cloneSchema(const std::vector<ValidChildren*>& schemaToCopy)
{
	std::vector<ValidChildren*> newSchema;
	// Do deep copy of schema
	for(int i = 0; i < schemaToCopy.size(); i++)
	{
		// No need for a deep copy of ValidChildren, it has no pointers, except
		//	mediator, which we want to keep the same
		ValidChildren* clonedValidChildren = new ValidChildren(*schemaToCopy[i]);
		newSchema.push_back(clonedValidChildren);
	}
	return newSchema;
}

XMLValidator::Memento* XMLValidator::createMemento()
{
	XMLValidator::Memento* memento = new XMLValidator::Memento();
	memento->schema = XMLValidator::cloneSchema(this->schema);
}

void XMLValidator::setFromMemento(const XMLValidator::Memento* memento)
{
	// First delete the old schema
	for (int i = 0; i < schema.size(); i++)
		delete schema[i];
		
	// Now clone the memento's schema and set it
	schema = XMLValidator::cloneSchema(memento->schema);
}