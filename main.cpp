#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

// clasa de baza a programului
class Car {
	string type;
	int fuel; // 1 for petrol and 2 for diesel, no electric
	int gearBox; // 1 for atuomatic and 2 for manual
	float engineCapacity; // can be 1.6, 2.0, 3.0, 4.0, 5.0 L
public:
	Car(const char *str) {
		type.assign(str);
	}
	Car(const char *str, int f, int g, float e) {
		type.assign(str);
		fuel = f;
		gearBox = g;
		engineCapacity = e;
	}
	~Car() {
		type.erase(type.begin(), type.end());
		//cout << "Destructor for class Car" << endl;
	}
	Car(const Car& ob) {
		type.erase(type.begin(), type.end());
		type = ob.type;
		fuel = ob.fuel;
		gearBox = ob.gearBox;
		engineCapacity = ob.engineCapacity;
	}
	virtual string get_Car_Type() {
		return type;
	}
	virtual int get_Fuel_Type() {
		return fuel;
	}
	virtual int get_GearBox_Type() {
		return gearBox;
	}
	virtual float get_Engine_Capacity() {
		return engineCapacity;
	}
	virtual void read(istream& in) {
		cout << "The car type is: " << type << endl;
		while (true) {
			cout << "The fuel type you want (1 for petrol, 2 for diesel): ";
			int f;
			in >> f;
			try {
				if (f < 1 || f > 2)
					throw f;
				else {
					fuel = f;
					break;
				}
			}
			catch (int val) {
				cout << "Exception, the fuel type must be either 1 for petrol or 2 for diesel." << endl;
			}
		}
		while (true) {
			cout << "The gear box you want (1 for automatic, 2 for manual): ";
			int g;
			in >> g;
			try {
				if (g < 1 || g > 2)
					throw g;
				else {
					gearBox = g;
					break;
				}
			}
			catch (int val) {
				cout << "Exception, the gearBox type must be either 1 for automatic or 2 for manual." << endl;
			}
		}
		while (true) {
			cout << "The engine capacity you want ( can be 1.6, 2.0, 3.0, 4.0, 5.0): ";
			float e;
			in >> e;
			try {
				if (e != 1.6 && e != 2.0 && e != 3.0 && e != 4.0 && e != 5.0)
					throw e;
				else {
					engineCapacity = e;
					break;
				}
			}
			catch (float val) {
				cout << "Exception, the engine Capacity must be a value from this selection: 1.6, 2.0, 3.0, 4.0, 5.0." << endl;
			}
		}
		return;
	}
	virtual void print(ostream& out) {
		out << "The car type is: " << type << "." << endl;
		if (fuel == 1)
			out << "The fuel type is: " << "petrol" << endl;
		else if (fuel == 2) out << "The fuel type is: " << "diesel" << endl;
		if (gearBox == 1)
			out << "The gear box is: " << "automatic" << endl;
		else if (gearBox == 2) out << "The gear Box is: " << "manual" << endl;
		out << "The engine capacity is: " << engineCapacity << " L" << endl;

	}
	friend istream& operator>>(istream&, Car&);
	friend ostream& operator<<(ostream&, Car);
	Car& operator=(const Car&);
};

istream& operator>>(istream& in, Car& ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, Car ob) {
	ob.print(out);
	return out;
}

Car& Car :: operator=(const Car& ob1) {
	type.erase(type.begin(), type.end());
	type = ob1.type;
	fuel = ob1.fuel;
	gearBox = ob1.gearBox;
	engineCapacity = ob1.engineCapacity;
	return *this;
}

class Coupe : public Car {
	 static int nr_models;
public:
	Coupe() : Car("Coupe") {
		// nr models incrementat aici
	}
	~Coupe() {
		//cout << "Destructor for class Coupe" << endl;
	}
	Coupe(const Coupe& ob) : Car(ob) {
	}
	string get_Car_Type() {
		return this->Car::get_Car_Type();
	}
	static int get_NrModels() {
		return nr_models;
	}
	static void set_NrModels(int value) {
		Coupe :: nr_models = value;
	}
	void read(istream& in) {
		this->Car::read(in);
	}
	void print(ostream& out) {
		this->Car::print(out);
		out << "The number of models for the Coupe is: " << nr_models << endl;
	}
	friend istream& operator>>(istream&, Coupe&);
	friend ostream& operator<<(ostream&, Coupe);
	Coupe& operator=(const Coupe&);
};
int Coupe::nr_models;
istream& operator>>(istream& in, Coupe& ob) {
	ob.read(in);
	return in;
}
ostream& operator<<(ostream& out, Coupe ob) {
	ob.print(out);
	return out;
}

