#ifndef DOM_DOCUMENT_ADAPTER_H
#define DOM_DOCUMENT_ADAPTER_H

#include "../xerces/xercesc/dom/DOMDocument.hpp"
#include "Document.H"
#include "NodeAdapter.H"

namespace dom
{
    // Adapts our XERCES::DOM Node to the Xerces XERCES::XERCES::DOMNode interface
    class DocumentAdapter : public virtual XERCES::DOMDocument
    {
    public:
        DocumentAdapter(void)
        {
            adaptee = new Document_Impl;
        }
        virtual ~DocumentAdapter()
        {
            if (adaptee != 0)
                delete adaptee;
        }
        virtual XERCES::DOMElement     *createElement(const XERCES::XMLCh *tagName);
        virtual XERCES::DOMText         *createTextNode(const XERCES::XMLCh *data)
        {
            
        }
        virtual XERCES::DOMAttr     *createAttribute(const XERCES::XMLCh *name)
        {
            
        }
        virtual XERCES::DOMElement     *getDocumentElement() const
        {
            //return adaptee->getDocumentElement();
        }

        // Unimplemented methods
        virtual XERCES::DOMDocumentFragment   *createDocumentFragment() {}
        virtual XERCES::DOMComment      *createComment(const XERCES::XMLCh *data) {}
        virtual XERCES::DOMCDATASection   *createCDATASection(const XERCES::XMLCh *data) {}
        virtual XERCES::DOMProcessingInstruction *createProcessingInstruction(const XERCES::XMLCh *target,
            const XERCES::XMLCh *data) {}
        virtual XERCES::DOMEntityReference    *createEntityReference(const XERCES::XMLCh *name) {}
        virtual XERCES::DOMDocumentType      *getDoctype() const {}
        virtual XERCES::DOMImplementation  *getImplementation() const {}
        virtual XERCES::DOMNodeList      *getElementsByTagName(const XERCES::XMLCh *tagname) const {}
        virtual XERCES::DOMNode        *importNode(const XERCES::DOMNode *importedNode, bool deep) {}
        virtual XERCES::DOMElement         *createElementNS(const XERCES::XMLCh *namespaceURI,
    	                                              const XERCES::XMLCh *qualifiedName) {}
        virtual XERCES::DOMAttr        *createAttributeNS(const XERCES::XMLCh *namespaceURI,
    	                                            const XERCES::XMLCh *qualifiedName) {}
        virtual XERCES::DOMNodeList        *getElementsByTagNameNS(const XERCES::XMLCh *namespaceURI,
    	                                                     const XERCES::XMLCh *localName) const {}
        virtual  XERCES::DOMElement        * getElementById(const XERCES::XMLCh *elementId) const {}
        virtual const XERCES::XMLCh*           getInputEncoding() const {}
        virtual const XERCES::XMLCh*           getXmlEncoding() const {}
        virtual bool                   getXmlStandalone() const {}
        virtual void                   setXmlStandalone(bool standalone) {}
        virtual const XERCES::XMLCh*           getXmlVersion() const {}
        virtual void                   setXmlVersion(const XERCES::XMLCh* version) {}
        virtual const XERCES::XMLCh*           getDocumentURI() const {}
        virtual void                   setDocumentURI(const XERCES::XMLCh* documentURI) {}
        virtual bool                   getStrictErrorChecking() const {}
        virtual void                   setStrictErrorChecking(bool strictErrorChecking) {}
        virtual XERCES::DOMNode* renameNode(XERCES::DOMNode* n, const XERCES::XMLCh* namespaceURI, const XERCES::XMLCh* qualifiedName) {}
        virtual XERCES::DOMNode*               adoptNode(XERCES::DOMNode* source) {}
        virtual void                   normalizeDocument() {}
        virtual XERCES::DOMConfiguration*      getDOMConfig() const {}
        virtual XERCES::DOMEntity     *createEntity(const XERCES::XMLCh *name) {}
        virtual XERCES::DOMDocumentType *createDocumentType(const XERCES::XMLCh *name) {}
        virtual XERCES::DOMDocumentType * createDocumentType(const XERCES::XMLCh *qName,
                                                    const XERCES::XMLCh*,  //publicId,
                                                    const XERCES::XMLCh*   //systemId
                                                   )
        {
            return createDocumentType(qName);
        }
        virtual XERCES::DOMNotation *createNotation(const XERCES::XMLCh *name) {}
        virtual XERCES::DOMElement *createElementNS(const XERCES::XMLCh *namespaceURI,
                                            const XERCES::XMLCh *qualifiedName,
                                            const XERCES::XMLFileLoc lineNum,
                                            const XERCES::XMLFileLoc columnNum) {}
                                            
                                            
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
        virtual XERCES::DOMNodeList    *getChildNodes() const
        {
            
        }
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
        Document* adaptee;
    }; // DocumentAdapter

}; // dom

#endif