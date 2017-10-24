#ifndef VALIDCHILDREN_H
#define VALIDCHILDREN_H

#include <vector>
#include <string>
#include "Observer.H"

class XMLValidator;

class ValidChildren : public Observer // and Colleague
{
private:
	std::string			thisElement;
	std::vector<std::string>	validChildren;
	std::vector<bool>		childIsAttribute;
	bool				_canHaveText;
	XMLValidator *			mediator;
	bool				active;
public:
	ValidChildren(std::string _thisElement, XMLValidator * _mediator) :
	  thisElement(_thisElement), _canHaveText(false), mediator(_mediator), active(true)	{}

	virtual std::string	getThisElement(void)			{ return thisElement; }
	virtual bool		canHaveText(void)			{ return _canHaveText; }
	virtual void		setCanHaveText(bool __canHaveText)	{ _canHaveText = __canHaveText; }

	virtual void		addValidChild(const std::string & child, bool isAttribute);
	virtual bool		childIsValid(const std::string & child, bool isAttribute);

	virtual void		activate(void)				{ active = true; }
	virtual void		deactivate(void)			{ active = false; }
	virtual bool		update(dom::Node * container, short targetType, std::string & target);
};

#endif // VALIDCHILDREN_H
