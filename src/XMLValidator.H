#ifndef XMLVALIDATOR_H
#define XMLVALIDATOR_H

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
	
	static std::vector<ValidChildren *> cloneSchema(const std::vector<ValidChildren*>& schemaToCopy);
public:
	XMLValidator(void) : subject(0)				{}
	XMLValidator(Subject * _subject) : subject(_subject)	{}
	~XMLValidator()						{ for (int i = 0; i < schema.size(); i++) delete schema[i]; }

	virtual ValidChildren *				addSchemaElement(std::string element);
	virtual std::vector<ValidChildren *>::iterator	findSchemaElement(std::string element);
	virtual void					validation(std::string & thisElement, const std::string &child, bool isAttribute);
	
	// Memento functions
	class Memento
	{
	public:
		virtual ~Memento()
		{
			for (int i = 0; i < schema.size(); i++)
			{
				delete schema[i];
			}
		}
	private:
		friend class XMLValidator;
		Memento() {}
		std::vector<ValidChildren *> schema;
	};
	virtual Memento* createMemento();
	virtual void setFromMemento(const Memento* memento);
};

#endif