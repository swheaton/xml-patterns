#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <string>

namespace dom
{
	class Node;
};

class Observer;

class Subject
{
private:
	std::vector<Observer *>	observers;
public:
	void	attach(Observer * observer);
	void	detach(Observer * observer);
protected:
	bool notify(dom::Node * container, short targetType, std::string & target);
};

#endif // SUBJECT_H
