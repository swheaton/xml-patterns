#include <string>
#include <iostream>
#include <ios>

#include "Node.H"
#include "Visitor.H"

//
// XMLSerializer is Serialization Strategy Context
// Node is Serialization Strategy and output stream Strategy Context
// Document, Element, Attr, Text are Serialization Concrete Strategies
// java.io.Writer is output stream Strategy
// java.io.BufferedWriter is output stream Concrete Strategy
//
class XMLSerializer : public Visitor
{
private:
	std::ostream *		file;
	WhitespaceStrategy *	whitespace;

	class PrettyWhitespaceStrategy : public WhitespaceStrategy
	{
	private:
		int	indentationLevel;
	public:
		PrettyWhitespaceStrategy(void) : indentationLevel(0)	{}

		virtual void	prettyIndentation(std::ostream * wwriter)
		{
			for (int i = 0; i < indentationLevel; i++)
				*wwriter << "\t";
		}

		virtual void incrementIndentation(void)		{ indentationLevel++; }
		virtual void decrementIndentation(void)		{ indentationLevel--; }
		virtual void newLine(std::ostream * wwriter)	{ *wwriter << "\n"; }
	};

	class MinimalWhitespaceStrategy : public WhitespaceStrategy
	{
	public:
		virtual void prettyIndentation(std::ostream * wwriter)	{}
		virtual void incrementIndentation(void)			{}
		virtual void decrementIndentation(void)			{}
		virtual void newLine(std::ostream * wwriter)		{}
	};

	virtual void VisitDocument(dom::Document * document);
	virtual void VisitElement(dom::Element * element);
	virtual void VisitAttribute(dom::Attr * attr);
	virtual void VisitText(dom::Text * text);
public:
	XMLSerializer(std::ostream * _file) : file(_file), whitespace(new PrettyWhitespaceStrategy)	{}
	~XMLSerializer() {}

	//
	// Strategized serialization
	//
	virtual void		serializePretty(void);
	virtual void		serializeMinimal(void);
};