Coupe& Coupe :: operator=(const Coupe& ob) {
	this->Car::operator=(ob);
	return *this; 
}

class FourDoorCoupe : protected Car{
	static int nr_models;
public:
	FourDoorCoupe() : Car("Foor Door Coupe") {	// tipul pot sa il verific la rulare cu dinamic si static cast
	}
	FourDoorCoupe(int f, int g, float e) : Car("Four Door Coupe", f, g, e) {
	}
	~FourDoorCoupe() {
		//cout << "Destructor for FourDoorCoupe class" << endl;
	}
	FourDoorCoupe(const FourDoorCoupe& ob) : Car(ob) {
	}
	static int get_NrModels() {
		return nr_models;
	}
	static void set_NrModels(int value) {
		nr_models = value;
	}
	void read(istream& in) {
		this->Car::read(in);
	}
	void print(ostream& out) {
		this->Car::print(out);
		out << "The number of models for the Four Door Coupe is: " << nr_models << endl;
	}
	friend ostream& operator<<(ostream&, FourDoorCoupe);
	friend istream& operator>>(istream&, FourDoorCoupe&);
	FourDoorCoupe& operator=(const FourDoorCoupe&);
};
int FourDoorCoupe::nr_models;

istream& operator>>(istream& in, FourDoorCoupe& ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, FourDoorCoupe ob) {
	ob.print(out);
	return out;
}

FourDoorCoupe& FourDoorCoupe :: operator=(const FourDoorCoupe& ob) {
	this->Car :: operator=(ob);
	return *this;
}

class HotHatch : protected Car {
	static int nr_models;
public:
	HotHatch() : Car("Hot-Hatch") {
	}
	HotHatch(int f, int g, float e) : Car("Hot-Hatch") {
	}
	~HotHatch() {
		//cout << "Destructor for HotHatch class." <<endl;
	}
	HotHatch(const HotHatch& ob) : Car(ob) {
	}
	static int get_NrModels() {
		return nr_models;
	}
	static void set_NrModels(int value) {
		HotHatch::nr_models = value;
	}
	void read(istream& in) {
		this->Car::read(in);
	}
	void print(ostream& out) {
		this->Car::print(out);
		out << "The number of models for the Hot Hatch is: " << nr_models << endl;
	}
	friend ostream& operator<<(ostream&, HotHatch);
	friend istream& operator>>(istream&, HotHatch&);
	HotHatch& operator=(const HotHatch&);
};
int HotHatch::nr_models;

istream& operator>>(istream& in, HotHatch& ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, HotHatch ob) {
	ob.print(out);
	return out;
}

HotHatch& HotHatch :: operator=(const HotHatch& ob) {
	this->Car::operator=(ob);
	return *this;
}

class Cabrio : protected Car {
	static int nr_models;
	int roof_type; // 1 for metalic, 2 for textile
public:
	Cabrio() : Car("Cabrio") {
	}
	Cabrio(int f, int g, float e, int roof) : Car("Cabrio", f, g, e) {
		roof_type = roof;
	}
	~Cabrio() {
		//cout << "Destructor for Cabrio class." <<endl;
	}
	Cabrio(const Cabrio& ob) : Car(ob) {
		roof_type = ob.roof_type;
	}
	static int get_NrModels() {
		return nr_models;
	}
	static void set_NrModels(int value) {
		Cabrio::nr_models = value;
	}
	int get_roofType() {
		return roof_type;
	}
	void set_RoofType(int value) {
		roof_type = value;
	}
	void read(istream& in) {
		this->Car::read(in);
		cout << "The type of roof you want is (1 for metalic, 2 for textile): ";
		in >> roof_type;
		// trateaza exceptia
	}
	void print(ostream& out) {
		this->Car::print(out);
		if (roof_type == 1)
			out << "The roof type is metalic." << endl;
		else if (roof_type == 2) out << "The roof type is textile." << endl;
		out << "The number of models for the Cabrio is: " << nr_models << endl;
	}
	friend ostream& operator<<(ostream&, Cabrio);
	friend istream& operator>>(istream&, Cabrio&);
	Cabrio& operator=(const Cabrio&);
};
int Cabrio::nr_models;

