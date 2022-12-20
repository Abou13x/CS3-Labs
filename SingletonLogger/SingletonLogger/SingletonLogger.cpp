// example opening file for appending
// Abou Diomande
// 10/19/2022

#include <fstream>
#include<string>

using namespace std;
using std::string;

class logger {
public:
	static logger& instance() {
		static logger s;
		return s;
	}
	void report(const string& s) {
		std::ofstream fout;
		fout.open("Log.txt", std::fstream::out | std::fstream::app);
		//fout << "more lorem ipsum" << std::endl;
		fout << s << std::endl;
		fout.close();
	}

	~logger() {}

private:
	logger() {}
	logger(const string&){}
	logger& operator = (const string&){}
};


void secondCall() {
	logger::instance().report("second login");
}




int main() {
	logger::instance().report("first login");
	secondCall();

}