#include "Interpreter.H"

#include <sstream>

#include "Builder.H"
#include "Director.H"
#include "Document.H"
#include "Text.H"

ArithmeticInterpreter::ArithmeticInterpreter(const std::string& fileName)
{
    dom::Document *	document	= new Document_Impl;
	Builder builder(document);
	Director director(fileName, &builder);
	
	rootExpr = interpret(document->getDocumentElement());
}

ArithmeticExpression* ArithmeticInterpreter::interpret(dom::Element* node)
{
    ArithmeticExpression* expr = 0;
    // Literal
    if (node->getTagName() == "value")
    {
        // Find the text node, and read in the literal
        for (dom::NodeList::iterator it = node->getChildNodes()->begin(); it != node->getChildNodes()->end(); it++)
        {
            if (dynamic_cast<dom::Text*>(*it.operator->()))
            {
                std::istringstream stream((*it)->getNodeValue());
                double value = 0.0;
                stream >> value;
                expr = new Literal(value);
                break;
            }
        }
    }
    // Unary operation
    else if (node->getChildNodes()->size() > 0 && node->getTagName() == "operation"
        && node->hasAttribute("type"))
    {
        char type = node->getAttribute("type")[0];
        std::vector<ArithmeticExpression*> exprs;
        for (dom::NodeList::iterator it = node->getChildNodes()->begin(); it != node->getChildNodes()->end(); it++)
        {
            if (dynamic_cast<dom::Element*>(*it.operator->()))
            {
                exprs.push_back(interpret(dynamic_cast<dom::Element*>(*it.operator->())));
            }
        }
        if (exprs.size() == 1)
        {
            expr = new UnaryOperation(type, exprs[0]);
        }
        else if (exprs.size() == 2)
        {
            expr = new BinaryOperation(type, exprs[0], exprs[1]);
        }
        // Else invalid arithmetic!
    }
    // If none of these, then we gave an invalid arithmetic expression
    return expr;
}

// Evaluate the root expression and return value
double ArithmeticInterpreter::evaluate()
{
    if (rootExpr != 0)
    {
        return rootExpr->evaluate();
    }
    return 0.0;
}