//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Flyweight Pattern
// This pattern is used to minimize memory usage and improves performance by sharing objects across different contexts.

// In this example, Flyweight Pattern is used to minimize memory usage by sharing common tree types (i.e., the intrinsic state) among multiple tree objects. The `TreeType` class represents the intrinsic state (shared data) of trees, such as name, color, and texture. The `TreeFactory` class ensures that only one instance of each unique `TreeType` is created and shared among all trees of that type.
// When creating trees in the `main` function, we use the `TreeFactory` to get shared instances of `TreeType`. Each `Tree` object contains extrinsic state (i.e., the x and y coordinates) and a reference to the shared `TreeType` instance. This way, the memory footprint is significantly reduced since the intrinsic state is shared, and only the extrinsic state is stored for each individual tree.
// By drawing each tree, we can see that the shared `TreeType` instances are used to render the trees efficiently, demonstrating the Flyweight Pattern in action.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

// Flyweight Interface
class TreeType {
public:
    virtual void draw(int x, int y) const = 0;
    virtual ~TreeType() = default;
};

// ConcreteFlyweight
class ConcreteTreeType : public TreeType {
private:
    std::string name;
    std::string color;
    std::string texture;

public:
    ConcreteTreeType(const std::string& name, const std::string& color, const std::string& texture)
        : name(name), color(color), texture(texture) {}

    void draw(int x, int y) const override {
        std::cout << "Drawing tree " << name << " of color " << color << " with texture " << texture << " at (" << x << ", " << y << ")\n";
    }
};

// FlyweightFactory
class TreeFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;

public:
    std::shared_ptr<TreeType> getTreeType(const std::string& name, const std::string& color, const std::string& texture) {
        std::string key = name + "_" + color + "_" + texture;
        if (treeTypes.find(key) == treeTypes.end()) {
            treeTypes[key] = std::make_shared<ConcreteTreeType>(name, color, texture);
        }
        return treeTypes[key];
    }
};

class Tree {
private:
    int x;
    int y;
    std::shared_ptr<TreeType> type;

public:
    Tree(int x, int y, std::shared_ptr<TreeType> type) : x(x), y(y), type(type) {}

    void draw() const {
        type->draw(x, y);
    }
};

int main() {
    TreeFactory factory;

    std::vector<Tree> forest;
    forest.emplace_back(1, 2, factory.getTreeType("Oak", "Green", "Rough"));
    forest.emplace_back(3, 4, factory.getTreeType("Pine", "Dark Green", "Smooth"));
    forest.emplace_back(5, 6, factory.getTreeType("Oak", "Green", "Rough"));
    forest.emplace_back(7, 8, factory.getTreeType("Pine", "Dark Green", "Smooth"));
    forest.emplace_back(9, 10, factory.getTreeType("Birch", "White", "Smooth"));

    for (const auto& tree : forest) {
        tree.draw();
    }

    return 0;
}