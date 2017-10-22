#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observer;
class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(Observer* obs);
    virtual void detach(Observer* obs);
    virtual void notify();
protected:
    Subject() {}
private:
    std::vector < Observer* > observers;
};

class Observer {
public:
    virtual void update(Subject* changedSubject) = 0;
protected:
    Observer() {}
};

#endif // OBSERVER_H