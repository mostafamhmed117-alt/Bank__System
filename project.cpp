#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

const string ClientFileName = "Client.txt";
void ShowMainMenue(void);
void ShowTransactionScreen(void);
struct stInfo
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkToDelete = false;
};

vector<string> Split(string Line)
{
	short pos = 0;
	string delim = "#//#";
	string sWord = "";
	vector<string> vString;
	while ((pos = Line.find(delim)) != std::string::npos)
	{
		sWord = Line.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		Line.erase(0, pos + delim.length());
	}
	if (Line != "")
	{
		vString.push_back(Line);
	}
	return vString;
}

stInfo ConvertLineToRecord(string Line)
{
	vector<string> vString = Split(Line);
	stInfo Client;
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);
	return Client;
}

vector<stInfo> LoadClientDataFromFile(string FileName)
{
	vector<stInfo> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//Read Mode
	if (MyFile.is_open())
	{
		string Line;
		stInfo Client;
		while (getline(MyFile, Line))
		{
			vClient.push_back(ConvertLineToRecord(Line));
		}
		MyFile.close();
	}
	return vClient;
}

void PrintClientRecord(stInfo &Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(15) << Client.PinCode;
	cout << "| " << left << setw(20) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(15) << Client.AccountBalance<<endl;

}

void ShowAllClientData()
{
	vector<stInfo> vClient = LoadClientDataFromFile(ClientFileName);
	cout << "\t\t\tClient List (" << vClient.size() << ") Client(s)." << endl;
	cout << "-------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << " Account Number ";
	cout << "| " << left << setw(15) << " Pin Code ";
	cout << "| " << left << setw(20) << " Name ";
	cout << "| " << left << setw(15) << " Phone ";
	cout << "| " << left << setw(15) << " Account Balance ";
	cout << "\n-------------------------------------------------------------------------------------------\n";
	for (stInfo& Client : vClient)
	{
		PrintClientRecord(Client);
	}
	cout << "\n-------------------------------------------------------------------------------------------\n";
}

string ConvertRecordToLine(stInfo &Client)
{
	string Line;
	Line += Client.AccountNumber + "#//#";
	Line += Client.PinCode + "#//#";
	Line += Client.Name + "#//#";
	Line += Client.Phone + "#//#";
	Line += to_string(Client.AccountBalance);
	return Line;
}

void AddClientToFile(stInfo &Client)
{
	string RecordToLine = ConvertRecordToLine(Client);
	fstream MyFile;
	MyFile.open(ClientFileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << RecordToLine << endl;
		MyFile.close();
	}
}

bool IsClientExist(string AccountNumber, vector<stInfo>& vClient,stInfo &Client)
{
	for (stInfo& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void AddNewClient()
{
	vector<stInfo> vClients = LoadClientDataFromFile(ClientFileName);
	stInfo NewClient;
	string AddMore;

	do
	{
		system("cls");
		cout << "Adding New Clinet:\n\n";
		cout << "Enter Account Number? ";
		
		getline(cin >> ws, NewClient.AccountNumber);

		while (IsClientExist(NewClient.AccountNumber, vClients,NewClient))
		{
			cout << "Clinet with [" << NewClient.AccountNumber << "] already exists, Enter anther Account Number? ";
			getline(cin >> ws, NewClient.AccountNumber);
		}

		cout << "Enter Pin Code? ";
		getline(cin, NewClient.PinCode);
		cout << "Enter Name? ";
		getline(cin, NewClient.Name);
		cout << "Enter Phone? ";
		getline(cin, NewClient.Phone);
		cout << "Enter Account Balance? ";
		cin >> NewClient.AccountBalance;
		AddClientToFile(NewClient);
		cout << "Client Added Successfuly, do you want to add more client?(Y/N)? ";
		cin >> AddMore;
	} while (AddMore == "y" || AddMore == "Y");
}

void ShowAddClientScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "-------------------------------------------\n";
	AddNewClient();
}

bool MarkClientToDelete(string AccountNumber, vector<stInfo>& vClients)
{
	for (stInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkToDelete = true;
			return true;
		}
	}
	return false;
}

void SaveClientInFile(vector<stInfo>&vClients)
{
	fstream MyFile;
	MyFile.open(ClientFileName, ios::out);
	if (MyFile.is_open())
	{
		for (stInfo &C : vClients)
		{
			if (C.MarkToDelete == false)
			{
				MyFile << ConvertRecordToLine(C) << endl;
			}
		}
		MyFile.close();
	}
}

