#ifndef FACADE_H
#define FACADE_H

#include "Node.H"

// Static class providing a facade to the DOM XML classes
class DomFacade
{
public:
    static void serialize(dom::Node* node, const std::string& file, bool minimal);
    static dom::Document* parseDocument(const std::string& fileName);
    static double evaluateArithmeticXml(const std::string& fileName);
    static dom::Node* findNodeByName(dom::Node* root, const std::string& name);
    static std::string getAttributeValue(dom::Node* root, const std::string& elementName, const std::string& attrName);
    
private:
    DomFacade() {}
    ~DomFacade() {}
};

#endif // FACADE_H