istream& operator>>(istream& in, Cabrio &ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, Cabrio ob) {
	ob.print(out);
	return out;
}

Cabrio& Cabrio :: operator=(const Cabrio& ob) {
	this->Car::operator=(ob);
	this->roof_type = ob.roof_type;
	return *this;
}

class Supersport : protected Car {
	static int nr_models;
public:
	Supersport() : Car("Supersport") {
	}
	Supersport(int f, int g, float e) : Car("Supersport", f, g, e) {
	}
	~Supersport() {
		//cout << "Destructor for Cabrio class." <<endl;
	}
	Supersport(const Supersport& ob) : Car(ob) {
	}
	static int get_NrModels() {
		return nr_models;
	}
	static void set_NrModels(int value) {
		Supersport::nr_models = value;
	}
	void read(istream& in) {
		this->Car::read(in);
	}
	void print(ostream& out) {
		this->Car::print(out);
		out << "The number of models for the Supersport is: " << nr_models << endl;
	}

	friend istream& operator>>(istream&, Supersport&);
	friend ostream& operator<<(ostream&, Supersport);
	Supersport& operator=(const Supersport&);
};
int Supersport::nr_models;

istream& operator>>(istream& in, Supersport& ob) {
	ob.read(in);
	return in;
}

ostream& operator<<(ostream& out, Supersport ob) {
	ob.print(out);
	return out;
}

Supersport& Supersport :: operator=(const Supersport& ob) {
	this->Car::operator=(ob);
	return *this;
}

template <class T = Car>
class Exposition {
	static int nrTotal;
	T** cars;
public:
	Exposition() {
		try {
			if (nrTotal < 0)
				throw nrTotal;
			else {
				cars = new T*[nrTotal];
				for (int i = 0; i < nrTotal; ++i) {
					cars[i] = new T[nrTotal];
				}
			}
		}
		catch (int nrTotal) {
			cout << "Exception, nrTotal must be a positive integer." << endl;
		}
	}
	~Exposition() {
		for (int i = 0; i < nrTotal; ++i) {
			delete[] cars[i];
		}
		delete[] cars;
	}
	static int get_nrTotal() {
		return nrTotal;
	}
	static void set_nrTotal(int value) {
		nrTotal = value;
	}
};
int Exposition<Car>::nrTotal;

template <>
class Exposition<char*>
{
	static int nrSuperTotal;
	static int sales;
	Supersport** stock;
	Supersport** sold;
public:
	Exposition() {
		stock = new Supersport*[nrSuperTotal];
		sold = new Supersport*[nrSuperTotal];
		for (int i = 0; i < nrSuperTotal; ++i)
		{
			*(stock + i) = new Supersport[nrSuperTotal];
			*(sold + i) = new Supersport[nrSuperTotal];
		}
	}
	/*~Exposition() {
		for (int i = 0; i < nrSuperTotal; ++i)
		{
			delete[] stock[i];
			delete[] sold[i];
		}
		delete[] stock;
		delete[] sold;
	}*/
	static int get_nrSuperTotal() {
		return Exposition<char*>::nrSuperTotal;
	}
	static void set_NrSuperTotal(int value) {
		Exposition <char*> :: nrSuperTotal = value;
	}
	static int get_nrSales() {
		return Exposition<char*>::sales;
	}
	static void set_nrSales(int value) {
		Exposition<char*>::sales = value;
	}
	void set_soldCar(Supersport x, int s) {
		*(*(sold + s)) = x;
	}
	Supersport get_stockCar(int value) {
		try {
			if (value > Exposition<char*>::get_nrSales())
				throw value;
			else return *(*(stock + value));
		}
		catch (int value) {
			cout << "Exception, value must be an smaller integer than sales." << endl;
		}
	}
	Supersport get_soldCar(int value) {
		try {
			if (value > Exposition<char*>::get_nrSales())
				throw value;
			else return *(*(sold + value));
		}
		catch (int value) {
			cout << "Exception, value must be an smaller integer than sales." << endl;
		}
	}
	friend static int operator-=(Exposition<char*>&, int);
};
int Exposition<char*> :: nrSuperTotal;
int Exposition<char*> ::sales;
static int operator-=(Exposition<char*> &ob, int value) {
	try {
		if (ob.nrSuperTotal - value < 0)
			throw value;
	}
	catch (int value) {
		cout << "Exception, value cannot be a bigger number than the number of Supersport cars in stock";
	}
	ob.nrSuperTotal = ob.nrSuperTotal - value;
	ob.sales += value;
	Supersport::set_NrModels(Supersport::get_NrModels() - value);
	return ob.nrSuperTotal;
}

