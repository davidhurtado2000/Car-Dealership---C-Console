#include <iostream>
#include "car.cpp"
#include <vector>
#include <map>
#include <iomanip>
#include "bank.cpp"
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;
vector<Car> cars;
vector<Car> cart;
User user1 = User("Shiven", 123);
Bank bank1 = Bank(user1.getName(), user1.getPin(), 8972.00, true);
float TotalWithTaxes;
void displayInfo(vector<Car> c)
{
	cout << "|Option|       Make       |       Model       |       Price       |\n";
	for (int i = 0; i < c.size(); i++)
	{
		cout << "    " + to_string(i + 1) + "  " + "     " + c[i].getMake() + "       " + "       " + c[i].getModel() + "       " + "       " + to_string(c[i].getPrice()) + "       " + "\n";
	}
}

void addCar()
{
	string make, model;
	int price;

	cout << "Enter the car make: \n";
	cin >> make;
	cout << "Enter the car model: \n";
	cin >> model;
	cout << "Enter the car's price: \n";
	cin >> price;

	cars.push_back(Car(make, model, price));
}

void displayReceipt(vector<Car> cartV)
{
	int price;
	float TotalWithoutTaxes;
	map<string, int> carCounts;
	for (Car car : cartV)
	{
		carCounts[car.getModel()]++;
	}
	for (auto entry : carCounts)
	{
		for (Car car2 : cars)
		{
			if (entry.first == car2.getModel())
			{
				price = car2.getPrice();
				break;
			}
		}
		TotalWithoutTaxes = TotalWithoutTaxes + price * entry.second;
		cout << "\n"
			 << entry.second << " x " << entry.first << " | Price: $" << fixed << setprecision(2) << price * entry.second << "\n\n";
	}
	cout << "Subtotal: $" << fixed << setprecision(2) << TotalWithoutTaxes << "\n";
	TotalWithTaxes = TotalWithoutTaxes * 1.0575;
	cout << fixed << "Total: $" << setprecision(2) << TotalWithTaxes << "\n";
	// make a bank accout user has to pay with, make them take out a loan if they dont have enough money
	// make a separate receipt for paying in full and taking out a loan or paying in parts that tells the user the next payment time and how much they'll have to pay next time
	// returning cars
}

void payInParts(float monthlyPrice, int monthsToPay)
{
	time_t currentTime = time(nullptr);
	struct tm *currentLocalTime = localtime(&currentTime);

	/*time_t now = time(0);
	tm*local_time = localtime(&now);*/

	cout << "The dates you must come back to pay $" << monthlyPrice << " are listed below:\n\n";
	for (int i = 0; i < monthsToPay; i++)
	{
		currentLocalTime->tm_mon++;
		if (currentLocalTime->tm_mon == 12)
		{
			currentLocalTime->tm_mon = 0;
			currentLocalTime->tm_year++;
			time_t newTime = mktime(currentLocalTime);
			cout << "Month " << i + 1 << ": " << asctime(currentLocalTime);
		}
		else
		{
			time_t newTime = mktime(currentLocalTime);
			cout << "Month " << i + 1 << ": " << asctime(currentLocalTime);
		}
	}
}

void payWithLoan(double loanAmount)
{
	bool awaitingInput = true;
	while (awaitingInput) {
	time_t currentTime = time(nullptr);
	struct tm *currentLocalTime = localtime(&currentTime);
	double annualInterestRate = 0.06;
	int loanTermMonths;
	// Input loan parameters
	cout << "Enter the loan term (in months): ";
	cin >> loanTermMonths;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again.\n";
		continue;
	}

	awaitingInput = false;
	// Calculate monthly interest rate
	double monthlyInterestRate = annualInterestRate / 12;

	// Calculate monthly payment
	double monthlyPayment = (loanAmount * monthlyInterestRate) / (1 - pow(1 + monthlyInterestRate, -loanTermMonths));

	// Display the monthly payment
	cout << "Your monthly payment is: $" << monthlyPayment << endl;

	cout << "The dates you must come back to pay $" << monthlyPayment << " are listed below:\n\n";
	for (int i = 0; i < loanTermMonths; i++)
	{
		currentLocalTime->tm_mon++;
		if (currentLocalTime->tm_mon == 12)
		{
			currentLocalTime->tm_mon = 0;
			currentLocalTime->tm_year++;
			time_t newTime = mktime(currentLocalTime);
			cout << "Month " << i + 1 << ": " << asctime(currentLocalTime);
		}
		else
		{
			time_t newTime = mktime(currentLocalTime);
			cout << "Month " << i + 1 << ": " << asctime(currentLocalTime);
		}
	}
	cout << "Total Price: $" << (monthlyPayment * loanTermMonths) << "\n";
	}
}

