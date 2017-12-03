#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Node.H"
#include "Element.H"

class ArithmeticExpression
{
public:
    ArithmeticExpression() {}
    virtual ~ArithmeticExpression() {}
    
    virtual double evaluate() = 0;
};

class Literal : public virtual ArithmeticExpression
{
public:
    Literal(double _value) : 
        ArithmeticExpression(),
        value(_value) {}
    virtual ~Literal() {}
    virtual double evaluate()
    {
        return value;
    }
private:
    double value;
};

class UnaryOperation : public virtual ArithmeticExpression
{
public:
    UnaryOperation(char _op, ArithmeticExpression* _operand) :
        ArithmeticExpression(),
        op(_op),
        operand(_operand) {}
        
    virtual ~UnaryOperation()
    {
        if (operand)
        {
            delete operand;
        }
    }
        
    virtual double evaluate()
    {
        double result = 0.0;
        switch (op)
        {
            case '-':
                result = -1 * (operand->evaluate());
                break;
                
            default:
                throw dom::DOMException(dom::DOMException::INVALID_CHARACTER_ERR, "Invalid operator");
                break;
        }
        return result;
    }

private:
    char op;
    ArithmeticExpression* operand;
};

class BinaryOperation : public virtual ArithmeticExpression
{
public:
    BinaryOperation(char _op, ArithmeticExpression* _operand1, ArithmeticExpression* _operand2) :
        ArithmeticExpression(),
        op(_op),
        operand1(_operand1),
        operand2(_operand2) {}
        
    virtual ~BinaryOperation()
    {
        if (operand1)
        {
            delete operand1;
        }
        if (operand2)
        {
            delete operand2;
        }
    }
        
    virtual double evaluate()
    {
        double result = 0.0;
        switch (op)
        {
            case '-':
                result = operand1->evaluate() - operand2->evaluate();
                break;
                
            case '+':
                result = operand1->evaluate() + operand2->evaluate();
                break;
                
            case '*':
                result = operand1->evaluate() * operand2->evaluate();
                break;
                
            case '/':
                result = operand1->evaluate() / operand2->evaluate();
                break;
                
            default:
                throw dom::DOMException(dom::DOMException::INVALID_CHARACTER_ERR, "Invalid operator");
                break;
        }
        return result;
    }

private:
    char op;
    ArithmeticExpression * operand1;
    ArithmeticExpression * operand2;
};

class ArithmeticInterpreter
{
public:
    ArithmeticInterpreter(const std::string& fileName);
    double evaluate();

private:
    ArithmeticExpression* rootExpr;
    
    ArithmeticExpression* interpret(dom::Element* node);
};

#endif // INTERPRETER_H