//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// State Pattern
// This pattern allows an object to change its behavior when its internal state changes. It's useful when an object's behavior depends on its state and transitions between states.

// In this example, State Pattern is used to allow the Machine object to change its behavior based on its current state. The `Machine` class holds a reference to a `State` object that represents its current state. 
// Each state (`OnState`, `OffState`, and `StandbyState`) implements the `State` interface and provides its own implementation of the `handleRequest` method. 
// The `Machine` class has methods to set its state and to handle requests, delegating the behavior to the current state. 
// This allows the `Machine` to change its behavior dynamically by changing its state without requiring conditional statements to check the current state.

#include <iostream>
#include <memory>

class Machine;

// State Interface
class State {
public:
    virtual ~State() {}
    virtual void handleRequest(Machine& machine) = 0;
};

// Concrete States
class OnState : public State {
public:
    void handleRequest(Machine& machine) override {
        std::cout << "Machine is ON now.\n";
    }
};

class OffState : public State {
public:
    void handleRequest(Machine& machine) override {
        std::cout << "Machine is OFF now.\n";
    }
};

class StandbyState : public State {
public:
    void handleRequest(Machine& machine) override {
        std::cout << "Machine is in Standby mode.\n";
    }
};

// Context
class Machine {
private:
    std::shared_ptr<State> currentState;
    std::shared_ptr<State> onState;
    std::shared_ptr<State> offState;
    std::shared_ptr<State> standbyState;

public:
    Machine() : onState(std::make_shared<OnState>()), offState(std::make_shared<OffState>()), standbyState(std::make_shared<StandbyState>())
    {
        currentState = offState;
    }

    void setState(std::shared_ptr<State> newState) {
        currentState = newState;
    }

    void handleRequest() {
        currentState->handleRequest(*this);
    }

    std::shared_ptr<State> getOnState() const {
        return onState;
    }
    
    std::shared_ptr<State> getOffState() const { 
        return offState;
    }
    
    std::shared_ptr<State> getStandbyState() const { 
        return standbyState; 
    }
};

int main() {
    Machine machine;

    machine.handleRequest(); // Machine is OFF now.

    machine.setState(machine.getOnState());
    machine.handleRequest(); // Machine is ON now.

    machine.setState(machine.getStandbyState());
    machine.handleRequest(); // Machine is in Standby mode.

    return 0;
}