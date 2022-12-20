
#include <iostream>
#include<queue>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
using std::cout; using std::endl; using std::string; using std::cin;
class State;
//base class
class Process {
public:
	Process();
	Process(State* state) : state_(state) {
		//keeping track of unique process ID
		id_++;
		id2_ = id_;
	}
	virtual Process* clone() {
	   return new Process(state_);
	}
	void create();
	void dispatch();
	void suspend();
	void exit();
	void block();
	void unblock();
	string report();
	void print() {
		cout << "PID " << id2_ << " state: ";
	}
	int getID()const {
		return id2_;
	}

	// changing the state of a process
	void changeState(State* state) { state_ = state; }
protected:
	State* state_;
	static int id_; 
	int id2_;
};
int Process::id_ = 0;



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

class Exit : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Exit;
		return onlyInstance;
	}
	//void exit(Process*) override;
	string report() override {

		return "exited";
	}
};


void Ready::dispatch(Process* p) {
	cout << "Dispatching..." << endl;
	changeState(p, Running::instance());
}

//Running
void Running::suspend(Process* p) {
	cout << "Suspending..." << endl;
	changeState(p, Ready::instance());
}
void Running::block(Process* p) {
	cout << "Blocking..." << endl;
	changeState(p, Blocked::instance());
}
//Exiting
void Running::exit(Process* p) {
	cout << "Exiting..." << endl;
	changeState(p, Exit::instance());
}

//Blocked
void Blocked::unblock(Process* p) {
	cout << "Unblocking..." << endl;
	changeState(p, Ready::instance());
}

Process::Process(){
	state_ = Ready::instance();
}


// handles/behaviors
void Process::dispatch() { state_->dispatch(this); }
void Process::suspend() { state_->suspend(this); }
void Process::exit() { state_->exit(this); }
void Process::block() { state_->block(this); }
void Process::unblock() { state_->unblock(this); }
void Process::create() { state_->create(this); }
string Process::report() { return state_->report(); }

int main() {
	srand(time(NULL));
queue<Process*> blockedQueue;
queue<Process*> readyQueue;
Process process1;

for (int i = 0; i < 4; ++i) {
	readyQueue.push(process1.clone());
	 cout << "PID " << i+1<< ": created" << endl;
	 cout << "PID " << i+1<< " state: ";
	cout<< readyQueue.front()->report();
	cout << endl;

}

cout << "----------------- scheduler ------------------" << endl;
while (!(readyQueue.empty() && blockedQueue.empty())) {

	if (!readyQueue.empty()) {
		if (readyQueue.front()->report() == "ready") {
			readyQueue.front()->dispatch();
			readyQueue.front()->print();
			cout << readyQueue.front()->report() << endl;
		}
		else {
			//random value to determine the state
			int rnd = rand() % 3;
			//second call
			if (rnd == 0) {
				//process is blocked and sent to blocked queue
				readyQueue.front()->block();
				readyQueue.front()->print();
				cout << readyQueue.front()->report() << endl;
				blockedQueue.push(readyQueue.front());
				readyQueue.pop();
				cout << endl;
			}

			if (rnd == 1) {
				//process is suspended and sent to the back of ready queue
				readyQueue.front()->suspend();
				readyQueue.front()->print();
				cout << readyQueue.front()->report() << endl;
				readyQueue.push(readyQueue.front());
				readyQueue.pop();
				cout << endl;
			}

			if (rnd == 2) {
				//process exit and is deleted from ready queue
				readyQueue.front()->exit();
				readyQueue.front()->print();
				cout << readyQueue.front()->report() << endl;
				readyQueue.pop();
				cout << endl;
			}
		}
		
	}

	//removing blocked precesses from blocked queue
	if (!blockedQueue.empty()) {
		int rnd = rand() % 2;
		if (rnd == 1) {
			blockedQueue.front()->unblock();
			blockedQueue.front()->print();
			cout << blockedQueue.front()->report() << endl;
			readyQueue.push(blockedQueue.front());
			blockedQueue.pop();
		}
	}


	if (readyQueue.empty()) {
		cout << "The ready queue is empty" << endl;
	}

}

  cout << "All processes exited." << endl;

}


