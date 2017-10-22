#include "Observer.H"
#include <algorithm>

void Subject::attach(Observer* obs)
{
    observers.push_back(obs);
}

void Subject::detach(Observer* obs)
{
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Subject::notify()
{
    for (int i = 0; i < observers.size(); i++)
    {
        observers[i]->update(this);
    }
}