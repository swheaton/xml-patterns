#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Node.H"

namespace dom
{
	class Document;
	class Text_Impl;

	class Text : public virtual Node
	{
	protected:
		Text(const std::string value, dom::Document * document);
	public:
		friend class Document_Impl;
		friend class Text_Impl;
		virtual ~Text()	{}

		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)	;

		virtual const std::string &	getName(void)							;
		virtual const std::string &	getData(void)							;
		virtual const std::string &	getValue(void)							;
		virtual void			setData(const std::string & value)				;
		virtual void			setValue(const std::string & value)				;
		virtual int			getLength(void)							;
		virtual const std::string &	substringData(int offset, int count)				;
		virtual void			appendData(const std::string & arg)				;
		virtual void			insertData(int offset, const std::string & arg)			;
		virtual void			deleteData(int offset, int count)				;
		virtual void			replaceData(int offset, int count, const std::string & arg)	;
		virtual Text *			splitText(int offset)						;
	private:
		Text_Impl* textImpl;
	};


	class Text_Impl : public virtual Node_Impl
	{
	protected:
		Text_Impl(const std::string value, dom::Document * document);
	public:
		friend class Document_Impl;
		friend class Text;
	
		virtual ~Text_Impl();
	
		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);
	
		virtual const std::string &	getName(void);
		virtual const std::string &	getData(void);
		virtual const std::string &	getValue(void);
		virtual void			setData(const std::string & value);
		virtual void			setValue(const std::string & value);
		virtual int			getLength(void);
		virtual const std::string &	substringData(int offset, int count);
		virtual void			appendData(const std::string & arg);
		virtual void			insertData(int offset, const std::string & arg);
		virtual void			deleteData(int offset, int count);
		virtual void			replaceData(int offset, int count, const std::string & arg);
		virtual dom::Text *		splitText(int offset);
	
		//
		// Overridden functions for conforming to Composite Leaf node behavior.
		//
		virtual Node *			insertBefore(Node * newChild, Node * refChild)	{ return 0; }
		virtual Node *			replaceChild(Node * newChild, Node * oldChild)	{ return 0; }
		virtual Node *			removeChild(Node * oldChild)			{ return 0; }
		virtual Node *			appendChild(Node * newChild)			{ return 0; }
	};
};

#endif // TEXT_H
