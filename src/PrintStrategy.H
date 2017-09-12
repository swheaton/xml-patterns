#ifndef PRINTSTRATEGY_H
#define PRINTSTRATEGY_H


namespace dom
{
    // AbstractStrategy for printing a node
    class PrintStrategy
    {
        std::string getWhitespaceAddition(int indentation) = 0;
    }
    
    // ConcreteStrategy for printing nothing - minimal
    class MinimalPrintStrategy
    {
        std::string getWhitespaceAddition(int indentation)
        {
            return "";
        }
    }
    
    // ConcreteStrategy for printing indentation - pretty print
    class PrettyPrintStrategy
    {
        std::string getWhitespaceAddition(int indentation)
        {
            std::string outString = "";
            for (int i = 0; i < indentation; i++)
		        outString += "\t";
        }
    }
}

#endif
