#ifndef VISITOR_H
#define VISITOR_H

namespace dom
{
	class Document;
	class Element;
	class Attr;
	class Text;
};

class Visitor
{
public:
	virtual void VisitDocument(dom::Document * document) = 0;
	virtual void VisitElement(dom::Element * element) = 0;
	virtual void VisitAttribute(dom::Attr * attr) = 0;
	virtual void VisitText(dom::Text * text) = 0;
};

#endif // VISITOR_H
