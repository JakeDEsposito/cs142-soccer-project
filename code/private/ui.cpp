#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "ledge.h"
#include "player.h"
using namespace std;

bool endProgram(Ledge & ledger)
{
	string control="N";
	cout<<"Press [Y] to confirm program exit or [N] to cancel:\t";
	cin>>control;
	cout<<endl;
	if(toupper(control.at(0))=='Y')
	{
		cout<<"Press [Y] If you would like to save before exiting or [N] to exit without saving:\t";
		cin>>control;
		cout<<endl;
		if(toupper(control.at(0))=='Y')
		{
			return saveLedger(ledger);
		}
	}
	return false;
}

bool saveLedger(Ledge & ledger)
{
	string fileName;
	cout<<"Enter the name you would like for the file (WARNING WILL OVERWRITE FILE SPECIFIED IF IT PRE-EXISTS) press [C] to cancel:\n\t";
	cin>>fileName;
	cout<<endl;
	if(toupper(fileName.at(0))=='C')
	{
		if((fileName.compare("c")==0)||(fileName.compare("C")==0))
		{
			return false;
		}
	}
	ledger.save(fileName);
	return true;
}

void print(const vector<Player> & playerV)
{
	ofstream outstr;
	string control;
	
	while(true)
	{
		string fileName;
		cout<<"Enter the name of the file you would like to load:\t";
		cin>>fileName;
		cout<<endl;
		
		outstr.open(fileName);
		if(outstr.fail())
		{
			cout<<"ERROR: failed to open/create file "+fileName+"!!!"<<endl;
			cout<<"\tPress [Y] to try a diffrent file or [N] to cancel:\t";
			cin>>control;
			
			if(toupper(control.at(0))=='N')
			{
				break;
			}
		}
		else
		{
			vector<string> cat={"U6", "U8", "U10", "U12", "U14", "U17"};
			
			for(string c: cat)
			{
				for(Player p: playerV)
				{
					if(c.compare(p["ca"])==0)
					{
						outstr<<p["fn"]<<p["ln"]<<p["by"]<<p["ca"]<<p["rs"]<<endl;
					}
				}
			}
			break;
		}
	}
}

void displayP(vector<Player> & playerV, int c)
{
	int temp=-3+c;
	while (temp<0)
	{
		temp+=playerV.size();
	}
	
	for(int i=0;i<8;i++)
	{
		if(temp==c)
		{
			cout<<" >  "<<temp<<"\t";
		}
		else
		{
			cout<<"    "<<temp<<"\t";
		}
		cout<<"Name:  "<<playerV[temp].getName()<<"\tYOB:  "<<playerV[temp].getYOB();
		cout<<"\tCategory:  "<<playerV[temp].getCategoryAsString()<<"\tRegistered:  ";
		cout<<playerV[temp].getRegistration()<<endl;
		temp=(temp+1)%playerV.size();
	}

}

