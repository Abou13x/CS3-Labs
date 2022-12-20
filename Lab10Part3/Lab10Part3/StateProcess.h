//#include <iostream>
//#include <string>
//using std::cin; using std::cout; using std::endl; using std::string;
//
//class State;
//
//// context
//class Process {
//public:
//    Process();
//
//    // behaviors
//    void create();
//    void dispatch();
//    void suspend();
//    void exit();
//    void block();
//    void unblock();
//    int getId() {
//        return id_;
//    }
//    string report();
//
//    // changing the state of a process
//    void changeState(State* state) { state_ = state; }
//private:
//    State* state_;
//    static int id_;
//};
//int Process::id_ = 0;
//
//// absract state
//class State {
//public:
//    // provides default implementation
//    virtual void create(Process*) {}
//    virtual void dispatch(Process*) {}
//    virtual void suspend(Process*) {}
//    virtual void exit(Process*) {}
//    virtual void block(Process*) {}
//    virtual void unblock(Process*) {}
//    virtual string report() = 0;
//
//    void changeState(Process* p, State* s) {
//        p->changeState(s);
//    }
//};
//
//class Ready : public State {
//public:
//    static State* instance() {
//        static State* onlyInstance = new Ready;
//        return onlyInstance;
//    }
//
//    void dispatch(Process*) override;
//    string report() override {
//        return "ready";
//    }
//};
//
//class Running : public State {
//public:
//    static State* instance() {
//        static State* onlyInstance = new Running;
//        return onlyInstance;
//    }
//    void suspend(Process*) override;
//    void exit(Process*) override;
//    void block(Process*) override;
//
//    string report() override {
//        return "running";
//    }
//};
//
//class Blocked : public State {
//public:
//    static State* instance() {
//        static State* onlyInstance = new Blocked;
//        return onlyInstance;
//    }
//    void unblock(Process*) override;
//    string report() override {
//        return "blocked";
//    }
//};
//
////class Exit : public State {
////public:
////    static State* instance() {
////        static State* onlyInstance = new Exit;
////        return onlyInstance;
////    }
////    void exit(Process*) override;
////    string report() override {
////        return "exit";
////    }
////};
//// state transitions member functions
//// Ready
//
//void Ready::dispatch(Process* p) {
//    changeState(p, Running::instance());
//}
//
////Running
//void Running::suspend(Process* p) {
//    changeState(p, Ready::instance());
//}
//void Running::block(Process* p) {
//    changeState(p, Blocked::instance());
//}
////Exiting
//void Running::exit(Process* p) {
//    //changeState(p, Exit::instance());
//    cout << "process deleted";
//    delete p;
//}
//
////Blocked
//void Blocked::unblock(Process* p) {
//    changeState(p, Ready::instance());
//}
//
//// Process member functions
//Process::Process() {
//    state_ = Ready::instance();
//    id_++;
//}
//
//// handles/behaviors
//void Process::dispatch() { state_->dispatch(this); }
//void Process::suspend() { state_->suspend(this); }
//void Process::exit() { state_->exit(this); }
//void Process::block() { state_->block(this); }
//void Process::unblock() { state_->unblock(this); }
//void Process::create() { state_->create(this); }
//string Process::report() { return state_->report(); }
//
//#pragma once
