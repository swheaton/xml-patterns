#ifndef BUILDER_H
#define BUILDER_H

#include <stack>
#include <string>

namespace dom
{
	class Document;
	class Element;
	class Attr;
};

class Builder
{
private:
	dom::Document *			factory;
	std::stack<dom::Element *>	elementStack;
	dom::Element *			currentElement;
	dom::Attr *			currentAttr;

	virtual const std::string	trim(const std::string & s) const;
public:
	Builder(dom::Document * _factory) : factory(_factory), currentElement(0), currentAttr(0) {}

	virtual dom::Document *	getDocument(void)	{ return factory; }	// aka getResult

	virtual void		addValue(const std::string & text);
	virtual void		confirmElement(const std::string & tag);
	virtual void		createAttribute(const std::string & attribute);
	virtual void		createElement(const std::string & tag);
	virtual void		createProlog(void);
	virtual void		endProlog(void);
	virtual void		identifyProlog(const std::string & id);
	virtual bool		popElement(void);
	virtual void		pushElement(void);
	virtual void		valueAttribute(const std::string & value);
};

#endif // BUILDER_H
