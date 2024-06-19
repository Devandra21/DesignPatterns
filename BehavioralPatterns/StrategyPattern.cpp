//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Strategy Pattern
// This pattern defines a family of algorithms, encapsulates each algorithm, and makes them interchangeable. It allows selecting an algorithm at runtime.

// In this example, the Strategy Pattern is used to define a family of algorithms (addition, subtraction, multiplication) which are encapsulated in their respective
// concrete strategy classes (ConcreteStrategyAdd, ConcreteStrategySubtract, ConcreteStrategyMultiply).
// The Context class is configured with a Strategy object and can switch between different strategies at runtime using the setStrategy method.

#include <iostream>
#include <memory>

// Strategy interface
class Strategy {
public:
    virtual void execute(int a, int b) = 0;
    virtual ~Strategy() = default;
};

// Concrete Strategies
class ConcreteStrategyAdd : public Strategy {
public:
    void execute(int a, int b) override {
        std::cout << "Result of addition: " << (a + b) << std::endl;
    }
};

class ConcreteStrategySubtract : public Strategy {
public:
    void execute(int a, int b) override {
        std::cout << "Result of subtraction: " << (a - b) << std::endl;
    }
};

class ConcreteStrategyMultiply : public Strategy {
public:
    void execute(int a, int b) override {
        std::cout << "Result of multiplication: " << (a * b) << std::endl;
    }
};

// Context
class Context {
private:
    std::unique_ptr<Strategy> strategy;

public:
    Context(std::unique_ptr<Strategy> strategy) : strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<Strategy> strategy) {
        this->strategy = std::move(strategy);
    }

    void executeStrategy(int a, int b) {
        if (strategy) {
            strategy->execute(a, b);
        }
    }
};

int main() {
    // Initialize strategies
    std::unique_ptr<ConcreteStrategyAdd> add = std::make_unique<ConcreteStrategyAdd>();
    std::unique_ptr<ConcreteStrategySubtract> subtract = std::make_unique<ConcreteStrategySubtract>();
    std::unique_ptr<ConcreteStrategyMultiply> multiply = std::make_unique<ConcreteStrategyMultiply>();

    // Use strategies
    Context context(std::move(add));
    context.executeStrategy(5, 3);

    context.setStrategy(std::move(subtract));
    context.executeStrategy(5, 3);

    context.setStrategy(std::move(multiply));
    context.executeStrategy(5, 3);

    return 0;
}
