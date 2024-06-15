//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Memento Pattern
// This pattern allows you to capture an object's internal state and save it externally so that the object can be restored to that state later.

// In this example, Memento Pattern is used to save and restore the state of an object.
// class Memento: Stores the internal state of the Originator. It is immutable and only accessible to the Originator.
// class Originator: Creates a Memento containing a snapshot of its current state and uses the Memento to restore its state.
// class Caretaker: Responsible for keeping track of multiple Mementos. It does not modify or inspect the Mementos.


#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Memento
class Memento {
private:
    std::string state;

public:
    Memento(const std::string& state) : state(state) {}

    const std::string& getState() const {
        return state;
    }
};

// Originator
class Originator {
private:
    std::string state;

public:
    void setState(const std::string& state) {
        this->state = state;
    }

    const std::string& getState() const {
        return state;
    }

    std::shared_ptr<Memento> createMemento() const {
        return std::make_shared<Memento>(state);
    }

    void restoreMemento(const std::shared_ptr<Memento>& memento) {
        if (memento) {
            state = memento->getState();
        }
    }
};

// Caretaker
class Caretaker {
private:
    std::vector<std::shared_ptr<Memento>> mementos;

public:
    void addMemento(const std::shared_ptr<Memento>& memento) {
        mementos.push_back(memento);
    }

    std::shared_ptr<Memento> getMemento(size_t index) const {
        if (index < mementos.size()) {
            return mementos[index];
        }
        return nullptr;
    }
};

int main() {
    Originator originator;
    Caretaker caretaker;

    originator.setState("State 1");
    caretaker.addMemento(originator.createMemento());

    originator.setState("State 2");
    caretaker.addMemento(originator.createMemento());

    originator.setState("State 3");

    std::cout << "Current state: " << originator.getState() << std::endl;

    originator.restoreMemento(caretaker.getMemento(0));
    std::cout << "Restored to state: " << originator.getState() << std::endl;

    originator.restoreMemento(caretaker.getMemento(1));
    std::cout << "Restored to state: " << originator.getState() << std::endl;

    return 0;
}