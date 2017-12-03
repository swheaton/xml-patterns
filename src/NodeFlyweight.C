#include "NodeFlyweight.H"

#include <functional>

size_t NodeFlyweight::Hash::operator()(NodeFlyweight* flyweight) const
{
    std::string temp = flyweight->name + flyweight->value;
    return std::hash<std::string>()(temp);
}

NodeFlyweight* NodeFlyweightFactory::getFlyweight(const std::string& name, const std::string& value)
{
    NodeFlyweight lookupFlyweight(name, value);
    auto flyweightIt = nodeFlyweights.find(&lookupFlyweight);
    if (flyweightIt == nodeFlyweights.end())
    {
        return *(nodeFlyweights.insert(new NodeFlyweight(name, value)).first);
    }
    return *flyweightIt;
}

// Declare the set
std::unordered_set<NodeFlyweight*, NodeFlyweight::Hash> NodeFlyweightFactory::nodeFlyweights;
