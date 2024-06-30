#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_INVENTORY = 20; // Maximum cars we can store in our showroom

class Car { // base class for inheritance
private:
	string make; // manufacturer
	string model;
	int model_year; // manufacturing year
	int price;
	int mileage;
	int horsepower;
	string color; // color of the car
	int inspection_score; // a percentage
	bool isAutomatic; // True if auto, false if manual
	int VIN;

public:

	Car() {
		make = "Unknown";
		model = "Unknown";
		model_year = 0;
		price = 1;
		mileage = 0;
		horsepower = 1;
		color = "Unspecified";
		inspection_score = 1;
		isAutomatic = false;
		VIN = 0;
	};

	Car(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN) {

		if (price < 0) {
			throw invalid_argument("Price cannot be negative.");
		}

		if (hp < 0) {
			throw invalid_argument("Horsepower cannot be negative.");
		}

		if (score < 0 || score > 100) {
			throw invalid_argument("Inspection score must be between 0 and 100.");
		}

		this->make = make;
		this->model = model;
		this->model_year = model_year;
		this->price = price;
		this->mileage = mileage;
		this->horsepower = hp;
		this->color = color;
		this->inspection_score = score;
		this->isAutomatic = trans;
		this->VIN = passedVIN;
	}

	// Getters
	string getMake() const {
		return make;
	}
	string getModel() const {
		return model;
	}
	int getYear() const {
		return model_year;
	}
	int getPrice() const {
		return price;
	}
	int getMileage() const {
		return mileage;
	}
	string getColor() const {
		return color;
	}
	int getInspectionScore() const {
		return inspection_score;
	}
	int getHorsepower() const {
		return horsepower;
	}

	bool getTrans() const {
		return isAutomatic;
	}

	// Setters
	void setMake(const string& newMake) {
		this->make = newMake;
	}
	void setModel(const string& newModel) {
		this->model = newModel;
	}
	void setModelYear(int newModelYear) {
		if (newModelYear >= 0) {
			this->model_year = newModelYear;
		}
		else {
			throw invalid_argument("Model year cannot be negative");
		}
	}
	void setPrice(int newPrice) {
		if (newPrice >= 0) {
			this->price = newPrice;
		}
		else {
			throw invalid_argument("Price cannot be negative");
		}
	}
	void setMileage(int newMileage) {
		if (newMileage >= 0) {
			this->mileage = newMileage;
		}
		else {
			throw invalid_argument("Mileage cannot be negative");
		}
	}
	void setColor(const string& newColor) {
		this->color = newColor;
	}
	void setInspectionScore(int newScore) {
		if (newScore >= 0 && newScore <= 100) {
			this->inspection_score = newScore;
		}
		else {
			throw invalid_argument("Inspection score must be between 0 and 100");
		}
	}
	void setHorsepower(int newHorsepower) {
		if (newHorsepower >= 0) {
			this->horsepower = newHorsepower;
		}
		else {
			throw invalid_argument("Horsepower cannot be negative");
		}
	}

	void setTrans(bool trans) {
		this->isAutomatic = trans;
	}

	int getVIN() const {
		return this->VIN;
	}

	void setVIN(int newVIN) {
		this->VIN = newVIN;
	}

	virtual string getType() = 0; // pure virtual function

	virtual ~Car() {} // virtual to enesure deallocation works correctly

};

// inheritance starts here

class SUV : public Car {

private:
	int cargoCapacity;

public:
	SUV(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN, int capacity) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN), cargoCapacity(capacity) {};

	friend ostream& operator<<(ostream& output, const SUV& obj) { // compile time polymorphism
		output << "This spacious " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " SUV offers a generous " << obj.cargoCapacity << " cubic feet of cargo space!" << endl;
		return output;
	}

	string getType() {
		return "SUV";
	}

	int getCargoCapacity() {
		return cargoCapacity;
	}
};

class Truck : public Car {
private:
	int towingCapacity;

public:

	Truck(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN, int capacity) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN), towingCapacity(capacity) {};

	friend ostream& operator<<(ostream& output, const Truck& obj) {
		output << "This powerful " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " truck can tow up to " << obj.towingCapacity << " pounds. Ready for work!" << endl;
		return output;
	}
	string getType() {
		return "Truck";
	}

	int getTowingCapacity() {
		return towingCapacity;
	}
};

class EV : public Car {
	int electricRange;
public:

	EV(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int range, int passedVIN) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN), electricRange(range) {};

	friend ostream& operator<<(ostream& output, const EV& obj) {
		output << "This eco-friendly " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " boasts an impressive " << obj.electricRange << "-mile range on a single charge!" << endl;
		return output;
	}

	string getType() {
		return "EV";
	}

	int getElectricRange() {
		return electricRange;
	}

};

class Sedan : public Car {
public:
	Sedan(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN) {};

	friend ostream& operator<<(ostream& output, const Sedan& obj) {
		output << "Enjoy the best of both worlds: This " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " delivers a smooth ride with the efficiency of a hybrid." << endl;
		return output;
	}

	string getType() {
		return "Sedan";
	}
};

class HybridCar : public Car {
public:
	HybridCar(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN) {};

