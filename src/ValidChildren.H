#ifndef VALIDCHILDREN_H
#define VALIDCHILDREN_H

#include <vector>
#include <string>

class XMLValidator;

class ValidChildren
{
private:
	std::string			thisElement;
	std::vector<std::string>	validChildren;
	std::vector<bool>		childIsAttribute;
	bool				_canHaveText;
	XMLValidator*		mediator;
public:
	ValidChildren(std::string _thisElement, XMLValidator* _mediator) :
		thisElement(_thisElement),
		_canHaveText(false),
		mediator(_mediator) {}

	virtual std::string	getThisElement(void)			{ return thisElement; }
	virtual bool		canHaveText(void)			{ return _canHaveText; }
	virtual void		setCanHaveText(bool __canHaveText)	{ _canHaveText = __canHaveText; }

	virtual void		addValidChild(const std::string & child, bool isAttribute);
	virtual bool		childIsValid(const std::string & child, bool isAttribute);
	
	// Does nothing right now, but ValidChildren can use this information in
	//	the future
	void shareValidationInfo(const std::string& child, bool isValid) {}
};

#endif // VALIDCHILDREN_H
