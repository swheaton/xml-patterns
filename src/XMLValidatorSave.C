#include "XMLValidatorSave.H"

void XMLValidatorSave::save()
{
    if (memento != NULL)
    {
        delete memento;
    }
    memento = validator->createMemento();
}

void XMLValidatorSave::revertToLastSave()
{
    validator->setFromMemento(memento);
}