#include "Drink.h";


int main() {
	Drink* drink = new Drink;

	char drinkSize;
	char topping;
	int price;
	string customerName;
	string order = "";
	cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?";
	cin >> drinkSize;
	cout << endl;
	drink->setDrinkSize(drinkSize);
	price = drink->getPrice();
	order = drink->getName();

	//getting toppings
	do { 
		cout << "Would you like to add [s]ugar, [c]ream, milk [f]oam,or [d]one? ";
		cin >> topping;
		cout << endl;
		if (topping == 's') {
			Sugar sugar(drink);
			price += drink->getPrice();
			order += drink->getName();
		}
		if (topping == 'c') {
			Cream cream(drink);
			price += drink->getPrice();
			order += drink->getName();
		}
		if (topping == 'f') {
			MilkFoam milkFoam(drink);
			price += drink->getPrice();
			order += drink->getName();
		}
		

	} while (topping != 'd');

	drink->setDrinkName(order);
	drink->setPrice(price);

	cout << "Can I get your name?";
	cin >> customerName;
	cout << endl;

	cout << customerName << ", your" << drink->getName() << " is ready. It will be $" << drink->getPrice() << ", please" << endl;
}

