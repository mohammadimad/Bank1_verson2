#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
//#include "Bank.h"
//using namespace Bank;
using namespace std;
const string ClientsFileName = "Clients2.txt";
void ShowMainMenue();
struct sClient {
	string AccountNumber;
	string AccountName;
	string PinCode;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};
enum enTransctionsOptions
{
	eDeposit = 1, ewithdraw = 2,
	eTotalbalances = 3, eMainMenue= 4,
};
enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransctions = 6, eExit = 7
};
string ReadString(string Message) {
	string Account;
	cout << Message;
	getline(cin, Account);
	return Account;
}
vector <string> SplitString(string S1, string delim) {

	//cout << "\nYour string wrords are: \n\n";
	string sWord;
	vector <string> vString;
	short pos = 0;
	// Hello Mohammad imad wasd Abdelfattah
	while ((pos = S1.find(delim)) != string::npos) {
		sWord = S1.substr(0, pos);
		if (sWord != "")
			vString.push_back(sWord);
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
		vString.push_back(S1);
	return vString;
}
sClient ConvertLineToRecord(string Line, string Seperator = "#//#") {
	string stClientRecord = "";
	sClient Clinet;
	vector <string> vString;
	vString = SplitString(Line, Seperator);
	Clinet.AccountNumber = vString[0];
	Clinet.PinCode = vString[1];
	Clinet.AccountName = vString[2];
	Clinet.PhoneNumber = vString[3];
	Clinet.AccountBalance = stod(vString[4]);//casting from string to double
	return Clinet;
}

vector <sClient>LoadClientsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		string Line;
		sClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void AddDateLineToFile(string FileName, string sDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << sDataLine << endl;
		MyFile.close();
	}
}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}

		MyFile.close();

	}
	return false;
}
sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";

	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.AccountName);

	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.AccountName + Seperator;
	stClientRecord += Client.PhoneNumber + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
