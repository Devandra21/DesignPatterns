//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Mediator  Pattern
// Mediator pattern centralizes communication between objects, reducing dependencies between them. Objects communicate through the mediator instead of directly with each other.

// In this example, The Mediator interface abstracts the communication logic, defining a method for sending messages between colleagues.
// ConcreteColleague1 and ConcreteColleague2 are concrete implementations of the Colleague interface, each capable of sending messages through the mediator.
// ConcreteMediator acts as the central hub for communication. It maintains references to concrete colleagues and routes messages between them based on the sender and receiver.
// This design promotes loose coupling between colleagues, as they interact solely through the mediator, reducing dependencies and simplifying maintenance.



#include <iostream>
#include <string>
#include <memory>

class Colleague;

// Mediator interface
class Mediator {
public:
    virtual void sendMessage(Colleague* colleague, const std::string& message) const = 0;
};

// Colleague interface
class Colleague {
protected:
    std::shared_ptr<Mediator> mediator;

public:
    Colleague(std::shared_ptr<Mediator> mediator) : mediator(mediator) {}

    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message) = 0;
};

// Concrete Mediator
class ConcreteMediator : public Mediator {
private:
    std::shared_ptr<Colleague> colleague1;
    std::shared_ptr<Colleague> colleague2;

public:
    void setColleague1(std::shared_ptr<Colleague> colleague) {
        colleague1 = colleague;
    }

    void setColleague2(std::shared_ptr<Colleague> colleague) {
        colleague2 = colleague;
    }

    void sendMessage(Colleague* colleague, const std::string& message) const override {
        if (colleague == colleague1.get()) {
            colleague2->receive(message);
        } else {
            colleague1->receive(message);
        }
    }
};

// Concrete Colleague
class ConcreteColleague1 : public Colleague {
public:
    ConcreteColleague1(std::shared_ptr<Mediator> mediator) : Colleague(mediator) {}

    void send(const std::string& message) override {
        mediator->sendMessage(this, message);
    }

    void receive(const std::string& message) override {
        std::cout << "Concrete Colleague 1 received: " << message << std::endl;
    }
};

// Concrete Colleague
class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(std::shared_ptr<Mediator> mediator) : Colleague(mediator) {}

    void send(const std::string& message) override {
        mediator->sendMessage(this, message);
    }

    void receive(const std::string& message) override {
        std::cout << "Concrete Colleague 2 received: " << message << std::endl;
    }
};

int main() {
    std::shared_ptr<ConcreteMediator> mediator = std::make_shared<ConcreteMediator>();
    std::shared_ptr<ConcreteColleague1> colleague1 =  std::make_shared<ConcreteColleague1>(mediator);
    std::shared_ptr<ConcreteColleague2> colleague2 =  std::make_shared<ConcreteColleague2>(mediator);

    mediator->setColleague1(colleague1);
    mediator->setColleague2(colleague2);

    colleague1->send("Hello, colleague2!");
    colleague2->send("Hello, colleague1!");

    return 0;
}
