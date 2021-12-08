#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "ledge.h"
#include "ledgefilter.h"
#include "player.h"
using namespace std;

bool endProgram(Ledge & ledger)
{
	string control=N;
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

bool searchView(Ledge & playerList)
{
	string control;
	bool r=false;
	
	
	
	while(true)
	{
		cout<<"Options are: [F]ilter the player list, [N]ext player, P[r]eviose player, E[d]it player, "+
				"\n\t[P]rint player list, E[x]it filter view, [E]xit Program"<<endl;
		cout<<"Choice:\t";
		cin>>control;
		
		
	}
	
	return r;
}

int main()
{
	int year;
	cout<<"Enter the year for the new season:\t";
	cin>>year;
	cout<<endl;
	
	Ledge ledger=new Ledge();
	
	string control=N;
	
	cout<<"Press [Y] if you would like to load a previose session or [N] if you would like to start fresh";
	cin>>control;
	cout<<endl;
	
	while(toupper(control.at(0))=='Y')
	{
		string fileName;
		
		cout<<"Enter the name of the file you would like to load:\t";
		cin>>fileName;
		cout<<endl;
		
		if(ledger.load(fileName)=1)
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
		cout<<"Options are: [N]ew season, [A]dd player, [F]ilter the player list, [S]ave ledger,"+
				"[P]rint player list, [D]isplay stats, [E]xit Program"<<endl;
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
					cout<<"Enter the year for the new season:\t";
					cin>>year;
					cout<<endl;
					
					ledger=new Ledge();
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
				endP=searchView(ledger);
				break;
			}
			case 'P':
			{
				ofstream outstr;
				
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
						vector<Player> playerV=ledger.allPlayers();
						
						for(string c: cat)
						{
							for(Player p: playerV)
							{
								if(c.compare(p[ca])==0)
								{
									outstr<<p[fn]<<p[ln]<<p[by]<<p[ca]<<p[rs]<<endl;
								}
							}
						}
						break;
					}
				}
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
						if(cat[i].compare(p[ca])==0)
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
