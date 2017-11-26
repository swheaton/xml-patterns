#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include "XMLTokenizer.H"
#include "DirectorState.H"

class Builder;
class DirectorState;

class Director
{
private:
	
	DirectorState* state;
	
	friend class DirectorState;
	void changeState(DirectorState* newState)
	{
		this->state = newState;
	}
public:
	Director(const std::string & filename, Builder * builder);
};

#endif // DIRECTOR_H
