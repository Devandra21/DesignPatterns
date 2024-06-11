//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Chain of Responsibility Pattern
// Creates a chain of receiver objects for a request, allowing the sender to pass the request along the chain until it's handled or the end of the chain is reached.

// In this example, ConcreteHandler1 and ConcreteHandler2 are concrete implementations of the Handler interface. Each handler has its own specific range of requests it can handle. If a request falls within that range, the handler handles it, otherwise, it delegates the request to the next handler in the chain.

#include <iostream>
#include <memory>

// Handler interface
class Handler {
public:
    virtual void handleRequest(int request) = 0;
    virtual void setNextHandler(std::unique_ptr<Handler> nextHandler) = 0;
};

// Concrete Handlers
class ConcreteHandler1 : public Handler {
    std::unique_ptr<Handler> nextHandler_;
private:

public:
    ConcreteHandler1() : nextHandler_(nullptr) {};

    void handleRequest(int request) override {
        if (request >= 0 && request < 10) {
            std::cout << "Request " << request << " handled by ConcreteHandler1." << std::endl;
        } else if (nextHandler_ != nullptr) {
            nextHandler_->handleRequest(request);
        } else {
            std::cout << "Request " << request << " can't be handled." << std::endl;
        }
    }

    void setNextHandler(std::unique_ptr<Handler> nextHandler) override {
        nextHandler_ = std::move(nextHandler);
    }
};

class ConcreteHandler2 : public Handler {
private:
    std::unique_ptr<Handler> nextHandler_;

public:
    ConcreteHandler2() : nextHandler_(nullptr) {};

    void handleRequest(int request) override {
        if (request >= 10 && request < 20) {
            std::cout << "Request " << request << " handled by ConcreteHandler2." << std::endl;
        } else if (nextHandler_ != nullptr) {
            nextHandler_->handleRequest(request);
        } else {
            std::cout << "Request " << request << " can't be handled." << std::endl;
        }
    }

    void setNextHandler(std::unique_ptr<Handler> nextHandler) override {
        nextHandler_ = std::move(nextHandler);
    }
};

// Client
int main() {
    // Create handlers
    std::unique_ptr<Handler> handler1 = std::make_unique<ConcreteHandler1>();
    std::unique_ptr<Handler> handler2 = std::make_unique<ConcreteHandler2>();;

    // Set up the chain of responsibility
    handler1->setNextHandler(std::move(handler2));

    // Handle requests
    handler1->handleRequest(5);
    handler1->handleRequest(12);
    handler1->handleRequest(25);

    return 0;
}
