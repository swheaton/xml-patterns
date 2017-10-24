#include "Subject.H"
#include "Observer.H"

void Subject::attach(Observer * observer)
{
	std::vector<Observer *>::iterator	i;

	for (i = observers.begin(); i != observers.end() && *i != observer; i++);

	if (i == observers.end())
		observers.push_back(observer);
}

void Subject::detach(Observer * observer)
{
	for (std::vector<Observer *>::iterator i = observers.begin(); i != observers.end(); i++)
		if (*i == observer)
		{
			observers.erase(i);
			break;
		}
}

bool Subject::notify(dom::Node * container, short targetType, std::string & target)
{
	bool	result	= true;

	for (std::vector<Observer *>::iterator i = observers.begin(); i != observers.end(); i++)
		result &= (*i)->update(container, targetType, target);

	return result;
}