	friend ostream& operator<<(ostream& output, const HybridCar& obj) {
		output << "Enjoy the best of both worlds: This " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " delivers a smooth ride with the efficiency of a hybrid." << endl;
		return output;
	}

	string getType() {
		return "HybridCar";
	}
};

class Supercar : public Car {
	float zeroToHundred;
	int topSpeed;

public:
	Supercar(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN, float zerotoHun, int topVel) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN), zeroToHundred(zerotoHun), topSpeed(topVel) {};

	friend ostream& operator<<(ostream& output, const Supercar& obj) {
		output << "Experience raw power! This thrilling " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " rockets from 0-60 mph in just " << obj.zeroToHundred << " seconds!" << endl;
		return output;
	}

	string getType() {
		return "Supercar";
	}

	float getZeroToHundred() {
		return zeroToHundred;
	}

	int getTopSpeed() {
		return topSpeed;
	}

};

class LuxuryCar : public Car {
public:
	LuxuryCar(string make, string model, int model_year, int price, int mileage, int hp, string color, int score, bool trans, int passedVIN) : Car(make, model, model_year, price, mileage, hp, color, score, trans, passedVIN) {};

	friend ostream& operator<<(ostream& output, const LuxuryCar& obj) {
		output << "Embrace unparalleled comfort! This exquisite " << obj.getYear() << " " << obj.getMake() << " " << obj.getModel() << " surrounds you with premium materials and refined design." << endl;
		return output;
	}

	string getType() {
		return "LuxuryCar";
	}
};

// inheritance ends here

class Inventory { // composition
private:
	Car** carsInHouse; // array of pointers
	int numCars;

public:
	Inventory() {
		carsInHouse = new Car * [MAX_INVENTORY];
		numCars = 0;
	}

	void addCar(Car* car) {
		if (numCars == MAX_INVENTORY) {
			cout << "Inventory full...\n";
		}
		else {
			carsInHouse[numCars] = car;
			numCars++;
		}
	}

