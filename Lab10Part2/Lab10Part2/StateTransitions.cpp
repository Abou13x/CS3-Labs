#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process {
public:
    Process();

    // behaviors
    void create();
    void dispatch();
    void suspend();
    void exit();
    void block();
    void unblock();
    string report();

    // changing the state of a process
    void changeState(State* state) { state_ = state; }
    //need a destructor
private:
    State* state_;
    static int id_;
};
int Process::id_ = 0;

// absract state
class State {
public:
    // provides default implementation
    virtual void create(Process*) {}
    virtual void dispatch(Process*) {}
    virtual void suspend(Process*) {}
    virtual void exit(Process*) {}
    virtual void block(Process*) {}
    virtual void unblock(Process*) {}
    virtual string report() = 0;

    void changeState(Process* p, State* s) {
        p->changeState(s);
    }
};

class Ready : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }
 
        void dispatch(Process*) override;
        string report() override {
            return "ready";
        }
};

class Running : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Running;
        return onlyInstance;
    }
        void suspend(Process*) override;
        void exit(Process*) override;
        void block(Process*) override;
    
        string report() override {
            return "running";
        }
};

class Blocked : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Blocked;
        return onlyInstance;
    }
        void unblock(Process*) override;
        string report() override {
            return "blocked";
        }
};

// state transitions member functions
// Ready

void Ready::dispatch(Process* p) {
    changeState(p, Running::instance());
}

//Running
void Running::suspend(Process* p) {
    changeState(p, Ready::instance());
}
void Running::block(Process* p) {
    changeState(p, Blocked::instance());
}
void Running::exit(Process* p) {
    delete p;
    return;
}

//Blocked
void Blocked::unblock(Process* p) {
    changeState(p, Ready::instance());
}

// Process member functions
Process::Process() { state_ = Ready::instance(); }

// handles/behaviors
void Process::dispatch() { state_->dispatch(this); }
void Process::suspend() { state_->suspend(this); }
void Process::exit() { state_->exit(this); }
void Process::block() { state_->block(this); }
void Process::unblock() { state_->unblock(this); }
void Process::create() { state_->create(this); }
string Process::report() { return state_->report(); }


int main() {
    Process process;

    cout << "Dispatch [d]" << endl;
    cout << "Suspend [s]" << endl;
    cout << "Exit [e]" << endl;
    cout << "Block [b]" << endl;
    cout << "unblock [u]" << endl;

    cout << "Process is " << process.report() << endl;
    
    while (process.report() != "exit") {
        cout << "What would you like process to do: ";
        char action; cin >> action;
        if (action == 'd')
            process.dispatch();
        else if (action == 's')
            process.suspend();
        else if (action == 'e')
            process.exit();
        else if (action == 'b')
            process.block();
        else if (action == 'u')
            process.unblock();
        else
            cout << "Invalid input";
        cout << "Process is " << process.report() << endl;
    }
}

