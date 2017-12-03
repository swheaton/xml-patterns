#ifndef NODEFLYWEIGHT_H
#define NODEFLYWEIGHT_H

#include <unordered_set>

// Plain old data class for intrinsic data of node, to allow it to be shared,
//  a la flyweight pattern
struct NodeFlyweight
{
public:
    std::string name;
    std::string value;
    
    NodeFlyweight(const std::string& _name, const std::string& _value) :
        name(_name),
        value(_value) {}
    
    struct Hash {
        size_t operator()(NodeFlyweight* flyweight) const;
    };
};

// Factory that stores shared flyweight nodes
class NodeFlyweightFactory
{
public:
    static NodeFlyweight* getFlyweight(const std::string& name, const std::string& value);

private:
    // Set of flyweight pointers
    static std::unordered_set<NodeFlyweight*, NodeFlyweight::Hash> nodeFlyweights;
};
#endif //NODEFLYWEIGHT_H