#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>
#include <fstream>

#include "Node.H"
#include "Element.H"
#include "Document.H"
#include "Builder.H"
#include "Director.H"
#include "XMLSerializer.H"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
protected:
    Command();
};

class ParseFileCommand : public Command
{
public:
    virtual void execute();
    ParseFileCommand(const std::string fileName_, dom::Node* rootNode_) :
        fileName(fileName_),
        rootNode(rootNode_) {}
private:
    std::string fileName;
    dom::Node* rootNode;
};

class SerializeCommand : public Command
{
public:
    SerializeCommand(const std::string& fileName, dom::Node* nodeToSerialize)  :
        file(new std::fstream(fileName.c_str(), std::ios_base::out)),
        node(nodeToSerialize) {}
    ~SerializeCommand()
    {
        if (file != 0)
        {
            delete file;
        }
    }
    virtual void execute();

private:
    dom::Node* node;
    std::fstream *	file;
};

class AddAttributeCommand : public Command
{
public:
    AddAttributeCommand(dom::Element* node_, const std::string& attrName_, const std::string& attrValue_) :
        node(node_),
        attrName(attrName_),
        attrValue(attrValue_) {}

    virtual void execute();
private:
    dom::Element* node;
    std::string attrName;
    std::string attrValue;
};

#endif