void menu() {
	cout << "1. Details about the exposition." << endl;
	cout << "2. Possible car configurations." << endl;
	cout << "3. Buy a supersport's car." << endl;
	cout << "4. Sales informations." << endl;
	cout << "5. Exit exposition." << endl;
	return;
}

void details() {
	cout << "The total number of models is: " << Exposition<>::get_nrTotal() << endl;
	cout << "The number of models for the Coupe class is: " << Coupe::get_NrModels() << endl;
	cout << "The number of models for the Four Door Coupe class is: " << FourDoorCoupe::get_NrModels() << endl;
	cout << "The number of models for the Hot-Hatch class is: " << HotHatch::get_NrModels() << endl;
	cout << "The number of models for the Cabrio class is: " << Cabrio::get_NrModels() << endl;
	cout << "The number of models for the Supersport class is: " << Supersport::get_NrModels() << endl;
	cout << "________________________________________________________" << endl;
}

void configure() {
	Car* first;
	int selection;
	cout << "What kind of car do you preferr: " << endl;
	cout << "1. Coupe"<<endl;
	cout << "2. Four Door Coupe"<<endl;
	cout << "3. Hot-Hatch"<<endl;
	cout << "4. Cabrio"<<endl;
	cout << "5. Supersport"<<endl;
	cout << "Select: ";
	cin >> selection;
	try {
		if (selection < 1 || selection > 5)
			throw selection;
	}
	catch (int selection) {
		cout << "Exception, your selection must be a integer between 1 and 5." << endl;
		return;
	}
	switch (selection) {
	case 1: {
		Coupe a;
		first = static_cast<Car*>(&a);
		cin >> a;
		cout << "Your preferred configuration is: " << endl;
		cout << a;
		break;
	}
	case 2: {
		FourDoorCoupe a;
		cin >> a;
		cout << "Your preferred configuration is: " << endl;
		cout << a;
		break;
	}
	case 3: {
		HotHatch a;
		cin >> a;
		cout << "Your preferred configuration is: " << endl;
		cout << a;
		break;
	}
	case 4: {
		Cabrio a;
		cin >> a;
		cout << "Your preferred configuration is: " << endl;
		cout << a;
		break;
	}
	case 5: {
		Supersport a;
		cin >> a;
		cout << "Your preferred configuration is: " << endl;
		cout << a;
		break;
	}
	}
	cout << "________________________________________________________" << endl;

}
void buy(Exposition<char*> sal) {
	sal -= 1;
	Supersport a;
	cin >> a;
	//sal.set_soldCar(a, sal.get_nrSales());
	cout << a;
	cout << "________________________________________________________" << endl;
}

void info(Exposition<char*> sal) {
	cout << "The number of Supersport models available is: " << sal.get_nrSuperTotal() << endl;
	cout << "The number of sold Supersport models is: " << sal.get_nrSales() << endl;
	cout << "________________________________________________________" << endl;
}

int main()
{
	// Setting the number of models for each class
	Coupe::set_NrModels(50);
	FourDoorCoupe::set_NrModels(60);
	HotHatch::set_NrModels(40);
	Cabrio::set_NrModels(35);
	Supersport::set_NrModels(30);
	Exposition <char*> :: set_NrSuperTotal(Supersport::get_NrModels());
	Exposition <char*> Sale;
	
	// Menu
	while (true) {
		int total = Coupe::get_NrModels() + FourDoorCoupe::get_NrModels() + HotHatch::get_NrModels() + Cabrio::get_NrModels() + Supersport::get_NrModels();
		Exposition <> ::set_nrTotal(total);
		
		menu();
		cout << "Select the preferred action: " << endl;
		int command;
		cin >> command;
		try {
			if (command < 1 || command > 5)
				throw command;
			else 
				switch (command)
				{
				case 1: {
					details();
					break;
				}
				case 2: {
					configure();
					break;
				}
				case 3: {
					buy(Sale);
					break;
				}
				case 4: {
					info(Sale);
					break;
				}
				case 5: {
					break;
				}
				default:
					break;
				}
			if (command == 5) break;
		}

		catch (int val) {
			cout << "Exception, the integer command must be a value between 1 and 5." << endl;
			cout << "________________________________________________________" << endl;
		}
	}
	system("pause");
	return 0;
}