bool FindClientByAccountNumber(sClient& Clients, string AccountNumber, vector <sClient> vClients) {
	for (sClient C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Clients = C;
			return true;
		}
	}
	return false;
}
void AddNewClient() {
	sClient Client;
	Client = ReadNewClient();
	AddDateLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddClients() {
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	char AddMore = 'Y';
	do {
		system("cls");
		cout << "Adding New Client: \n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void ShowAddNewClinetsScreen() {
	cout << "\n----------------------\n";
	cout << "\tAdd Cleints Screen";
	cout << "\n-----------------------\n";
	AddClients();
}
void PrintClientRecord(sClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.AccountName;
	cout << "| " << left << setw(12) << Client.PhoneNumber;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void ShowAllClientsScreen() {
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\tClients List ( " << vClients.size() << ") Client(s).";
	cout << "\n________________________________________________________";
	cout << "__________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\tNo Clinets Available In the Screen!";
	else
		for (sClient Client : vClients) {
			PrintClientRecord(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}



void PrintRecord(sClient clinet) {

	cout << " Account Number: ";
	cout << clinet.AccountNumber << endl;

	cout << " PinCode: ";
	cout << clinet.PinCode << endl;

	cout << " Name: ";
	cout << clinet.AccountName << endl;

	cout << " Phone: ";
	cout << clinet.PhoneNumber << endl;

	cout << " AccountBalance: ";
	cout << clinet.AccountBalance << endl;

}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) {

	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients) {
	fstream MyFile;
	string DataLine;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (sClient C : vClients) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}
		MyFile.close();
	}
	return vClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	sClient Clients;
	char x = 'n';
	if (FindClientByAccountNumber(Clients, AccountNumber, vClients) == true) {
		PrintRecord(Clients);
		cout << "Are you sure you want to delete this client? y/n ";
		cin >> x;
		if (towupper(x) == 'Y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}
}
string ReadAccountNumber() {
	string AccountNumber = "";
	cout << "Enter Account Number: ";
	cin >> AccountNumber;
	return AccountNumber;
}
void ShowDeleteClientScreen() {
	cout << "\n----------------------\n";
	cout << "\tDelete Cleints Screen";
	cout << "\n-----------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
sClient ChangeClinetRecord(string AccountNumber) {
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.AccountName);

	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	sClient Clients;
	char x = 'n';
	if (FindClientByAccountNumber(Clients, AccountNumber, vClients) == true) {
		PrintRecord(Clients);
		cout << "Are you sure you want to update this client? y/n ";
		cin >> x;
		if (towupper(x) == 'Y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClinetRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Update Successfully.";
			return true;
		}
	}
	else {
		cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}
}

void ShowUpdateClientScreen() {
	cout << "\n----------------------\n";
	cout << "\tUpdate Cleints Screen";
	cout << "\n-----------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowFindClientScreen() {
	cout << "\n----------------------\n";
	cout << "\tFind Cleints Screen";
	cout << "\n-----------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(Client, AccountNumber, vClients) == true)
		PrintRecord(Client);
	else
		cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
}
void ShowTransctionsMenue();
void GoBackToTransctions()
{
	int x;
	cout << "\n\nPress Any Key To Go Back To Transctions Menue ..";
	system("pause>0");
	ShowTransctionsMenue();

}
void GoBackToMainMenu()
{
	int x;
	cout << "\n\nPress Any Key To Go Back To Main Menu Screen..";
	system("pause>0");
	ShowMainMenue();

}
short ReadTransctionsMeneue(){
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}
short ReadMainMenue() {

	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}
void ShowEndsScreen() {
	cout << "-------------------------------\n";
	cout << "\tProgram Ends\n";
	cout << "-------------------------------";
	system("pause>0");
}
double ChangeDeposit(sClient Clients, double Number) {
	Clients.AccountBalance += Number;
	return Clients.AccountBalance;
}
double Changewidthdraw(sClient Clients, double Number) {
	Clients.AccountBalance -= Number;
	return Clients.AccountBalance;
}
bool DeositClientByAccountNumber(string AccountNumber, vector <sClient>& vClients, double Amount)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{

		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

				return true;
			}
		}
		return false;
	}
}

void ShowDeositScreen() {
	sClient Client;
	cout << "\n----------------------\n";
	cout << "\tDeosit Screen";
	cout << "\n-----------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(Client, AccountNumber, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintRecord(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;
	DeositClientByAccountNumber(AccountNumber, vClients, Amount);
}

void ShowWithdrawScreen() {
	sClient Client;
	cout << "\n----------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!FindClientByAccountNumber(Client, AccountNumber, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintRecord(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DeositClientByAccountNumber(AccountNumber, vClients, Amount * -1);
}
void PrintClientRecord2(sClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.AccountName;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void ShowTotalBalanceClientsScreen() {
	double sum = 0;
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\tBalance List ( " << vClients.size() << ") Client(s).";
	cout << "\n________________________________________________________";
	cout << "__________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\tNo Clinets Available In the Screen!";
	else
		for (sClient Client : vClients) {
			PrintClientRecord2(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient& C : vClients) {
		sum += C.AccountBalance;
	}
	cout << "\n\t\t\t\Total Balance = " << sum;
}


void PerfomtTransctionsOption(enTransctionsOptions TransctionsMenueOption) {

	switch (TransctionsMenueOption) {
	case enTransctionsOptions::eDeposit:
		system("cls");
		ShowDeositScreen();
		GoBackToTransctions();

		break;
	case enTransctionsOptions::ewithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransctions();
		break;
	case enTransctionsOptions::eTotalbalances:
		system("cls");
		ShowTotalBalanceClientsScreen();
		GoBackToTransctions();
		break;
	case enTransctionsOptions::eMainMenue:
		system("cls");
		GoBackToMainMenu();
		break;

	}
}
void ShowTransctionsMenue() {

	system("cls");
	cout << "=======================================\n";
	cout << "\t\tTransctions Screen\n";
	cout << "=======================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] withdraw.\n";
	cout << "\t[3] Total balance.\n";
	cout << "\t[4] Main Menue.\n";
	
	cout << "=======================================\n";
	PerfomtTransctionsOption((enTransctionsOptions)ReadTransctionsMeneue());
}

void PerfomMainMenueOption(enMainMenueOptions MainMenueOption) {

	switch (MainMenueOption) {
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();

		break;
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClinetsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenueOptions::eTransctions:
		system("cls");
		ShowTransctionsMenue();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndsScreen();
		break;
	}
}
void ShowMainMenue() {

	system("cls");
	cout << "=======================================\n";
	cout << "\t\tMain Screen\n";
	cout << "=======================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Show Client Info.\n";
	cout << "\t[6] Transctions.\n";
	cout << "\t[7] Exit.\n";
	cout << "=======================================\n";
	PerfomMainMenueOption((enMainMenueOptions)ReadMainMenue());
}
int main()
{
	ShowMainMenue();
}
