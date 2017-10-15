#ifndef DOM_NODE_ADAPTER_H
#define DOM_NODE_ADAPTER_H

#include "../xerces/xercesc/dom/DOMNode.hpp"
#include "Node.H"

namespace dom
{
    // Adapts our DOM Node to the Xerces XERCES::DOMNode interface
    class NodeAdapter : public virtual XERCES::DOMNode
    {
    public:
        NodeAdapter(){}
        NodeAdapter(Node* _adaptee) : adaptee(_adaptee) {}

        virtual const XERCES::XMLCh *   getNodeName() const
        {
            return adaptee->getNodeName().c_str();
        }
        virtual const XERCES::XMLCh *       getNodeValue() const
        {
            return adaptee->getNodeValue().c_str();
        }
        virtual void              setNodeValue(const XERCES::XMLCh  *nodeValue)
        {
            return adaptee->setNodeValue(nodeValue);
        }
        virtual XERCES::DOMNode::NodeType            getNodeType() const
        {
            short myNodeType = adaptee->getNodeType();
            switch (myNodeType)
            {
                case dom::Node::ATTRIBUTE_NODE:
                    return XERCES::DOMNode::ATTRIBUTE_NODE;
                case dom::Node::ELEMENT_NODE:
                    return XERCES::DOMNode::ELEMENT_NODE;
                case dom::Node::DOCUMENT_NODE:
                    return XERCES::DOMNode::DOCUMENT_NODE;
                case dom::Node::TEXT_NODE:
                    return XERCES::DOMNode::TEXT_NODE;
                default:
                    printf("ERROR: no matching node type\n");
                    break;
            }
            return XERCES::DOMNode::ELEMENT_NODE;
        }
        virtual XERCES::DOMNode        *getParentNode() const
        {
            return dynamic_cast<XERCES::DOMNode*>(adaptee->getParentNode());
        }
        virtual XERCES::DOMNodeList    *getChildNodes() const;
        virtual XERCES::DOMNode        *getFirstChild() const
        {
            return dynamic_cast<XERCES::DOMNode*>(adaptee->getFirstChild());
        }
        virtual XERCES::DOMNode        *getLastChild() const
        {
            return dynamic_cast<XERCES::DOMNode*>(adaptee->getLastChild());
        }
        virtual XERCES::DOMNode        *getPreviousSibling() const
        {
            return dynamic_cast<XERCES::DOMNode*>(adaptee->getPreviousSibling());
        }
        virtual XERCES::DOMNode        *getNextSibling() const
        {
            return dynamic_cast<XERCES::DOMNode*>(adaptee->getNextSibling());
        }
        virtual XERCES::DOMDocument      *getOwnerDocument() const
        {
            //return adaptee->getOwnerDocument();
        }
        virtual XERCES::DOMNode       *insertBefore(XERCES::DOMNode *newChild,
                                                    XERCES::DOMNode *refChild)
        {
            
        }
        virtual XERCES::DOMNode  *replaceChild(XERCES::DOMNode *newChild,
                                         XERCES::DOMNode *oldChild)
        {
            //NodeAdapter * newAdapter = static_cast<NodeAdapter*>(newChild);
            //NodeAdapter * oldAdapter = static_cast<NodeAdapter*>(oldChild);
        }
                                         
                                         
                                         
//                                         public org.w3c.dom.Node replaceChild( org.w3c.dom. Node node) {
 //  AdapterNode adapter = (AdapterNode)node;
  // realNode.replaceChilde(node.getAdaptee());
//}

        virtual XERCES::DOMNode        *removeChild(XERCES::DOMNode *oldChild)
        {
            
        }
        virtual XERCES::DOMNode        *appendChild(XERCES::DOMNode *newChild)
        {
            
        }
        virtual bool             hasChildNodes() const
        {
            return adaptee->hasChildNodes();
        }
        virtual const XERCES::XMLCh *          getLocalName() const
        {
            return adaptee->getLocalName().c_str();
        }
        
        // Maybe implemented methods
        virtual const XERCES::XMLCh*      getTextContent() const {}
        virtual void              setTextContent(const XERCES::XMLCh* textContent) {}
        virtual XERCES::DOMNamedNodeMap  *getAttributes() const {}
        virtual bool              hasAttributes() const {}

        // Unimplemented methods
        virtual XERCES::DOMNode        * cloneNode(bool deep) const {}
        virtual void              normalize() {}
        virtual bool              isSupported(const XERCES::XMLCh *feature,
    	                                       const XERCES::XMLCh *version) const {}
        virtual const XERCES::XMLCh *         getNamespaceURI() const {}
        virtual const XERCES::XMLCh *          getPrefix() const {}
        virtual void              setPrefix(const XERCES::XMLCh * prefix) {}
        virtual bool              isSameNode(const XERCES::DOMNode* other) const {}
        virtual bool              isEqualNode(const XERCES::DOMNode* arg) const {}
        virtual void*             setUserData(const XERCES::XMLCh* key,
                                              void* data,
                                              XERCES::DOMUserDataHandler* handler) {}
        virtual void*             getUserData(const XERCES::XMLCh* key) const {}
        virtual const XERCES::XMLCh*      getBaseURI() const {}
        virtual short             compareDocumentPosition(const XERCES::DOMNode* other) const {}
        virtual const XERCES::XMLCh*      lookupPrefix(const XERCES::XMLCh* namespaceURI) const {}
        virtual bool              isDefaultNamespace(const XERCES::XMLCh* namespaceURI) const {}
        virtual const XERCES::XMLCh*      lookupNamespaceURI(const XERCES::XMLCh* prefix) const {}
        virtual void*             getFeature(const XERCES::XMLCh* feature, const XERCES::XMLCh* version) const {}
        virtual void              release() {}
        
    private:
        Node * adaptee;
    }; // NodeAdapter
}; // dom

#endif