void buyCars(int carSelection, char continueShopping, string continueShopping2, bool stopVariable)
{
	while (stopVariable)
	{
		bool a = true;
		int whileHolder = 1;
		displayInfo(cars);
		while (a) {
		try {
			cout << "Please choose the car you wish to buy: \n";
			cin >> carSelection;

			// Check if the extraction failed
			if (cin.fail()) {
				cin.clear(); // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				throw runtime_error("You have entered an invalid value.");
			}
			a = false; // Exit the loop if valid input is provided
			if (carSelection <= 0 || carSelection > cars.size()) {
				cout << "Invalid value entered, try again.";
			}
			else
			{
			cart.push_back(cars[carSelection - 1]);
			while (whileHolder == 1)
			{
				cout << "Would you like to continue shopping? \n";
				cin >> continueShopping;
				continueShopping = toupper(continueShopping);
				continueShopping2 = continueShopping;
				if (continueShopping2 == "N")
				{
					whileHolder = 0;
				}
				else if (continueShopping2 == "Y")
				{
					whileHolder = 0;
				}
				else
				{
					cout << "Wrong option, try again: \n";
				}
			}
			if (whileHolder == 0 && continueShopping2 == "N")
			{
				stopVariable = false;
			}
		}
		} catch (const exception& e) {
			cerr << "Exception caught: " << e.what() << endl;
			}
		}

	}
}

