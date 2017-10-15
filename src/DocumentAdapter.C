#include "DocumentAdapter.H"

XERCES::DOMElement     *dom::DocumentAdapter::createElement(const XERCES::XMLCh *tagName)
{
    // Returns Element_Impl which is a dom::Element
    dom::Node * retElt = adaptee->createElement(std::string(tagName));
    //dom::Node * retNode = retElt;
    //return new NodeAdapter(retNode);
}