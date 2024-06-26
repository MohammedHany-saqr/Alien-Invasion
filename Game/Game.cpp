#include "Game.h"
#include <iostream>
#include "../Units/Unit.h"
#include <ctime>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "../Data Structure/LinkedQueue.h"
#include "../Units/AlienDrone.h"
#include "../Units/AlienMonster.h"
#include "../Units/AlienSoldier.h"
#include "../Units/EarthSoldier.h"
#include "../Units/EarthGunnery.h"
#include "../Units/EarthTank.h"
#include <iomanip>
#include"windows.h"
using namespace std;
Game::Game()
{
	TimeStep = 1;
	AArmy = new AlienArmy;
	EArmy = new EarthArmy;
	Gen1 = new Generator(this);
	status = false;
	MOD = false;
}
void Game::StartGame()
{
	srand((time(nullptr))); //Create New Seed
	LoadFromFile();    //Read data from the input file
	if (status == false) {
		cout << "Input Not Valid";
		return;
	}
	cout << "For Interactive Mode press 1" << endl;
	cout << "For Silent Mode press 2" << endl;
	int x;
	cin >> x;
	while (x != 2 && x != 1) {
;		cout << "Please Enter 1 OR 2" << endl;
		cin >> x;
	}
	if (x == 1) MOD = true;
	if (status) {
		cout << "Simulation Starts"<<endl;
		do {
			if(MOD) cout << " Current Timestep => " << TimeStep << endl;
			Gen1->Execute();    //Generate Units
			if (MOD)
			{
				EArmy->PrintEarthArmyInfo();	//Print EarthArmy Units
				AArmy->PrintAlianArmyInfo();	//Print AlienArmy Units
				cout << "==========" << " Units fighting at current step " << "==========\n";
			}
			Unit* unit = nullptr;
			
			//EarthArmy
			if (EArmy->GetASoldierToAttack(unit)) { //Get Soldier To Attack
				unit->Attack(this);
			}
			if (EArmy->GetATankToAttack(unit)) {	//Get Tank To Attack
				unit->Attack(this);
			}
			if (EArmy->GetAGunneryToAttack(unit)) {	//Get Gunnery To Attack
				unit->Attack(this);
			}

			// Alein Army
			if (AArmy->GetASoldierToAttack(unit)) {	//Get Soldier To Attack
				unit->Attack(this);
				////AArmy->AddAUnit(unit);
			}
			if (AArmy->GetAMonsterToAttack(unit)) {
				unit->Attack(this);
				////AArmy->AddAUnit(unit);
			}
			if (AArmy->GetFirstDroneToAttack(unit)) {
				unit->Attack(this);
				//AArmy->AddAUnit(unit);
			}
			if (MOD) PrintKilledUnitsInfo();
			TimeStep++;
			setColor(3); // Set Color To console
			if (MOD) cout << "\n\nPress any key to move to next step";
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (MOD) cout<< endl << endl;
			if (TimeStep > 40) {
				if (AArmy->GetMonstersCount() + AArmy->GetSoldiersCount() + AArmy->GetDronesCount() == 0) {
					cout << "Alien Army Lose";
					EArmy->setStatus(true); //Set EarthArmy To lose
					createOutput(); //Create Output file
					break;
				}
				if (EArmy->GetGunnersCount() + EArmy->GetSolidersCount() + EArmy->GetTanksCount() == 0) {
					cout << "Earth Army Lose";
					AArmy->setStatus(true); //Set AlienArmy To lose
					createOutput();	//Create Output file
					break;
				}
			}
			if (TimeStep == 40) {
				cout << "Drew";
				createOutput();
				break;
			}
		} while(!MOD || _getch()); //reads a single character from the keyboard
	}
	else {
		cout << "Input Not Valid";
	}
}

AlienArmy* Game::GetAlienArmy()
{
	return AArmy;
}

EarthArmy* Game::GetEarthArmy()
{
	return EArmy;
}

void Game::PushKilledUnit(Unit*& u)
{
	u->setTd(TimeStep);
	KilledList.enqueue(u);
}

void Game::PrintKilledUnitsInfo()
{
	//Print Killed Units Info

	cout << "==========" << " Killed/Destructed Units " << "==========\n";
	
	KilledList.print(" units ");
}

int Game::GetTimeStep()
{
	return TimeStep;
}

