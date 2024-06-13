//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Interpreter Pattern
// This pattern is used to define a grammar for interpreting a language and provides an interpreter that interprets sentences in the defined language.

// In this example, Interpreter Pattern is used to create a language interpreter for evaluating boolean expressions.
// class Context: Represents the state in which the expressions are evaluated. It holds variables and their values.
// class Expression (Abstract class): Defines an interface for interpreting expressions. Contains a method for interpretation and cloning.
// class TerminalExpression: Represents a variable in the boolean expression. It retrieves the value of the variable from the context.
// Nonterminal Expressions(OrExpression, AndExpression): These are the composite expressions formed by combining multiple expressions, OrExpression and AndExpression evaluate boolean OR and AND operations respectively.


#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Context
class Context {
public:
    bool getVariable(const std::string& name) {
        return variables[name];
    }

    void setVariable(const std::string& name, bool value) {
        variables[name] = value;
    }

private:
    std::unordered_map<std::string, bool> variables;
};

// Abstract Expression
class Expression {
public:
    virtual bool interpret(Context& context) = 0;
    virtual std::unique_ptr<Expression> clone() const = 0;
};

// Terminal Expression
class TerminalExpression : public Expression {
private:
    std::string variable;

public:
    TerminalExpression(const std::string& variable) : variable(variable) {}

    bool interpret(Context& context) override {
        return context.getVariable(variable);
    }

    std::unique_ptr<Expression> clone() const override {
        return std::make_unique<TerminalExpression>(*this);
    }
};

// Nonterminal Expression
class OrExpression : public Expression {
private:
    std::unique_ptr<Expression> expr1;
    std::unique_ptr<Expression> expr2;

public:
    OrExpression(std::unique_ptr<Expression> expr1, std::unique_ptr<Expression> expr2)
        : expr1(std::move(expr1)), expr2(std::move(expr2)) {}

    bool interpret(Context& context) override {
        return expr1->interpret(context) || expr2->interpret(context);
    }

    std::unique_ptr<Expression> clone() const override {
        return std::make_unique<OrExpression>(expr1->clone(), expr2->clone());
    }
};

// Nonterminal Expression
class AndExpression : public Expression {
private:
    std::unique_ptr<Expression> expr1;
    std::unique_ptr<Expression> expr2;

public:
    AndExpression(std::unique_ptr<Expression> expr1, std::unique_ptr<Expression> expr2)
        : expr1(std::move(expr1)), expr2(std::move(expr2)) {}

    bool interpret(Context& context) override {
        return expr1->interpret(context) && expr2->interpret(context);
    }

    std::unique_ptr<Expression> clone() const override {
        return std::make_unique<AndExpression>(expr1->clone(), expr2->clone());
    }
};

int main() {
    Context context;
    context.setVariable("A", true);
    context.setVariable("B", false);

    std::unique_ptr<Expression> expr1 = std::make_unique<TerminalExpression>("A");
    std::unique_ptr<Expression> expr2 = std::make_unique<TerminalExpression>("B");
    std::unique_ptr<Expression> expr3 = std::make_unique<OrExpression>(expr1->clone(), expr2->clone());
    std::unique_ptr<Expression> expr4 = std::make_unique<AndExpression>(expr1->clone(), expr2->clone());

    std::cout << "A OR B is " << expr3->interpret(context) << std::endl;
    std::cout << "A AND B is " << expr4->interpret(context) << std::endl;

    return 0;
}
