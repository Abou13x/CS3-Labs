// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Abou Diomande
// 11/2/2022

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
	Fill(char fillChar, char borderChar) : fillChar_(fillChar), borderChar_(borderChar) {}
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;
	virtual ~Fill() {}
protected:
	char fillChar_;
	char borderChar_;
};

// concrete body
class Hollow : public Fill {
public:
	Hollow(char fillChar) :Fill(fillChar, ' ') {}
	char getBorder() override { return fillChar_; }
	char getInternal() override { return ' '; }
	~Hollow() override {}
};


// another concrete body
class Filled : public Fill {
public:
	Filled(char fillChar) :Fill(fillChar, fillChar) {}
	Filled(char fillChar, char borderChar) :Fill(fillChar, borderChar) {}
	char getBorder() override { return fillChar_; }
	char getInternal() override { return fillChar_; }
	~Filled() override {}
};

// abstract handle
class Figure {
public:
	Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
	virtual void draw() = 0;
	virtual ~Figure() {}
protected:
	int size_;
	Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
	Square(int size, Fill* fill) : Figure(size, fill) {}
	void draw() override;

};

void Square::draw() {
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j)
			if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
				cout << fill_->getBorder();
			else
				cout << fill_->getInternal();
		cout << endl;
	}
}

class FullyFilled : public Filled {
public:
	FullyFilled(char fillChar,char borderChar) :Filled(fillChar, borderChar) {
		//borderChar_ = borderChar;
	}
	char getBorder() override { return borderChar_; }
	char getInternal() override { return fillChar_; }
	~FullyFilled() override {}
};

class RandomFilled : public Filled {
public:
	RandomFilled(char fillChar, char borderChar) : Filled(fillChar, borderChar){}
	char getBorder() override {
		int rnd = rand()%2;

		return (rnd == 0) ? borderChar_ : fillChar_; 
	}
	char getInternal() override {
		int rnd = rand() % 2;
		return (rnd == 0) ? borderChar_ : fillChar_;
	}
	~RandomFilled() override {}
};


int main() {
	srand(time(NULL));
	/*
	Fill* hollowPaintQ = new Hollow('Q');
	Fill* filledPaintStar = new Filled('*');


	Figure *smallBox = new Square(5, hollowPaintQ);
	Figure *bigBox = new Square(15, filledPaintStar);

	smallBox->draw();
	cout << endl;
	bigBox -> draw();
	*/


	// ask user for figure parameters
	cout << "Enter fill character: ";
	char fchar; cin >> fchar;
	cout << "Filled or hollow? [f/h] ";
	char ifFilled; cin >> ifFilled;
	cout << "Enter size: "; int size; cin >> size;


	Figure* userBox = new Square(size, ifFilled == 'f' ?
		static_cast<Fill*>(new Filled(fchar)) :
		static_cast<Fill*>(new Hollow(fchar))
	);


	/*
	Figure *userBox = new Square(size,
			ifFilled == 'f'? new Filled(fchar): new Hollow(fchar)
				);

	*/


	//Figure* userBox = ifFilled == 'f' ?
	//	new Square(size, new Filled(fchar)) :
	//	new Square(size, new Hollow(fchar));


	userBox->draw();
	cout << endl;



	delete userBox;

	cout << "*****Fully FILL*****" << endl;
	cout << "Enter border: ";
	char fullyFilledBorder; cin >> fullyFilledBorder;
	cout << "Enter fill: ";
	char fullyFilledFill; cin >> fullyFilledFill;
	cout << endl;

	userBox = new Square(size, static_cast<Fill*>(new FullyFilled(fullyFilledFill, fullyFilledBorder)));
	userBox->draw();
	cout << endl;

	delete userBox;

	cout << "*****Random FILL*****" << endl;
	cout << "Enter border: ";
	char randomFilledBorder; cin >> randomFilledBorder;
	cout << "Enter fill: ";
	char randomFilledFill; cin >> randomFilledFill;
	cout << endl;

	userBox = new Square(size, static_cast<Fill*>(new RandomFilled(randomFilledFill, randomFilledBorder)));
	userBox->draw();
	cout << endl;

	delete userBox;

}