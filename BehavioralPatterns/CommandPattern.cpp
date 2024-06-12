//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Command Pattern
// The Command pattern encapsulates a request as an object, allowing parameterization of clients with different requests, queuing of requests, and logging of the requests.

// In this example, we have Command Interface: The Command class defines an interface for executing operations, it's the base class for all commands, providing a common execute() method.
// The ConcreteCommand class implements the Command interface and binds with the Receiver. It encapsulates a specific action to be performed by invoking a method on the Receiver.
// The Receiver class contains the actual implementation of the operations that can be performed. It's decoupled from the client and executes actions when called by a command.
// The Invoker class holds and executes commands. It doesn't know how the command will be executed; it just knows how to execute it.




#include <iostream>
#include <vector>
#include <memory>

// Command Interface: Defines an interface for executing operations.
class Command {
public:
    virtual void execute() = 0;
};

// Receiver: Contains the actual implementation of operations.
class Receiver {
public:
    void performAction() { // Perform the action.
        std::cout << "Receiver is performing action." << std::endl;
    }
};

// Concrete Command: Implements the Command interface and binds with the Receiver.
class ConcreteCommand : public Command {
private:
    std::unique_ptr<Receiver> receiver_;

public:
    ConcreteCommand(std::unique_ptr<Receiver> receiver) : receiver_(std::move(receiver)) {}

    void execute() override {
        receiver_->performAction(); // Execute the action on the Receiver.
    }
};

// Invoker: Holds and executes commands.
class Invoker {
private:
    std::vector<std::unique_ptr<Command>> commands_;

public:
    void addCommand(std::unique_ptr<Command> command) {
        commands_.push_back(std::move(command)); // Add command to the list.
    }

    void executeCommands() {
        for (auto& command : commands_) {
            command->execute();
        }
        commands_.clear();
    }
};

// Client
int main() {
    // Create receiver, command, and invoker
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();
    std::unique_ptr<ConcreteCommand> command = std::make_unique<ConcreteCommand>(std::move(receiver));
    std::unique_ptr<Invoker> invoker = std::make_unique<Invoker>();

    // Add command to the invoker
    invoker->addCommand(std::move(command));

    // Execute the command
    invoker->executeCommands();

    return 0;
}
