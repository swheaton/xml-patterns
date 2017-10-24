#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

namespace dom
{
	class Node;
};

class Observer
{
public:
	virtual bool	update(dom::Node * container, short targetType, std::string & target) = 0;
};

#endif // OBSERVER_H
