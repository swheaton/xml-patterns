#ifndef DIRECTORSTATE_H
#define DIRECTORSTATE_H

#include "XMLTokenizer.H"
#include "Director.H"
#include "Builder.H"

class Director;

class DirectorState
{
public:
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token) {}
protected:
    void changeState(Director* director, DirectorState* state);
    DirectorState() {}
};

class End : public virtual DirectorState
{
public:
    static End& getInstance()
    {
        static End _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token)
    {
    }
};

class InsideElement : public virtual DirectorState
{
public:
    static InsideElement& getInstance()
    {
        static InsideElement _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class ElementTagCloseStart : public virtual DirectorState
{
public:
    static ElementTagCloseStart& getInstance()
    {
        static ElementTagCloseStart _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class ElementValue : public virtual DirectorState
{
public:
    static ElementValue& getInstance()
    {
        static ElementValue _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class NonnullElement : public virtual DirectorState
{
public:
    static NonnullElement& getInstance()
    {
        static NonnullElement _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class NullTagEnd : public virtual DirectorState
{
public:
    static NullTagEnd& getInstance()
    {
        static NullTagEnd _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class PrologAttribute : public virtual DirectorState
{
public:
    static PrologAttribute& getInstance()
    {
        static PrologAttribute _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class ParseAttribute : public virtual DirectorState
{
public:
    static ParseAttribute& getInstance()
    {
        static ParseAttribute _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class ParseElement : public virtual DirectorState
{
public:
    static ParseElement& getInstance()
    {
        static ParseElement _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class TagStart : public virtual DirectorState
{
public:
    static TagStart& getInstance()
    {
        static TagStart _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class AfterProlog : public virtual DirectorState
{
public:
    static AfterProlog& getInstance()
    {
        static AfterProlog _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class PrologIdentifier : public virtual DirectorState
{
public:
    static PrologIdentifier& getInstance()
    {
        static PrologIdentifier _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class PrologStart : public virtual DirectorState
{
public:
    static PrologStart& getInstance()
    {
        static PrologStart _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

class BeforePrologState : public virtual DirectorState
{
public:
    static BeforePrologState& getInstance()
    {
        static BeforePrologState _instance;
        return _instance;
    }
    virtual void parse(Director* director, Builder* builder, XMLTokenizer::XMLToken * token);
};

#endif // DIRECTORSTATE_H

/*
BeforeProlog -> PrologStart
PrologStart -> PrologIdentifier
PrologIdentifier -> PrologAttribute, AfterProlog
PrologAttribute -> PrologAttributeValue
PrologAttributeValue (merge w/ PrologIdentifier??) -> PrologAttribute, AfterProlog
AfterProlog -> TagStart
TagStart -> ParseElement
ParseElement -> ParseAttribute, NonnullElement, NullTagEnd
ParseAttribute -> ParseAttributeValue
ParseAttributeValue (merge w/ ParseElement) -> ParseAttribute, NullTagEnd, NonnullElement
NullTagEnd -> ParseElement, ElementTagCloseStart
NonnullElement -> ParseElement, ElementTagCloseStart, ElementValue
ElementTagCloseStart -> InsideElement
InsideElement -> NonnullElement, End
ElementValue -> ElementTagCloseStart
End
*/