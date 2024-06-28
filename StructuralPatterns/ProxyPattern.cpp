//**************************************************************************************
//   This code is just for easier understanding
//   Author:  Devandra Jain
//   For any feedback, please reach out to me at: nittdevandra2017@gmail.com
//**************************************************************************************

// Proxy Pattern
// The Proxy pattern provides a surrogate or placeholder for another object to control access to it, used for lazy initialization, access control, and logging purposes.

// In this example, IDatabase is the Subject interface that declares the common operations (e.g., `query` method) to be implemented by both the RealSubject (Database) and the Proxy (DatabaseProxy).
// Database is the RealSubject that performs the actual work (e.g., connecting to and querying the database). It simulates an expensive initialization process during its construction.
// DatabaseProxy is the Proxy that controls access to the RealSubject. It holds a pointer to the Database object and performs lazy initialization by creating the Database instance only when it is needed (i.e., when the first query is made).

#include <iostream>
#include <memory>

// Subject Interface
class IDatabase {
public:
    virtual void query(const std::string& sql) = 0;
    virtual ~IDatabase() = default;
};

// RealSubject
class Database : public IDatabase {
public:
    Database() {
        // Simulating expensive initialization (e.g., connecting to a database)
        std::cout << "Connecting to the database..." << std::endl;
    }

    void query(const std::string& sql) override {
        std::cout << "Executing query: " << sql << std::endl;
    }
};

// Proxy
class DatabaseProxy : public IDatabase {
public:
    DatabaseProxy() : realDatabase(nullptr) {}

    void query(const std::string& sql) override {
        if (!realDatabase) {
            realDatabase = std::make_unique<Database>();
        }
        realDatabase->query(sql);
    }

private:
    std::unique_ptr<Database> realDatabase;
};

int main() {
    std::unique_ptr<IDatabase> db = std::make_unique<DatabaseProxy>();

    // Database connection is not established yet

    // The first query triggers the actual database connection
    db->query("SELECT * FROM users");

    // Subsequent queries use the already established connection
    db->query("SELECT * FROM orders");

    return 0;
}