bool searchLogic(Ledge & playerList, vector<Player> & players)
{
	string control;

	string fn, ln, key;
	int YOB, cat, reg;

	cout<<"Enter the first name to filter by or [N] to skip this filter:\t";
	cin>>control;
	cout<<endl;
	if(control.compare("N")==0||control.compare("n")==0)
	{
		fn="";
	}
	else
	{
		fn=control;
	}

	cout<<"Enter the last name to filter by or [N] to skip this filter:\t";
	cin>>control;
	cout<<endl;
	if(control.compare("N")==0||control.compare("n")==0)
	{
		ln="";
	}
	else
	{
		ln=control;
	}

	cout<<"Enter the keyword to filter by or [N] to skip this filter:\t";
	cin>>control;
	cout<<endl;
	if(control.compare("N")==0||control.compare("n")==0)
	{
		key="";
	}
	else
	{
		key=control;
	}

	cout<<"Enter the year of birth to filter by or [0] to skip this filter:\t";
	cin>>YOB;
	cout<<endl;
	
	cout<<"Enter the catagory number to filter by or [0] to skip this filter:\t";
	cin>>cat;
	cout<<endl;

	cout<<"Enter [0] to filter out registered players, [1] to filter out unregistered ";
	cout<<endl<<"\tplayers, or [3] to skip this filter:\t";
	cin>>reg;
	cout<<endl;

	players=playerList.search(fn, ln, key, YOB, cat, reg);
	if(players.size()==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool searchView(Ledge & playerList, vector<Player> & p)
{
	string control;
	bool rExit, pExit;
	int playerN=0;

	while(true)
	{
		cout<<"Options are: [F]ilter the player list, [N]ext player, P[r]eviose player, E[d]it player, ";
		cout<<"\n\t[P]rint player list, E[x]it filter view, [E]xit Program"<<endl;
		cout<<"Choice:\t";
		cin>>control;
		
		switch(toupper(control.at(0)))
		{
			case 'F':
			{
				if(searchLogic(playerList, p)==false)
				{
					cout<<"ERROR: No results found, "<<endl;
				}
				break;
			}
			case 'N':
			{
				playerN++;
				playerN=(playerN%p.size());
				displayP(p, playerN);
				break;
			}
			case 'R':
			{
				playerN--;
				playerN=(playerN%p.size());
				displayP(p, playerN);
				break;
			}
			case 'D':
			{
				string ofn, oln, nfn, nln;
				int nYOB, reg;
				bool nReg;

				ofn=p[playerN]["fn"];
				oln=p[playerN]["ln"];

				cout<<"Enter their new first name  or [N] to leave it unchanged:\t";
				cin>>nfn;
				if(toupper(nfn.at(0))=='N')
				{
					if(nfn.compare("n")==0||nfn.compare("N")==0)
					{
						nfn="";
					}
				}
				
				cout<<endl<<"Enter their new last name or [N] to leave it unchanged:\t";
				cin>>nln;
				if(toupper(nln.at(0))=='N')
				{
					if(nln.compare("n")==0||nln.compare("N")==0)
					{
						nln="";
					}
				}
				
				cout<<endl<<"Enter their new year of birth or [0] to leave it unchanged:\t";
				cin>>nYOB;
				
				cout<<endl<<"Enter [1] if they are registered, [0] if they are un-registered, or [3] to leave it unchanged:\t";
				cin>>reg;
				if(reg!=1||reg!=0)
				{
					reg=-1;
				}

				playerList.editPlayer(oln,ofn,nfn,nln,nYOB,reg);
				break;
			}
			case 'P':
			{
				print(p);
				break;
			}
			case 'X':
			{
				rExit=true;
				pExit=false;
				break;
			}
			case 'E':
			{
				rExit=pExit=true;
				break;
			}
			default:
			{
				cout<<"ERROR: Option Does Not Exist";
				break;
			}
		}
		if(rExit)
		{
			break;
		}
	}
	
	return pExit;
}

int main()
{
	int year;
	cout<<"Enter the year for the new season:\t";
	cin>>year;
	cout<<endl;
	
	Ledge ledger;
	ledger.programYear=year;

	string control="N";
	
	cout<<"Press [Y] if you would like to load a previose session or [N] if you would like to start fresh";
	cin>>control;
	cout<<endl;
	
	while(toupper(control.at(0))=='Y')
	{
		string fileName;
		
		cout<<"Enter the name of the file you would like to load:\t";
		cin>>fileName;
		cout<<endl;
		
		int tempC=ledger.load(fileName);
		if(tempC=1)
		{
			cout<<"ERROR: Attempted to open a file that does not exist!!!"<<endl;
			cout<<"\tPress [Y] to try a diffrent file or [N] to launch without loading a previose session:\t";
			cin>>control;
			cout<<endl<<endl;
		}
	}
	
	while (true)//main view
	{
		bool endP=false;
		cout<<"Options are: [N]ew season, [A]dd player, [F]ilter the player list, [S]ave ledger,";
		cout<<"[P]rint player list, [D]isplay stats, [E]xit Program"<<endl;
		cout<<"Choice:\t";
		cin>>control;
		
		switch(toupper(control.at(0)))
		{
			case 'N':
			{
				cout<<"WARNING: This will delete all players!!! Press [Y] to start a new season or [N] to cancel:\t";
				cin>>control;
				cout<<endl;
				
				if(toupper(control.at(0))=='Y')
				{
					year;
					cout<<"Enter the year for the new season:\t";
					try
					{
						cin>>year;
						cout<<endl;
					}
					catch(const exception& e)
					{
						cout<<endl<<"ERROR: Invalid Input"<<endl;
					}
					
					ledger.wipe(year);
				}
				break;
			}
			case 'A':
			{
				string fn;
				string ln;
				int yob;
				bool regStat;
				
				cout<<"Enter their first name:\t";
				cin>>fn;
				
				cout<<endl<<"Enter their last name:\t";
				cin>>ln;
				
				cout<<endl<<"Enter their year of birth:\t";
				cin>>yob;
				
				cout<<endl<<"Enter [1] if they are registered or [0] if they are un-registered:\t";
				cin>>regStat;
				cout<<endl;
				
				ledger.addPlayer(Player(fn, ln, yob, regStat));
				break;
			}
			case 'F':
			{
				vector<Player> players;
				if(searchLogic(ledger, players))
				{
					endP=searchView(ledger, players);
				}
				break;
			}
			case 'P':
			{
				vector<Player> playerV=ledger.allPlayers();
				print(playerV);
				break;
			}
			case 'D':
			{
				vector<string> cat={"U6", "U8", "U10", "U12", "U14", "U17"};
				vector<Player> playerV=ledger.allPlayers();
				
				vector<int> totalPlayers={0,0,0,0,0,0};
				vector<int> totalNumPaid={0,0,0,0,0,0};
				int totalPl=0;
				int totalPa=0;
				
				for(int i=0;i<cat.size();i++)
				{
					for(Player p: playerV)
					{
						if(cat[i].compare(p["ca"])==0)
						{
							totalPlayers[i]++;
							if(p.getRegistration())
							{
								totalNumPaid[i]++;
							}
						}
					}
				}
				
				for(int v: totalPlayers)
				{
					totalPl+=v;
				}
				for(int v: totalNumPaid)
				{
					totalPa+=v;
				}
				
				cout<<"Total player count:\t"<<totalPl<<endl;
				cout<<"Total paying player count:\t"<<totalPa<<endl;
				cout<<"Total non-paying player count:\t"<<(totalPl-totalPa)<<endl;
				for(int i=0;i<cat.size();i++)
				{
					cout<<cat[i]<<":"<<endl;
					cout<<"\tPlayer count:\t"<<totalPlayers[i]<<endl;
					cout<<"\tPaying player count:\t"<<totalNumPaid[i]<<endl;
					cout<<"\tNon-playing player count:\t"<<(totalPlayers[i]-totalNumPaid[i])<<endl;
				}
				
				break;
			}
			case 'S':
			{
				bool temp=saveLedger(ledger);
				break;
			}
			case 'E':
			{
				endP=endProgram(ledger);
				break;
			}
			default:
			{
				cout<<"ERROR: Option Does Not Exist";
				break;
			}
		}
		if(endP)
		{
			break;
		}
	}
	
	return 0;
}