void Game::createOutput()
{
	float Data[12];
	/*
		Data[0] AlienDrone
		Data[1]	AlienMonster
		Data[2]	AlienSoldier
		Data[3] AlienArmy Total DF
		Data[4] AlienArmy Total Dd
		Data[5] AlienArmy Total Db
		Data[6]	EarthSoldier
		Data[7]	EarthTank
		Data[8]	EarthGunnery
		Data[9] EarthArmy Total DF
		Data[10] EarthArmy Total Dd
		Data[11] EarthArmy Total Db
	*/
	for (int i = 0; i < 12; i++) Data[i] = 0;
	ofstream output;
	output.open("output.txt");
	output << "Td\tID\tTj\tDf\tDd\tDb\n";
	Unit* unit;

	while (KilledList.dequeue(unit)) {
		output	<< unit->getTd() << "\t" 
				<< unit->GetID() << "\t" 
				<< unit->getTj() << "\t";

		int Df = ((unit->getTa() - unit->getTj()) >= 0) ? (unit->getTa() - unit->getTj()) : 0;
		int Dd = ((unit->getTd() - unit->getTa()) >= 0) ? (unit->getTd() - unit->getTa()) : 0;
		int Db = ((unit->getTd() - unit->getTj()) >= 0) ? (unit->getTd() - unit->getTj()) : 0;

		if (dynamic_cast <AlienDrone*> (unit) || dynamic_cast <AlienMonster*> (unit) || dynamic_cast <AlienSoldier*> (unit)) {
			if (dynamic_cast <AlienDrone*> (unit) != NULL) {
				Data[0] += 1;
			}
			else if (dynamic_cast <AlienMonster*> (unit) != NULL) {
				Data[1] += 1;
			}
			else if (dynamic_cast <AlienSoldier*> (unit) != NULL) {
				Data[2] += 1;
			}
			Data[3] += Df;
			Data[4] += Dd;
			Data[5] += Db;
		}
		if (dynamic_cast <EarthGunnery*> (unit) || dynamic_cast <EarthSoldier*> (unit) || dynamic_cast <EarthTank*> (unit)) {
			if (dynamic_cast <EarthSoldier*> (unit) != NULL) {
				Data[6] += 1;
			}
			else if (dynamic_cast <EarthTank*> (unit) != NULL) {
				Data[7] += 1;
			}
			else if (dynamic_cast <EarthGunnery*> (unit) != NULL) {
				Data[8] += 1;
			}
			Data[9] += Df;
			Data[10] += Dd;
			Data[11] += Db;
		}

		output << Df << "\t" << Dd << "\t" << Db << "\n";
		delete unit; // delete the unit
	}
	//Print The Winner
	if (EArmy->getStatus() && !AArmy->getStatus()) output << "WIN\n";
	else if (!EArmy->getStatus() && AArmy->getStatus())	output << "Lose\n";
	else output << "Drew\n";
	
	// Print EarthArmy Info
	output << "For Earth Army:\n"
		<< "ES=> " << Data[6] + EArmy->GetSolidersCount() << "\t"
		<< "ET=> " << Data[7] + EArmy->GetTanksCount() << "\t"
		<< "EG=> " << Data[8] + EArmy->GetGunnersCount() << "\n";
	if (Data[6] + EArmy->GetSolidersCount() <= 0)
		output << "ES destructed percent=> There is no ES responed"<< "\t";
	else
		output << "ES destructed percent=> " << Data[6] / (Data[6] + EArmy->GetSolidersCount()) * 100 << "\t";
	if (Data[7] + EArmy->GetTanksCount() <= 0)
		output << "ET destructed percent=> There is no ET responed" << "\t";
	else
		output << "ET destructed percent=> " << Data[7] / ( Data[7] + EArmy->GetTanksCount()) * 100 << "\t";
	if(Data[8] + EArmy->GetGunnersCount()<=0)
		output << "EG destructed percent=> There is no EG responed" << "\n";
	else
		output << "EG destructed percent=> " << Data[8] / ( Data[8] + EArmy->GetGunnersCount()) * 100 << "\n";
	
	output << "Total destructed percent=>" << (Data[6] + Data[7] + Data[8]) / (Data[6] + EArmy->GetSolidersCount() + Data[7] + EArmy->GetTanksCount() + Data[8] + EArmy->GetGunnersCount()) * 100 << "\n";
	if (Data[6] + Data[7] + Data[8] <= 0)
	{
		output << "There Is no Destruied EarthUnits\n";
		output << "Average of Df=> " << 0 << "\t"
			<< "Average of Dd=> " << 0 << "\t"
			<< "Average of Db=> " << 0 << "\n"
			<< "(Df/Db)%=> " << 0 << "\t"
			<< "(Dd/Db)%=> " << 0 << "\n";
	}
	else 
		output << "Average of Df=> " << Data[9] / (Data[6] + Data[7] + Data[8]) << "\t"
			<< "Average of Dd=> " << Data[10]/ (Data[6] + Data[7] + Data[8]) << "\t"
			<< "Average of Db=> " << Data[11]/ (Data[6] + Data[7] + Data[8]) << "\n"
			<< "(Df/Db)%=> " << (Data[9] / Data[11]) * 100 << "\t"
			<< "(Dd/Db)%=> " << (Data[10] / Data[11]) * 100 << "\n";

	output << "For Alien Army:\n"
		<< "AS=> " << Data[2] + EArmy->GetSolidersCount() << "\t"
		<< "AM=> " << Data[1] + EArmy->GetTanksCount() << "\t"
		<< "Ad=> " << Data[0] + EArmy->GetGunnersCount() << "\n";

	if (Data[2] + AArmy->GetSoldiersCount() <= 0)
		output << "AS destructed percent=> There is no ES responed" << "\t";
	else
		output << "AS destructed percent=> " << Data[2] / (Data[2] + AArmy->GetSoldiersCount()) * 100 << "\t";

	if (Data[1] + AArmy->GetMonstersCount() <= 0)
		output << "AM destructed percent=> There is no ET responed" << "\t";
	else
		output << "AM destructed percent=> " << Data[1] / (Data[1] + AArmy->GetMonstersCount()) * 100 << "\t";

	if (Data[0] + AArmy->GetDronesCount() <= 0)
		output << "AD destructed percent=> There is no EG responed" << "\n";
	else
		output << "AD destructed percent=> " << Data[0] / (Data[0] + AArmy->GetDronesCount()) * 100 << "\n";

	output << "Total destructed percent=>" << (Data[0] + Data[1] + Data[2]) / (Data[0] + AArmy->GetDronesCount() + Data[1] + AArmy->GetMonstersCount() + Data[2] + AArmy->GetSoldiersCount()) * 100 << "\n";
	if (Data[0] + Data[1] + Data[2] <= 0)
	{
		output << "There Is no Destruied AlienUnits\n";
		output << "Average of Df=> " << 0 << "\t"
			<< "Average of Dd=> " << 0 << "\t"
			<< "Average of Db=> " << 0 << "\n"
			<< "(Df/Db)%=> " << 0 << "\t"
			<< "(Dd/Db)%=> " << 0 << "\n";
	}
	else
		output << "Average of Df=> " << Data[3] / (Data[0] + Data[1] + Data[2]) << "\t"
		<< "Average of Dd=> " << Data[4] / (Data[0] + Data[1] + Data[2]) << "\t"
		<< "Average of Db=> " << Data[5] / (Data[0] + Data[1] + Data[2]) << "\n"
		<< "(Df/Db)%=> " << (Data[3] / Data[5]) * 100 << "\t"
		<< "(Dd/Db)%=> " << (Data[4] / Data[5]) * 100 << "\n";
}

