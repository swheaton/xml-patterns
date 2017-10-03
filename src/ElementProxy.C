#include "ElementProxy.H"
#include "XMLTokenizer.H"

void ElementProxy::loadChildren()
{
    XMLTokenizer	tokenizer(fileName, offset);

    XMLTokenizer::XMLToken *	token	= 0;
    dom::Element * currElt = 0;
    bool firstElt = false, tagCloseStart = false;
    std::string eltName = "", attrName = "";
    
    // We start off right past this element proxy, so the level is 1.
    int level = 1;
    do
    {
        if (token != 0)
        {
            delete	token;
        }
        token	= tokenizer.getNextToken();
    	switch (token->getTokenType())
    	{
    		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
    			if (currElt != 0 && level == 1)
    			{
    				XMLBuilder::getInstance()->addAttribute(currElt, attrName, token->getToken());
    				attrName = "";
    			}
    			break;

    		case XMLTokenizer::XMLToken::ELEMENT:
    			// Important - only create children - no further descendants!
    			if (!tagCloseStart && level == 1)
    			{
    				currElt = XMLBuilder::getInstance()->addElement(parent, token->getToken(), fileName, tokenizer.getFileOffset());
    			}
    			break;
    		case XMLTokenizer::XMLToken::ATTRIBUTE:
    			attrName = token->getToken();
    			break;				   				   				   				   				   				   				 	     					        
    		case XMLTokenizer::XMLToken::NULL_TAG_END:
    			break;
    		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
    			tagCloseStart = true;
    			break;
    		case XMLTokenizer::XMLToken::VALUE:
    			if (level == 1)
    			    XMLBuilder::getInstance()->addText(parent, token->getToken());
    			break;
    		case XMLTokenizer::XMLToken::TAG_END:
    		    if (tagCloseStart)
    		        level--;
    		    else
    		        level++;
    			tagCloseStart = false;
    			break;
    		default:
    			break;
    	}
    } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN && level > 0);
}