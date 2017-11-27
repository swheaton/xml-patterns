#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>
#include <ios>
//#include "Attr.H"
//#include "Element.H"
//#include "Text.H"
//#include "Document.H"

namespace dom {
    class Attr;
    class Element;
    class Text;
    class Document;
}
class WhitespaceStrategy;

class Visitor
{
public:
    Visitor() {}

    virtual void visitAttr(dom::Attr*) = 0;
    virtual void visitDocument(dom::Document*) = 0;
    virtual void visitElement(dom::Element*) = 0;
    virtual void visitText(dom::Text*) = 0;
};

class SerializeVisitor : public virtual Visitor
{
public:
    SerializeVisitor(std::ostream* _writer, WhitespaceStrategy* _whitespace) :
        writer(_writer),
        whitespace(_whitespace) {}
    virtual void visitAttr(dom::Attr* attr);
    virtual void visitDocument(dom::Document* doc);
    virtual void visitElement(dom::Element* elt);
    virtual void visitText(dom::Text* t);
private:
    std::ostream * writer;
    WhitespaceStrategy * whitespace;
};

#endif // VISITOR_H