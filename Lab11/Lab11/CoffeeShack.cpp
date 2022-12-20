
//Abou Diomande
#include "Barista.h";


int main() {
	srand(time(NULL));
	const int number = 4;

	JuniorBarista barista(new SeniorBarista(new Manager));
	vector <Customer*> allCustomers;
	for (int i = 0; i < number; i++) {
		//adding 4 customers
		allCustomers.push_back(new Customer());
	}

	for (auto customers : allCustomers) {
		barista.processOrder(customers);
		//randomly notifying all customers when an order is ready
		int randomValue = rand() % 2;
		//cout << "Random Value " << randomValue<< endl;
		if (randomValue == 1) {
			barista.notifyCustomers();
		}

	}
}

