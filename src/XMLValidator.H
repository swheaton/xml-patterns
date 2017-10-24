#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include "Element.H"

class ValidChildren;
class Subject;

//
// Mediator
//
class XMLValidator
{
private:
	std::vector<ValidChildren *>	schema;
	Subject *			subject;
public:
	XMLValidator(void) : subject(0)				{}
	XMLValidator(Subject * _subject) : subject(_subject)	{}
	~XMLValidator()						{ for (int i = 0; i < schema.size(); i++) delete schema[i]; }

	virtual ValidChildren *				addSchemaElement(std::string element);
	virtual std::vector<ValidChildren *>::iterator	findSchemaElement(std::string element);
	virtual void					validation(std::string & thisElement, const std::string &child, bool isAttribute);
};