Game::~Game()
{
	delete AArmy;
	delete EArmy;               //free reserved memory//
	delete Gen1;             
}
void Game::setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); //Set Console Color
}
void Game::LoadFromFile() {
	int Data[20];
	/*
	index 0		UnitNum
	index 1:3	percentage for Earth : Solider, Tank, Gunner.
	index 4:6	percentage for Alien : Solider, Monster, Drone.
	index 7		percent to generate new unit(prob)
	index 8:13	Power, Health, AttackCapacity for EarthUnits
	index 14:19	Power, Health, AttackCapacity for AleinUnits
	*/
	for (int i = 0; i < 20; i++) {
		Data[i] = -1;
	}
	//Get File Name
	string Name;
	cout << "Please Enter The Name Of The Input File: ";
	cin >> Name;
	Name = Name + ".txt";
	//Read File Data
	ifstream GenFile(Name);
	if (GenFile.is_open()) {
		int i = 0;
		while (!GenFile.eof()) {
			GenFile >> Data[i];
			//Check if Data is Negative so it is broken data
			if ((i < 9 || (i >= 9 && i % 2 == 0)) && Data[i] < 0) {
				status = false;
				return;
			}
			Data[i] = abs(Data[i]); // Abs the Negtive value when input range 2-50 it take -50 so make abs to it
			i++;
		}
		GenFile.close(); //Close the file
		if (i == 20) { //Check that all data have been entered
			DataChecker(Data);//Check The Data
			if (status) Gen1->SetDate(Data); // if its right gen start his work
			return;
		}
		else {
			status = false;
			return;
		}
	}
	else {
		status = false;
		return;
	}
}

bool Game::GetMod()
{
	return MOD;
}

void Game::DataChecker(int Data[])
{
	if (Data[1] + Data[2] + Data[3] == 100) {//EarthGen Units Prob
		if (Data[4] + Data[5] + Data[6] == 100) {//AlienGen Units Prob
			if (Data[7] < 100 || Data[7] > 0) {//ProbGen Units
				if (Data[9] > Data[8]) {//EarthRange Unit
					if (Data[11] > Data[10]) {//EarthHealth Unit
						if (Data[13] > Data[12]) {//EarthAttackCapacity
							if (Data[15] > Data[14]) {//AlienRange Unit
								if (Data[17] > Data[16]) {//AlienHealth Unit
									if (Data[19] > Data[18]) {//AlienAttackCapacity
										status = true;
										return;
									}
									else {
										//AlienAttackCapacity Unit Not True
										status = false;
									}
								}
								else {
									//AlienHealth Unit Not True
									status = false;
								}
							}
							else {
								//AlienRange Unit Not True
								status = false;
							}
						}
						else {
							//EarthAttackCapacity Unit Not True
							status = false;
						}
					}
					else {
						//EarthHealth Unit Not True
						status = false;
					}
				}
				else {
					//EarthRange Unit Not True
					status = false;
				}
			}
			else {
				//ProbGen Units not True
				status = false;
			}
		}
		else {
			//AlienGen Units Prob not True
			status = false;
		}
	}
	else {
		//EarthGen Units Prob not True
		status = false;
	}
}
