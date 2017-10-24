#include "ValidChildren.H"
#include "XMLValidator.H"

void ValidChildren::addValidChild(const std::string & child, bool isAttribute)
{
	if (childIsValid(child, isAttribute))
		return;

	validChildren.push_back(child);
	childIsAttribute.push_back(isAttribute);
}

bool ValidChildren::childIsValid(const std::string & child, bool isAttribute)
{
	for (int i = 0; i < validChildren.size(); i++)
		if (childIsAttribute[i] == isAttribute && validChildren[i].compare(child) == 0)
		{
			if (mediator != 0)
				mediator->validation(thisElement, child, isAttribute);

			return true;
		}

	return false;
}

bool ValidChildren::update(dom::Node * container, short targetType, std::string & target)
{
	if (!active)
		return true;

	if (container == 0 && thisElement.size() == 0 && targetType == dom::Node::ELEMENT_NODE)
	{
		return childIsValid(target, false);
	}
	else if (container != 0 && thisElement.size() != 0)
	{
		if (thisElement == container->getNodeName())
			switch(container->getNodeType())
			{
			case dom::Node::ELEMENT_NODE:
				switch(targetType)
				{
				case dom::Node::ELEMENT_NODE:
					return childIsValid(target, false);
				case dom::Node::ATTRIBUTE_NODE:
					return childIsValid(target, true);
				case dom::Node::TEXT_NODE:
					return canHaveText();
				}
				break;
			case dom::Node::ATTRIBUTE_NODE:
				break;// ValidChildren can't do this yet.
			}
	}

	return true;	// Default behavior if this ValidChildren is indifferent to the event.
}
