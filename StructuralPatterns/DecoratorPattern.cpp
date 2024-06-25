//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Decorator Pattern
// This pattern attaches additional responsibilities to an object dynamically, providing a flexible alternative to subclassing for extending functionality. This pattern can be simpilfied in below four parts:
// Component : An interface that defines the behavior that can be dynamically added to objects.
// Concrete Component: A class that implements the Component interface and represents the core object to which additional responsibilities can be attached.
// Decorator: An abstract class that implements the Component interface and has a reference to a Component object. It serves as the base class for all concrete decorators.
// Concrete Decorators: Classes that extend the Decorator class and add additional responsibilities to the component.


#include <iostream>
#include <memory>

// Component Interface
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual std::string getDescription() const = 0;
    virtual int cost() const = 0;
};

// Concrete Component
class Espresso : public Beverage {
public:
    std::string getDescription() const override {
        return "Espresso";
    }

    int cost() const override {
        return 10;
    }
};

// Decorator
class CondimentDecorator : public Beverage {
public:
    virtual ~CondimentDecorator() = default;
    virtual std::string getDescription() const = 0;
};

// Concrete Decorators
class Milk : public CondimentDecorator {
public:
    Milk(std::shared_ptr<Beverage> beverage) : beverage_(beverage) {}

    std::string getDescription() const override {
        return beverage_->getDescription() + ", Milk";
    }

    int cost() const override {
        return 15 + beverage_->cost();
    }

private:
    std::shared_ptr<Beverage> beverage_;
};

class Mocha : public CondimentDecorator {
public:
    Mocha(std::shared_ptr<Beverage> beverage) : beverage_(beverage) {}

    std::string getDescription() const override {
        return beverage_->getDescription() + ", Mocha";
    }

    int cost() const override {
        return 30 + beverage_->cost();
    }

private:
    std::shared_ptr<Beverage> beverage_;
};


int main() {
    // Create an Espresso beverage
    std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();
    std::cout << beverage->getDescription() << " Rs." << beverage->cost() << std::endl;

    // Decorate the beverage with Milk
    beverage = std::make_shared<Milk>(beverage);
    std::cout << beverage->getDescription() << " Rs." << beverage->cost() << std::endl;

    // Further decorate the beverage with Mocha
    beverage = std::make_shared<Mocha>(beverage);
    std::cout << beverage->getDescription() << " Rs." << beverage->cost() << std::endl;

    return 0;
}