int main(int argc, char **argv)
{

	Car car1 = Car("Honda", "Civic", 9700);

	Car car2 = Car("Hyundia", "Palisade", 83712);

	Car car3 = Car("Lamborghini", "Urus", 222);

	cars.push_back(car1);
	cars.push_back(car2);
	cars.push_back(car3);

	// Separation
	int choice;
	int carSelection;
	char continueShopping;
	string continueShopping2;
	string cont = "y";
	do
	{
		cout << "Welcome to our car dealership. A list of options will appear below, feel free to choose one. 	\n 1.- Buy Car \n 2.- Pay \n 3.- Exit \n 4.- [ADMIN ONLY] Add Car(s)\n";
		cout << "Choose option: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again.\n";
			continue;
		}

		/* code */

		switch (choice)
		{
		case 1:
		{
			bool stopVariable = true;
			buyCars(carSelection, continueShopping, continueShopping2, stopVariable);
		}
		break;
		case 2:
		{
			// payment with receipt output
			bool keepWhileGoing = true;
			char isInfoCorrect;
			string isInfoCorrect2;
			int paymentMethod;
			float downPayment;
			float remainingPrice;
			int monthsToPay;
			float monthlyPrice;
			while (keepWhileGoing)
			{
				displayReceipt(cart);
				if (TotalWithTaxes > 0)
				{
					cout << "\nIs everything correct? (Y/N): ";
					cin >> isInfoCorrect;
					isInfoCorrect = toupper(isInfoCorrect);
					isInfoCorrect2 = isInfoCorrect;
					bool whileCorrect = true;
					if (isInfoCorrect2 == "Y")
					{
						while (whileCorrect)
						{
							cout << "Which payment method are you going to choose? \n";
							cout << "1. - Pay in Full \n";
							cout << "2. - Pay in Parts \n";
							cout << "3. - Take Out a Loan \n";
							cin >> paymentMethod;
							if (paymentMethod == 1)
							{
								if (bank1.getBalance() >= TotalWithTaxes)
								{
									whileCorrect = false;
									keepWhileGoing = false;
									bank1.setBalance(bank1.getBalance() - TotalWithTaxes);
									displayReceipt(cart);
									cart.clear();
									cout << "Your current bank balance is: $" << bank1.getBalance() << "\n";
								}
								else
								{
									cout << "You don't have enough money in your bank account, make sure your items are correct or choose another payment method.\n";
									whileCorrect = false;
								}
							}
							else if (paymentMethod == 2)
							{
								cout << "\nYou have $" << bank1.getBalance() << " in your bank account.\n";
								cout << "State your downpayment: $";
								cin >> downPayment;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
									cout << "Invalid input. Try again.\n";
								}
								else if (downPayment < TotalWithTaxes && bank1.getBalance() >= downPayment)
								{
									remainingPrice = TotalWithTaxes - downPayment;
									cout << "Choose the number of months you wish to pay for the car: ";
									cin >> monthsToPay;
									monthlyPrice = remainingPrice / monthsToPay;
									payInParts(monthlyPrice, monthsToPay);
									bank1.setBalance(bank1.getBalance() - downPayment);
									cout << "Your bank balance is $" << fixed << setprecision(2) << bank1.getBalance() << "\n";
									displayReceipt(cart);
									cart.clear();
									whileCorrect = false;
									keepWhileGoing = false;
								}
								else if (bank1.getBalance() < downPayment)
								{
									cout << "Choose a lower downpayment. Not enough money in your bank account. \n";
								}
								else if (bank1.getBalance() > downPayment && downPayment >= TotalWithTaxes)
								{
									cout << "Please pay in full.\n";
								}
							}
							else if (paymentMethod == 3)
							{
								if (!bank1.getLoanStatus())
								{
									cout << "You cannot take out a loan, choose another payment method or don't buy a car.\n";
								}
								else
								{
									// when you pay again after paying the 1st time, it keeps the cars that you already bought in the vector
									payWithLoan(TotalWithTaxes);
									whileCorrect = false;
									keepWhileGoing = false;
								}
							}
							else
							{
								// code for wrong number selected
								cout << "Choose a different payment method; you have selected an invalid method. \n";
							}
						}
					}
					else if (isInfoCorrect2 == "N")
					{
						while (isInfoCorrect2 == "N")
						{
							cout << "Let's change your items. \n";
							cout << "What is the problem? Type the number corresponding to your problem. \n";
							cout << "1. Clear The Cart \n2. Add Item(s) \n3. Remove Item(s)\n4. Exit\n";
							int problem;
							cin >> problem;
							if (problem == 1)
							{
								char response;
								string response2;
								cout << "Are you sure you want to clear the cart?";
								cin >> response;
								response = toupper(response);
								response2 = response;
								if (response2 == "Y")
								{
									cart.clear();
									cout << "Your cart has been emptied.\n";
									isInfoCorrect2 = "Y";
									keepWhileGoing = false;
								}
								else if (response2 == "N")
								{
									cout << "Returning back to main menu.";
								}
								else
								{
									cout << "You chose an invalid option, try again. Returning to main menu.\n";
								}
							}
							else if (problem == 2)
							{
								bool stopVariable = true;
								displayReceipt(cart);
								buyCars(carSelection, continueShopping, continueShopping2, stopVariable);
								displayReceipt(cart);
							}
							else if (problem == 3)
							{
								for (int i = 0; i < cart.size(); i++)
								{
									cout << i + 1 << ". " << cart[i].getMake() << "\n";
								}
								cout << "Choose which car to remove.\n";
								int carToRemove;
								cin >> carToRemove;
								cart.erase(cart.begin() + (carToRemove - 1));
								displayReceipt(cart);
							}
							else if (problem == 4)
							{
								isInfoCorrect2 = "Y";
							}
							else
							{
								cout << "Invalid option entered. Try again.";
							}
						}
					}
					else
					{
						cout << "Wrong option, try again.";
					}
				}
				else
				{
					cout << "Your cart is empty. Buy some cars or exit the dealership.\n";
					keepWhileGoing = false;
				}
			}
		}
		break;

		case 3:
			cout << "Program closed";
			break;
		case 4:
		{
			string password = "[4TVqui`27[nL?80DF8QDRWa*GJxD!n-ysBp3{rWxm0QRGH6%,";
			cout << "Type the Admin Password: ";
			string passwordAttempt;
			cin >> passwordAttempt;
			if (passwordAttempt == password)
			{
				addCar();
			}
			else
			{
				cout << "That's the wrong password. You are stupid, stop trying to break into the admin panel.\n";
			}
			break;
		}

		default:
			cout << "Wrong option, try again. \n";
			break;
		}

		if (choice == 3)
		{
			cont = "n";
		}

	} while (cont == "y");
	return 0;
}

//try and catch with exceptions for data types