void ShowClientInfo(stInfo &Client)
{
	cout << "\nThe Following Are the Client details:\n";
	cout << "----------------------------------------------------------\n";
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Pin Code        : " << Client.PinCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone           : " << Client.Phone << endl;
	cout << "Account Balance : " << to_string(Client.AccountBalance) << endl;
	cout << "----------------------------------------------------------\n";
}

void DeleteClient()
{
	vector<stInfo>vClients = LoadClientDataFromFile(ClientFileName);
	stInfo Client;
	string AccountNumber;
	string Answer = "No";
	cout << "\nPlease Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	if (IsClientExist(AccountNumber, vClients,Client))
	{
		ShowClientInfo(Client);
		cout << "\nAre You Sure You Want To Delete This Client?(Y/N)? ";
		cin >> Answer;
		if (Answer == "Y" || Answer == "y")
		{
			MarkClientToDelete(AccountNumber, vClients);
			SaveClientInFile(vClients);
			cout << "\nClient Deleted Succesfuly.\n";
		}
		return;
	}
	
	cout << "\nClient with Account Number [" << AccountNumber << "] is not found!\n";
	
}

void ShowDeleteClientScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tDelete New Clients Screen\n";
	cout << "-------------------------------------------\n";
	DeleteClient();
}

bool Update(string AccountNumber, vector<stInfo>&vClients)
{
	for (stInfo& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			cout << "\nEnter PinCode? ";
			getline(cin>>ws, C.PinCode);
			cout << "Enter Name? ";
			getline(cin, C.Name);
			cout << "Enter Phone? ";
			getline(cin, C.Phone);
			cout << "Enter Account Balance? ";
			cin >> C.AccountBalance;
			return true;
		}
	}
	return false;
}

void UpdateClientInfo()
{
	vector<stInfo> vClients = LoadClientDataFromFile(ClientFileName);
	stInfo Client;
	string AccountNumber;
	string Answer = "No";
	cout << "\nPlease enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	if (IsClientExist(AccountNumber, vClients, Client))
	{
		ShowClientInfo(Client);
		cout << "\nAre you sure you want update this client?(Y/N)? ";
		cin >> Answer;
		if (Answer == "Y" || Answer == "y")
		{
			Update(AccountNumber, vClients);
			SaveClientInFile(vClients);
			cout << "\nClient Update Succesfly.\n";
		}
		return;
	}
	cout << "\nClient with Account Number [" << AccountNumber << "] is not found!\n";

}

void ShowUpdateScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tUpdate Clients Screen\n";
	cout << "-------------------------------------------\n";
	UpdateClientInfo();
}

void FindClientInFile()
{
	vector<stInfo>vClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumber;
	stInfo Client;
	cout << "\nPlease Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	if (IsClientExist(AccountNumber, vClients, Client))
	{
		ShowClientInfo(Client);
		return;
	}
	
	cout << "\nClient With Account Number [" << AccountNumber << "] is not found!\n";

}

void ShowFindScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tUpdate Clients Screen\n";
	cout << "-------------------------------------------\n";
	FindClientInFile();
}

void ShowExitScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "-------------------------------------------\n";
}

string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\nPlease enter AccountNumber? ";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}

bool ConfirmTransactionChoies(vector<stInfo>&vClients,string AccountNumber,double &Amount)
{
	char Answer = 'y';
	cout << "\nAre you sure you want to perform this transaction?(Y/N)? ";
	cin >> Answer;
	if(Answer == 'Y' || Answer == 'y')
	{
		for (stInfo& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				cout << "\nDone successfully, New Balance is: "<< C.AccountBalance<<endl;
				return true;
			}	
		}
	}
	return false;
}

void ShowDepositScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-------------------------------------------\n";
	stInfo Client;
	vector<stInfo> vClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumner = ReadAccountNumber();

	while (!IsClientExist(AccountNumner, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumner << "] does not exist.\n";
		AccountNumner = ReadAccountNumber();
	}
	ShowClientInfo(Client);
	double Amount = 0;
	cout << "Please enter Deposit amount? ";
	cin >> Amount;
	ConfirmTransactionChoies(vClients,AccountNumner,Amount);
	SaveClientInFile(vClients);
}

void ShowWithdrawScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-------------------------------------------\n";
	stInfo Client;
	vector<stInfo> vClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumner = ReadAccountNumber();
	while (!IsClientExist(AccountNumner, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumner << "] does not exist.\n";
		AccountNumner = ReadAccountNumber();
	}
	ShowClientInfo(Client);
	double Amount = 0;
	cout << "Please enter withdraw amount? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the blance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter withdraw amount? ";
		cin >> Amount;
	}
	Amount *= -1;
	ConfirmTransactionChoies(vClients, AccountNumner,Amount);
	SaveClientInFile(vClients);
}

void PrintTotalBalance(vector<stInfo>& vClients)
{
	double TotalBalance = 0;
	for (stInfo& C : vClients)
	{
		TotalBalance += C.AccountBalance;
	}
	cout << "\n\t\t\tTotal Balance = " << TotalBalance << endl;
}

void PrintClientCard(stInfo& Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(20) << Client.Name;
	cout << "| " << left << setw(15) << Client.AccountBalance << endl;

}

void ShowTotalBalances()
{
	vector<stInfo> vClient = LoadClientDataFromFile(ClientFileName);
	cout << "\t\t\tClient List (" << vClient.size() << ") Client(s)." << endl;
	cout << "-------------------------------------------------------------------------------------------\n";
	cout << "|" << left << setw(15) << " Account Number ";
	cout << "| " << left << setw(20) << " Name ";
	cout << "| " << left << setw(15) << " Account Balance ";
	cout << "\n-------------------------------------------------------------------------------------------\n";
	for (stInfo& Client : vClient)
	{
		PrintClientCard(Client);
	}
	cout << "\n-------------------------------------------------------------------------------------------\n";
	PrintTotalBalance(vClient);
}

enum TransactonChoies
{
	enDeposit = 1,
	enWithdraw = 2,
	enTotalBalances = 3,
	enMainMenue = 4
};

short ReadTransactionNumber()
{
	short Number;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Number;
	return Number;
}

void BackToTransactionScreen()
{
	cout << "\nPress any key to go back to Transaction Menue\n";
	system("pause>0");
	ShowTransactionScreen();
}

void PreformYourTransaction(TransactonChoies Ch)
{

	switch (Ch)
	{
	case TransactonChoies::enDeposit:
		system("cls");
		ShowDepositScreen();
		BackToTransactionScreen();
		break;
	case TransactonChoies::enWithdraw:
		system("cls");
		ShowWithdrawScreen();
		BackToTransactionScreen();
		break;
	case TransactonChoies::enTotalBalances:
		system("cls");
		ShowTotalBalances();
		BackToTransactionScreen();
		break;
	case TransactonChoies::enMainMenue:
		ShowMainMenue();
	}
	
}

void ShowTransactionScreen()
{
	system("cls");
	cout << "===========================================================\n";
	cout << "\t\tTransaction Menue Screen\n";
	cout << "===========================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================================\n";
	PreformYourTransaction((TransactonChoies)ReadTransactionNumber());
}

enum enOperation
{
	ShowClient = 1,
	AddClient = 2,
	DeleteClientList = 3,
	UpdateClient = 4,
	FindClient = 5,
	Transaction = 6,
	Exit = 7
};

short ReadOperationNumber()
{
	short Number;
	cout << "Choose what do you want to do? [1 to 7]? ";
	cin >> Number;
	return Number;
}

void BackToMainMenue()
{
	cout << "\nPress any key to go back to main Menue\n";
	system("pause>0");
	ShowMainMenue();
}

void PreformYourMainTask(enOperation Op)
{
	switch (Op)
	{
		case enOperation::ShowClient:
			system("cls");
			ShowAllClientData();
			BackToMainMenue();
			break;
		case enOperation::AddClient:
			system("cls");
			ShowAddClientScreen();
			BackToMainMenue();
			break;
		case enOperation::DeleteClientList:
			system("cls");
			ShowDeleteClientScreen();
			BackToMainMenue();
			break;
		case enOperation::UpdateClient:
			system("cls");
			ShowUpdateScreen();
			BackToMainMenue();
			break;
		case enOperation::FindClient:
			system("cls");
			ShowFindScreen();
			BackToMainMenue();
			break;
		case enOperation::Transaction:
			system("cls");
			ShowTransactionScreen();
			break;
		case enOperation::Exit:
			system("cls");
			ShowExitScreen();
			break;
	}
	
}

void ShowMainMenue()
{
	system("cls");
	cout << "===========================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Clients.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Exist.\n";
	cout << "===========================================================\n";
	PreformYourMainTask((enOperation)ReadOperationNumber());
}

int main()
{
	
	ShowMainMenue();
	return 0;
}
