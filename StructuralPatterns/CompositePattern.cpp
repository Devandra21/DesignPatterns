//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Composite Pattern
// This pattern allows to compose objects into tree structures to represent part-whole hierarchies, treating individual objects and compositions uniformly. This pattern can be simpilfied in below three parts:
// Component: An interface that defines the common operations for both simple and complex objects of the composition.
// Leaf: A basic element of the composition that implements the Component interface. It represents the end objects of a composition.
// Composite: A complex component that has children and implements the Component interface. It can have operations to manage its child components.

// In this example, Composite Pattern is used to create a structure of graphics that can be treated uniformly.
// The Graphic interface (Component) defines the draw method which is implemented by Circle and Rectangle classes (Leaf).
// These classes represent simple graphical objects. The CompositeGraphic class (Composite) can contain multiple Graphic
// objects, including both simple shapes and other CompositeGraphic objects, allowing for nested compositions.
// By calling the draw method on a CompositeGraphic object, all its child graphics are drawn, demonstrating how the Composite
// Pattern enables treating individual objects and compositions of objects uniformly.

#include <iostream>
#include <vector>
#include <memory>

// Component Interface:
class Graphic {
public:
    virtual void draw() const = 0;
    virtual ~Graphic() = default;
};

// Leaf
class Circle : public Graphic {
public:
    void draw() const override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

// Leaf
class Rectangle : public Graphic {
public:
    void draw() const override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};

// Composite
class CompositeGraphic : public Graphic {
private:
    std::vector<std::shared_ptr<Graphic>> children;

public:
    void add(const std::shared_ptr<Graphic>& graphic) {
        children.push_back(graphic);
    }

    void draw() const override {
        for (const auto& child : children) {
            child->draw();
        }
    }
};

int main() {
    // Create simple shapes
    std::shared_ptr<Graphic> circle1 = std::make_shared<Circle>();
    std::shared_ptr<Graphic> circle2 = std::make_shared<Circle>();
    std::shared_ptr<Graphic> rectangle = std::make_shared<Rectangle>();

    // Create composite graphics
    std::shared_ptr<CompositeGraphic> composite1 = std::make_shared<CompositeGraphic>();
    std::shared_ptr<CompositeGraphic> composite2 = std::make_shared<CompositeGraphic>();

    // Compose graphics
    composite1->add(circle1);
    composite1->add(rectangle);

    composite2->add(circle2);
    composite2->add(composite1);  // Composite within composite

    // Draw all graphics
    composite2->draw();

    return 0;
}