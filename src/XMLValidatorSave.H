#ifndef XMLVALIDATORSAVE_H
#define XMLVALIDATORSAVE_H

#include "XMLValidator.H"

// Caretaker for XMLValidator::Memento
class XMLValidatorSave
{
public:
    XMLValidatorSave(XMLValidator* validator_) :
        validator(validator_),
        memento(NULL) {}

    void save();
    void revertToLastSave();
private:
    XMLValidator* validator;
    XMLValidator::Memento* memento;
};

#endif