	void addCarToInventory() {
		string type, make, model, color;
		int year, price, mileage, hp, score, vin, additionalData;
		bool trans;
		bool invalidInput = true;

		while (true) {
			cout << "Enter car type (SUV, Truck, EV, Sedan, HybridCar, Supercar, LuxuryCar): ";
			cin >> type;

			if (type == "SUV" || type == "Truck" || type == "EV" || type == "Sedan" ||
				type == "HybridCar" || type == "Supercar" || type == "LuxuryCar") {
				cout << "You entered: " << type << endl;
				break;
			}
			else {
				cout << "Invalid car type. Please try again." << endl;
			}
		}

		while (invalidInput) {
			try {
				// Get common car details
				cout << "Enter make: ";
				cin >> make;
				cout << "Enter model: ";
				cin >> model;

				cout << "Enter model year: ";
				if (!(cin >> year) || year < 0) {
					throw invalid_argument("Invalid year. Please enter a non-negative number.");
				}

				cout << "Enter price: $";
				if (!(cin >> price) || price < 0) {
					throw invalid_argument("Invalid price. Please enter a non-negative number.");
				}

				cout << "Enter mileage: ";
				if (!(cin >> mileage) || mileage < 0) {
					throw invalid_argument("Invalid mileage. Please enter a non-negative number.");
				}

				cout << "Enter horsepower: ";
				if (!(cin >> hp) || hp < 0) {
					throw invalid_argument("Invalid horsepower. Please enter a non-negative number.");
				}

				cout << "Enter color: ";
				cin.ignore(); // Clear newline from previous input
				getline(cin, color);

				cout << "Enter inspection score (0-100): ";
				if (!(cin >> score) || score < 0 || score > 100) {
					throw invalid_argument("Invalid score. Please enter a number between 0 and 100.");
				}

				cout << "Is it automatic? (1 for yes, 0 for no): ";
				if (!(cin >> trans)) {
					throw invalid_argument("Invalid input. Please enter 1 for yes or 0 for no.");
				}

				cout << "Enter VIN: ";
				if (!(cin >> vin)) {
					throw invalid_argument("Invalid VIN. Please enter a number.");
				}

				invalidInput = false;
			}
			catch (const invalid_argument& e) {
				cerr << "Error: " << e.what() << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}


		if (type == "SUV") {
			cout << "Enter cargo capacity: ";
			cin >> additionalData;
			addCar(new SUV(make, model, year, price, mileage, hp, color, score, trans, vin, additionalData));
		}
		else if (type == "Truck") {
			cout << "Enter towing capacity: ";
			cin >> additionalData;
			addCar(new Truck(make, model, year, price, mileage, hp, color, score, trans, vin, additionalData));
		}
		else if (type == "EV") {
			cout << "Enter electric range: ";
			cin >> additionalData;
			addCar(new EV(make, model, year, price, mileage, hp, color, score, trans, additionalData, vin));
		}
		else if (type == "Sedan") {
			addCar(new Sedan(make, model, year, price, mileage, hp, color, score, trans, vin));
		}
		else if (type == "HybridCar") {
			addCar(new HybridCar(make, model, year, price, mileage, hp, color, score, trans, vin));
		}
		else if (type == "Supercar") {
			float zeroToHundred;
			int topSpeed;
			cout << "Enter 0-60 mph time: ";
			cin >> zeroToHundred;
			cout << "Enter top speed: ";
			cin >> topSpeed;
			addCar(new Supercar(make, model, year, price, mileage, hp, color, score, trans, vin, zeroToHundred, topSpeed));
		}
		else if (type == "LuxuryCar") {
			addCar(new LuxuryCar(make, model, year, price, mileage, hp, color, score, trans, vin));
		}
		else {
			cerr << "Error: Invalid car type." << endl;
			return;
		}

		cout << "Car added to inventory!" << endl;
	}

	Car* removeCarFromInventory() {
		int vin;
		cout << "Enter VIN of car to remove: ";


		while (!(cin >> vin)) {
			cout << "Invalid input. Please enter a numeric VIN: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}


		for (int i = 0; i < numCars; ++i) {
			if (carsInHouse[i]->getVIN() == vin) {
				Car* removedCar = carsInHouse[i];

				for (int j = i; j < numCars - 1; ++j) {
					carsInHouse[j] = carsInHouse[j + 1];
				}

				numCars--;
				cout << "Car with VIN " << vin << " removed from inventory." << endl;
				return removedCar;
			}
		}

		cout << "Car with VIN " << vin << " not found in inventory." << endl;
		return nullptr; // Car not found
	}

	Car* removeCarWithVIN(int vin) {
		int indexToRemove = -1;

		for (int i = 0; i < numCars; ++i) {
			if (carsInHouse[i]->getVIN() == vin) {
				indexToRemove = i;
				break;
			}
		}

		if (indexToRemove != -1) {

			Car* removedCar = carsInHouse[indexToRemove];
			delete carsInHouse[indexToRemove]; // Free memory

			for (int j = indexToRemove; j < numCars - 1; ++j) {
				carsInHouse[j] = carsInHouse[j + 1];
			}

			numCars--;
			return removedCar;
		}
		else {
			return nullptr;
		}
	}

	void displayInventory() {
		for (int i = 0; i < numCars; i++) {
			cout << i + 1 << ". "
				<< carsInHouse[i]->getYear() << " "
				<< carsInHouse[i]->getMake() << " "
				<< carsInHouse[i]->getModel()
				<< " - $" << carsInHouse[i]->getPrice()
				<< " | VIN: " << carsInHouse[i]->getVIN()
				<< endl;
		}
	}

	void saveToFile(const string& filename) {
		ofstream outFile(filename);
		if (!outFile.is_open()) {
			cerr << "Error opening file for writing: " << filename << endl;
			return;
		}

		for (int i = 0; i < numCars; ++i) {
			outFile << carsInHouse[i]->getType() << ","
				<< carsInHouse[i]->getMake() << ","
				<< carsInHouse[i]->getModel() << ","
				<< carsInHouse[i]->getYear() << ","
				<< carsInHouse[i]->getPrice() << ","
				<< carsInHouse[i]->getMileage() << ","
				<< carsInHouse[i]->getHorsepower() << ","
				<< carsInHouse[i]->getColor() << ","
				<< carsInHouse[i]->getInspectionScore() << ","
				<< (carsInHouse[i]->getTrans() ? 1 : 0) << ","
				<< carsInHouse[i]->getVIN();

			string carType = carsInHouse[i]->getType();
			if (carType == "SUV") {
				outFile << "," << static_cast<SUV*>(carsInHouse[i])->getCargoCapacity();
			}
			else if (carType == "Truck") {
				outFile << "," << static_cast<Truck*>(carsInHouse[i])->getTowingCapacity();
			}
			else if (carType == "EV") {
				outFile << "," << static_cast<EV*>(carsInHouse[i])->getElectricRange();
			}
			else if (carType == "Supercar") {
				outFile << "," << static_cast<Supercar*>(carsInHouse[i])->getZeroToHundred()
					<< "," << static_cast<Supercar*>(carsInHouse[i])->getTopSpeed();
			}
			outFile << endl;
		}

		outFile.close();
		cout << "Inventory saved to " << filename << endl;
	}

	void loadFromFile(const string& filename) {
		ifstream inFile(filename);
		if (!inFile.is_open()) {
			cerr << "Error opening file for reading: " << filename << endl;
			return;
		}

		string line, type, make, model, color;
		int year, price, mileage, hp, score, vin;
		bool trans;
		float zeroToHundred = 0.0f;
		int topSpeed = 0;

		while (getline(inFile, line)) {
			stringstream ss(line);


			getline(ss, type, ',');


			getline(ss, make, ',');
			getline(ss, model, ',');

			string temp_year;
			getline(ss, temp_year, ',');
			year = stoi(temp_year);

			string temp_price, temp_mileage, temp_hp;
			getline(ss, temp_price, ',');
			getline(ss, temp_mileage, ',');
			getline(ss, temp_hp, ',');
			price = stoi(temp_price);
			mileage = stoi(temp_mileage);
			hp = stoi(temp_hp);

			getline(ss, color, ',');
			string temp_score, temp_trans, temp_vin;
			getline(ss, temp_score, ',');
			score = stoi(temp_score);
			getline(ss, temp_trans, ',');
			trans = stoi(temp_trans);
			getline(ss, temp_vin, ',');
			vin = stoi(temp_vin);


			if (type == "SUV")
			{
				int cargoCapacity;
				string cargo_temp;
				getline(ss, cargo_temp, ',');
				cargoCapacity = stoi(cargo_temp);
				addCar(new SUV(make, model, year, price, mileage, hp, color, score, trans, vin, cargoCapacity));
			}
			else if (type == "Truck") {
				int towingCapacity;
				string temp_tow;
				getline(ss, temp_tow, ',');
				towingCapacity = stoi(temp_tow);
				addCar(new Truck(make, model, year, price, mileage, hp, color, score, trans, vin, towingCapacity));
			}
			else if (type == "EV") {
				int electricRange;
				string range;
				getline(ss, range, ',');
				electricRange = stoi(range);
				addCar(new EV(make, model, year, price, mileage, hp, color, score, trans, electricRange, vin));
			}
			else if (type == "Sedan") {

				addCar(new Sedan(make, model, year, price, mileage, hp, color, score, trans, vin));
			}
			else if (type == "HybridCar") {

				addCar(new HybridCar(make, model, year, price, mileage, hp, color, score, trans, vin));
			}
			else if (type == "Supercar") {

				string zero_to_60;
				getline(ss, zero_to_60, ',');
				string tpspd;
				getline(ss, tpspd, ',');

				zeroToHundred = stof(zero_to_60);
				topSpeed = stof(tpspd);
				addCar(new Supercar(make, model, year, price, mileage, hp, color, score, trans, vin, zeroToHundred, topSpeed));
			}
			else if (type == "LuxuryCar") {
				addCar(new LuxuryCar(make, model, year, price, mileage, hp, color, score, trans, vin));
			}
			else {
				cerr << "Error loading car: Invalid car type in file." << endl;
			}
		}

		inFile.close();
		cout << "Inventory loaded from " << filename << endl;
	}

	void searchByMake(const string& make) {
		bool found = false;
		for (int i = 0; i < numCars; ++i) {
			if (carsInHouse[i]->getMake() == make) {
				cout << i + 1 << ". "
					<< carsInHouse[i]->getYear() << " "
					<< carsInHouse[i]->getMake() << " "
					<< carsInHouse[i]->getModel()
					<< " - $" << carsInHouse[i]->getPrice()
					<< " | VIN: " << carsInHouse[i]->getVIN()
					<< endl;
				found = true;
			}
		}
		if (!found) {
			cout << "No cars found with make: " << make << endl;
		}
	}

	Car* findCarByVIN(int vin) const {
		for (int i = 0; i < numCars; ++i) {
			if (carsInHouse[i]->getVIN() == vin) {
				return carsInHouse[i];
			}
		}
		return nullptr;
	}


	void searchByType(const string& type) {
		bool found = false;
		for (int i = 0; i < numCars; ++i) {
			if (carsInHouse[i]->getType() == type) {
				cout << i + 1 << ". "
					<< carsInHouse[i]->getYear() << " "
					<< carsInHouse[i]->getMake() << " "
					<< carsInHouse[i]->getModel()
					<< " - $" << carsInHouse[i]->getPrice()
					<< " | VIN: " << carsInHouse[i]->getVIN()
					<< endl;
				found = true;
			}
		}
		if (!found) {
			cout << "No cars found with type: " << type << endl;
		}
	}


	void searchByPriceRange(int minPrice, int maxPrice) {
		bool found = false;
		if (minPrice > maxPrice) {
			cout << "Invalid price range. Minimum price must be less than or equal to maximum price." << endl;
			return;
		}

		for (int i = 0; i < numCars; ++i) {
			int carPrice = carsInHouse[i]->getPrice();
			if (carPrice >= minPrice && carPrice <= maxPrice) {
				cout << i + 1 << ". "
					<< carsInHouse[i]->getYear() << " "
					<< carsInHouse[i]->getMake() << " "
					<< carsInHouse[i]->getModel()
					<< " - $" << carsInHouse[i]->getPrice()
					<< " | VIN: " << carsInHouse[i]->getVIN()
					<< endl;
				found = true;
			}
		}
		if (!found) {
			cout << "No cars found within the price range: $" << minPrice << " - $" << maxPrice << endl;
		}
	}

	~Inventory() { // Destructor
		for (int i = 0; i < numCars; ++i) {
			delete carsInHouse[i];
		}
		delete[] carsInHouse;
		carsInHouse = nullptr;
	}
};

class Workshop {
public:
	const int baseOilChange = 40;
	const int baseCarWash = 30;


	const int suvAdjustment = 5;
	const int truckAdjustment = 10;
	const int evAdjustment = -5;
	const int hybridAdjustment = 0;
	const int supercarAdjustment = 20;
	const int luxuryCarAdjustment = 15;


	const int sedanPaintProtection = 800;
	const int suvTruckPaintProtection = 1000;
	const int superLuxuryPaintProtection = 1500;

	void oilChange(const string& carType) {
		int price = baseOilChange;
		cout << "Servicing your " << carType << "...\n";

		if (carType == "SUV") {
			price += suvAdjustment;
			cout << "Oil change successful! Your rugged SUV is ready to hit the road. ";
		}
		else if (carType == "Truck") {
			price += truckAdjustment;
			cout << "Oil change complete! Your workhorse is fueled up. ";
		}
		else if (carType == "EV") {
			price += evAdjustment;
			cout << "Servicing your eco-friendly EV complete! Charged and ready to go. ";
		}
		else if (carType == "HybridCar") {
			price += hybridAdjustment;
			cout << "Oil change done! Your efficient hybrid is optimized. ";
		}
		else if (carType == "Supercar") {
			price += supercarAdjustment;
			cout << "Precision oil change finished! Your high-performance machine is roaring. ";
		}
		else if (carType == "LuxuryCar") {
			price += luxuryCarAdjustment;
			cout << "Oil change complete! Your luxurious ride gleams. ";
		}
		else if (carType == "Sedan") {
			cout << "Oil change successful! Your reliable sedan is running smoothly. ";
		}
		else {
			throw runtime_error("Unknown car type: " + carType);
		}

		cout << "Your bill is $" << price << endl;
	}

	void carWash(const string& carType) {
		int price = baseCarWash;
		cout << "Detailing your " << carType << "...\n";

		if (carType == "SUV") {
			price += suvAdjustment;
			cout << "Car wash complete! Your adventurous SUV shines. ";
		}
		else if (carType == "Truck") {
			price += truckAdjustment;
			cout << "Wash successful! Your powerful truck looks spotless. ";
		}
		else if (carType == "EV") {
			price += evAdjustment;
			cout << "Wash complete! Your sleek EV gleams. ";
		}
		else if (carType == "HybridCar") {
			price += hybridAdjustment;
			cout << "Wash finished! Your fuel-efficient hybrid sparkles. ";
		}
		else if (carType == "Supercar") {
			price += supercarAdjustment;
			cout << "Detailing complete! Your head-turning supercar looks pristine. ";
		}
		else if (carType == "LuxuryCar") {
			price += luxuryCarAdjustment;
			cout << "Wash finished! Your elegant luxury car radiates. ";
		}
		else if (carType == "Sedan") {
			cout << "Wash successful! Your practical sedan looks refreshed. ";
		}
		else {
			throw runtime_error("Unknown car type: " + carType);
		}

		cout << "Your bill is $" << price << endl;
	}

	void applyPaintProtection(const string& carType) {
		int price = 0;
		cout << "Applying paint protection to your " << carType << "...\n";

		if (carType == "Sedan" || carType == "HybridCar" || carType == "EV") {
			price = sedanPaintProtection;
		}
		else if (carType == "SUV" || carType == "Truck") {
			price = suvTruckPaintProtection;
		}
		else if (carType == "Supercar" || carType == "LuxuryCar") {
			price = superLuxuryPaintProtection;
		}
		else {
			throw runtime_error("Unknown car type: " + carType);
		}

		cout << "Paint protection applied successfully! Cost: $" << price << "\n";
	}
};

class Finance {
public:
	void lease(int carPrice, int leaseTermYears) const {
		while (leaseTermYears < 2) {
			cout << "Invalid lease term. Minimum lease term is 2 years.\n";
			cout << "Enter lease term (in years): ";
			if (!(cin >> leaseTermYears)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number.\n";
				leaseTermYears = 0;
			}
		}

		double interestRate = (leaseTermYears <= 3) ? 0.035 : 0.045;
		double monthlyPayment = calculateLeasePayment(carPrice, leaseTermYears, interestRate);

		cout << "\nLease Details:\n";
		cout << "Car Price: $" << carPrice << endl;
		cout << "Lease Term: " << leaseTermYears << " years\n";
		cout << "Interest Rate: " << (interestRate * 100) << "%\n";
		cout << "Estimated Monthly Payment: $" << monthlyPayment << endl;
	}

	void payWithCash(int carPrice) const {
		cout << "\nCash Purchase:\n";
		cout << "Total Price: $" << carPrice << endl;
	}

	void creditCardLoan(int carPrice, int loanTermYears) const {

		while (loanTermYears < 1) {
			cout << "Invalid loan term. Minimum loan term is 1 year.\n";
			cout << "Enter loan term (in years): ";
			if (!(cin >> loanTermYears)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a number.\n";
				loanTermYears = 0;
			}
		}

		double interestRate = 0.18;
		double monthlyPayment = calculateLoanPayment(carPrice, loanTermYears * 12, interestRate);

		cout << "\nCredit Card Loan Details:\n";
		cout << "Car Price: $" << carPrice << endl;
		cout << "Loan Term: " << loanTermYears << " years\n";
		cout << "Interest Rate: " << (interestRate * 100) << "%\n";
		cout << "Estimated Monthly Payment: $" << monthlyPayment << endl;
		cout << "Warning: Credit card interest rates can be high. Consider other loan options.\n";
	}

private:

	double calculateLeasePayment(int carPrice, int leaseTermYears, double interestRate) const {
		double residualValue = carPrice * 0.5;
		double depreciation = (carPrice - residualValue) / (leaseTermYears * 12);
		double interest = (carPrice + residualValue) * interestRate / 24;
		return depreciation + interest;
	}


	double calculateLoanPayment(int loanAmount, int loanTermMonths, double interestRate) const {
		double monthlyInterestRate = interestRate / 12;
		return loanAmount * monthlyInterestRate * pow(1 + monthlyInterestRate, loanTermMonths)
			/ (pow(1 + monthlyInterestRate, loanTermMonths) - 1);
	}
};

class Salesman {
private:
	string name;
	int employee_id;
	int totalSales;
	double commissionRate;
	double amountGenerated;

public:
	Salesman() : name(""), employee_id(0), totalSales(0),
		commissionRate(0.0), amountGenerated(0.0) {}

	Salesman(const string& dataString) {
		stringstream ss(dataString);
		string temp;

		getline(ss, name, ',');
		getline(ss, temp, ','); employee_id = stoi(temp);
		getline(ss, temp, ','); totalSales = stoi(temp);
		getline(ss, temp, ','); commissionRate = stod(temp);
		getline(ss, temp, ','); amountGenerated = stod(temp);
	}


	string getName() const { return name; }
	int getID() const { return employee_id; }
	int getTotalSales() const { return totalSales; }
	double getCommissionRate() const { return commissionRate; }
	double getAmountGenerated() const { return amountGenerated; }

	// Actions
	void makeSales(double amount) {
		if (amount < 0) {
			throw invalid_argument("Sales amount cannot be negative");
		}
		totalSales++;
		amountGenerated += amount;
	}

	double calculateCommission() const {
		return amountGenerated * commissionRate / 100.0;
	}

	// File Handling
	void loadFromFile(const string& filename) {
		ifstream inFile(filename);
		if (inFile.is_open()) {
			string dataString;
			getline(inFile, dataString);
			*this = Salesman(dataString);
			inFile.close();
		}
		else {
			cerr << "Unable to open file: " << filename << endl;
		}
	}

	void saveToFile(const string& filename) const {
		const int MAX_SALESMEN = 100;
		Salesman allSalesmen[MAX_SALESMEN];
		int numSalesmen = 0;

		ifstream inFile(filename);
		if (inFile.is_open()) {
			string dataString;
			while (getline(inFile, dataString) && numSalesmen < MAX_SALESMEN) {
				allSalesmen[numSalesmen] = Salesman(dataString);
				numSalesmen++;
			}
			inFile.close();
		}


		for (int i = 0; i < numSalesmen; i++) {
			if (allSalesmen[i].getName() == name) {
				allSalesmen[i] = *this;
				break;
			}
		}


		ofstream outFile(filename);
		if (outFile.is_open()) {
			for (int i = 0; i < numSalesmen; i++) {
				outFile << allSalesmen[i].getName() << "," << allSalesmen[i].getID() << ","
					<< allSalesmen[i].getTotalSales() << "," << allSalesmen[i].getCommissionRate() << ","
					<< allSalesmen[i].getAmountGenerated() << endl;
			}
			outFile.close();
		}
		else {
			cerr << "Unable to open file: " << filename << endl;
		}
	}

};

class SalesmanMenu { // aggregation
private:
	Salesman& salesman;
	const string salesmanFilename = "salespeople.txt";

public:
	SalesmanMenu(Salesman& s) : salesman(s) {}

	void displayMenu() {
		int choice;
		do {
			cout << "\nSalesman Menu:\n";
			cout << "1. Add a Sale\n";
			cout << "2. Calculate My Commission\n";
			cout << "3. Generate Sales Report\n";
			cout << "4. Back to Main Menu\n";
			cout << "Enter your choice: ";

			while (!(cin >> choice) || choice < 1 || choice > 4) {
				cout << "Invalid input. Please enter a number between 1 and 4: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			switch (choice) {
			case 1: { //Add a Sale
				double saleAmount;
				cout << "Enter the sale amount: $";
				while (!(cin >> saleAmount) || saleAmount < 0) {
					cout << "Invalid input. Please enter a positive number: $";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				try {
					salesman.makeSales(saleAmount);
					salesman.saveToFile(salesmanFilename); // Use the correct filename
					cout << "Sale added successfully!\n";
				}
				catch (const invalid_argument& e) {
					cout << "Error: " << e.what() << endl;
				}
				break;
			}
			case 2:
				cout << "\nYour total commission is: $" << salesman.calculateCommission() << endl;
				break;
			case 3: {
				cout << "\nSales Report for " << salesman.getName() << ":\n";
				cout << "------------------------------------\n";
				cout << "Employee ID: " << salesman.getID() << endl;
				cout << "Total Sales Made: " << salesman.getTotalSales() << endl;
				cout << "Total Amount Generated: $" << fixed << setprecision(2)
					<< salesman.getAmountGenerated() << endl;
				cout << "Commission Rate: " << salesman.getCommissionRate() << "%\n";
				cout << "Total Commission Earned: $" << fixed << setprecision(2)
					<< salesman.calculateCommission() << endl;
				break;
			}
			case 4:
				break;
			}
		} while (choice != 4);
	}
};

class AdminMenu { // aggregation
private:
	Inventory& inventory;
	const string inventoryFilename = "inventory.txt";

public:
	AdminMenu(Inventory& inv) : inventory(inv) {}

	void displayMenu() {
		int choice;
		do {
			cout << "\nAdmin Menu:\n";
			cout << "1. Add a car to inventory\n";
			cout << "2. Remove a car from inventory\n";
			cout << "3. Show all inventory\n";
			cout << "4. Save Inventory to File\n";
			cout << "5. Back to Main Menu\n";
			cout << endl;
			cout << "Enter your choice: ";


			while (!(cin >> choice) || choice < 1 || choice > 5) {
				cout << "Invalid input. Please enter a number between 1 and 5: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			if (choice == 1) {
				inventory.addCarToInventory();
			}
			else if (choice == 2) {
				Car* removedCar = inventory.removeCarFromInventory();
				if (removedCar != nullptr) {
					delete removedCar;
				}
			}
			else if (choice == 3) {
				inventory.displayInventory();
			}
			else if (choice == 4) {
				inventory.saveToFile(inventoryFilename);
			}

		} while (choice != 5);
	}
};

class CustomerMenu { // aggregation with other classes
private:
	Inventory& inventory;
	Workshop& workshop;
	Finance finance;

public:
	CustomerMenu(Inventory& inv, Workshop& w) : inventory(inv), workshop(w), finance() {}

	void displayMenu() {
		int choice;
		do {
			cout << "\nCustomer Menu:\n";
			cout << "1. View All Inventory\n";
			cout << "2. Access Workshop\n";
			cout << "3. See Potential Finance Options / Buy a Car\n";
			cout << "4. Filter Searches\n";
			cout << "5. Back to Main Menu\n";
			cout << endl;
			cout << "Enter your choice: ";


			while (!(cin >> choice) || choice < 1 || choice > 5) {
				cout << "Invalid input. Please enter a number between 1 and 5: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cout << endl;

			if (choice == 1) {
				viewInventory();
			}
			else if (choice == 2) {
				accessWorkshop();
			}
			else if (choice == 3) {
				seeFinanceOptions();
			}
			else if (choice == 4) {
				int searchChoice;
				string make, type;
				cout << "\nCar Search Menu:\n";
				cout << "1. Search by Make\n";
				cout << "2. Search by Type\n";
				cout << "3. Search by Price Range\n";
				cout << "4. Exit\n";
				cout << "Enter your choice: ";

				cin >> searchChoice;

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (searchChoice == 1) {
					cout << "Enter the make to search for: ";
					getline(cin, make);
					inventory.searchByMake(make);
				}
				else if (searchChoice == 2) {
					cout << "Enter the type to search for: ";
					getline(cin, type);
					inventory.searchByType(type);
				}
				else if (searchChoice == 3) {
					int minPrice, maxPrice;
					cout << "Enter the minimum price: ";
					cin >> minPrice;
					cout << "Enter the maximum price: ";
					cin >> maxPrice;
					inventory.searchByPriceRange(minPrice, maxPrice);
				}
				else if (searchChoice == 4) {
					cout << "Exiting...\n";
				}
				else {
					cout << "Invalid choice. Please try again.\n";
				}
			}

		} while (choice != 5);
	}

	void seeFinanceOptions() {
		char displayInventoryChoice;
		cout << "\nWould you like to view the current inventory before proceeding? Enter 'Y' if yes: ";
		cin >> displayInventoryChoice;

		if (displayInventoryChoice == 'y' || displayInventoryChoice == 'Y') {
			cout << "\nCurrent Inventory:\n";
			inventory.displayInventory();
		}

		int vin = 0;
		cout << "\nPlease enter the VIN of the car you're interested in: ";
		cin >> vin;


		Car* car = inventory.findCarByVIN(vin);
		if (!car) {
			cout << "Car with VIN " << vin << " not found. Please try again.\n";
			return;
		}


		int carPrice = car->getPrice();

		cout << "\nPotential Finance Options:\n";

		if (carPrice <= 20000) {
			cout << "- Pay with cash (full amount)\n";
			cout << "- Consider a credit card loan (1-3 years)\n";
			cout << "- Explore leasing options (2-4 years)\n";
		}
		else if (carPrice <= 50000) {
			cout << "- Pay with cash (if possible)\n";
			cout << "- Secure a traditional auto loan (3-5 years)\n";
			cout << "- Leasing is still an option (3-5 years)\n";
		}
		else {
			cout << "- Traditional auto loan (5-7 years)\n";
			cout << "- Explore specialized luxury car financing\n";
			cout << "- Leasing might be available with higher payments\n";
		}

		cout << "\nWould you like to get an estimated monthly payment for the finance options (other than cash)? (y/n): ";
		char paymentChoice;
		cin >> paymentChoice;

		if (paymentChoice == 'y' || paymentChoice == 'Y') {
			int option;
			cout << "\n1. Lease (2-7 years)\n";
			cout << "2. Credit Card Loan (1-3 years)\n";
			cout << "Enter your choice: ";

			while (!(cin >> option) || option < 1 || option > 2) {
				cout << "Invalid input. Please enter either 1 or 2: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			int termYears;
			cout << "Enter term (in years): ";
			while (!(cin >> termYears) || termYears < 1) {
				cout << "Invalid input. Please enter a positive number of years: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			switch (option) {
			case 1:
				finance.lease(carPrice, termYears);
				break;
			case 2:
				finance.creditCardLoan(carPrice, termYears);
				break;
			}
		}

		char buyChoice;
		cout << "\nWould you like to purchase this car? (y/n): ";
		cin >> buyChoice;

		if (buyChoice == 'y' || buyChoice == 'Y') {
			if (inventory.removeCarWithVIN(vin) != nullptr) {
				cout << "Congratulations! You have purchased the car.\n";
			}
			else {

				cout << "Unexpected error: Car with VIN " << vin << " not found.\n";
			}
		}
		else {
			cout << "Purchase cancelled.\n";
		}
	}

private:
	void viewInventory() {
		inventory.displayInventory();
	}

	void accessWorkshop() {
		string carType;
		cout << "What type of car do you have? (SUV, Truck, EV, HybridCar, Supercar, LuxuryCar, Sedan): ";
		cin >> carType;


		while (carType != "SUV" && carType != "Truck" && carType != "EV" &&
			carType != "HybridCar" && carType != "Supercar" &&
			carType != "LuxuryCar" && carType != "Sedan") {
			cout << "Invalid car type. Please enter a valid type: ";
			cin >> carType;
		}


		int serviceChoice;
		do {
			cout << "\nWorkshop Service Menu:\n";
			cout << "1. Oil Change\n";
			cout << "2. Car Wash\n";
			cout << "3. Apply Paint Protection\n";
			cout << "4. Back to Customer Menu\n";
			cout << "Enter your choice: ";

			while (!(cin >> serviceChoice) || serviceChoice < 1 || serviceChoice > 4) {
				cout << "Invalid input. Please enter a number between 1 and 4: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			switch (serviceChoice) {
			case 1:
				workshop.oilChange(carType);
				break;
			case 2:
				workshop.carWash(carType);
				break;
			case 3:
				workshop.applyPaintProtection(carType);
				break;
			case 4:
				break;
			}
		} while (serviceChoice != 4);
	}
};

template <typename CarType>
void printGenericCarDetails(const CarType* car) {
	if (car == nullptr) {
		std::cerr << "Error: Cannot print details of a null car pointer.\n";
		return;
	}

	cout << "\n----------------- Car Details -----------------\n";
	cout << "Make: " << car->getMake() << std::endl;
	cout << "Model: " << car->getModel() << std::endl;
	cout << "Year: " << car->getYear() << std::endl;
	cout << "Price: $" << car->getPrice() << std::endl;
	cout << "Mileage: " << car->getMileage() << " miles" << std::endl;
	cout << "Horsepower: " << car->getHorsepower() << std::endl;
	cout << "Color: " << car->getColor() << std::endl;
	cout << "Inspection Score: " << car->getInspectionScore() << "%" << std::endl;
	cout << "Transmission: " << (car->getTrans() ? "Automatic" : "Manual") << std::endl;
	cout << "VIN: " << car->getVIN() << std::endl;
	cout << "---------------------------------------------\n";
}

int main() {
	Inventory ClaycoMotors;
	Workshop ClaycoWorks;
	ClaycoMotors.loadFromFile("inventory.txt");

	int choice;

	do {
		cout << "\nMain Menu:\n";
		cout << "1. Salesman Login\n";
		cout << "2. Customer Options\n";
		cout << "3. Admin Login\n";
		cout << "4. Exit\n";
		cout << "Enter your choice: ";

		// Input Validation for Main Menu
		while (!(cin >> choice) || choice < 1 || choice > 4) {
			cout << "Invalid input. Please enter a number between 1 and 4: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (choice == 1) {
			string salesmanName;
			cout << "Enter salesman name (case-sensitive): ";
			cin.ignore();
			while (getline(cin, salesmanName) && (salesmanName.empty() || !isalpha(salesmanName[0]))) {
				cout << "Invalid input. Please enter a valid name (starting with a letter): ";
			}

			string filename = "salespeople.txt";
			ifstream inFile(filename);
			Salesman currentSalesman;
			bool salesmanFound = false;

			if (inFile.is_open()) {
				string dataString;
				while (getline(inFile, dataString)) {
					Salesman tempSalesman(dataString);
					if (tempSalesman.getName() == salesmanName) {
						currentSalesman = tempSalesman;
						salesmanFound = true;
						break;
					}
				}
				inFile.close();
			}

			if (!salesmanFound) {
				cout << "Salesman not found. Exiting...\n";
				return 1;
			}
			SalesmanMenu menu(currentSalesman);
			menu.displayMenu();
		}
		else if (choice == 2) {
			CustomerMenu customerMenu(ClaycoMotors, ClaycoWorks);
			customerMenu.displayMenu();
		}
		else if (choice == 3) {
			string username, password;
			cout << "\nAdmin Login:\n";
			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;

			if (username == "admin" && password == "admin") {
				AdminMenu adminMenu(ClaycoMotors);
				adminMenu.displayMenu();
			}
			else {
				cout << "Incorrect username or password. Access denied. Aborting...\n";
				exit(0);
			}
		}
		else if (choice == 4) {
			cout << "Exiting the program. Goodbye from Clayco Motors!\n";
		}
	} while (choice != 4);

	ClaycoMotors.saveToFile("inventory.txt");
	return 0;
}