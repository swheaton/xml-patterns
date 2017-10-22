#ifndef XMLVALIDATOR_H
#define XMLVALIDATOR_H

#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include "Element.H"
#include "Observer.H"
#include "ValidChildren.H"

class XMLValidator : public virtual Observer
{
private:
	std::vector<ValidChildren *>	schema;
public:
	XMLValidator(void)	{}
	~XMLValidator() { for (int i = 0; i < schema.size(); i++) delete schema[i]; }

	virtual ValidChildren *				addSchemaElement(std::string element);
	virtual std::vector<ValidChildren *>::iterator	findSchemaElement(std::string element);
	
	// Observer functions
	virtual void update(Subject* changedSubject);
	
	// Mediator function for sharing info
	void shareValidationInfo(const std::string& child, bool isValid);
};

#endif