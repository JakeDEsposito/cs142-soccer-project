#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "ledge.h"
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
			string fileName;
			cout<<"Enter the name you would like for the file (WARNING WILL OVERWRITE FILE SPECIFIED IF IT PRE-EXISTS) press [C] to cancel:\n\t";
			cin>>fileName;
			cout<<endl;
			if(toupper(fileName.at(0))=='C')
			{
				if((fileName.compare("n")==0)||(fileName.compare("N")==0))
				{
					return false;
				}
			}
			ledger.save(fileName);
		}
		return true;
	}
	return false;
}

bool searchView(Vector<Player> & playerList)
{
}

int main()
{
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
		cout<<"Options are: [N]ew season, [A]dd player, [S]earch for player, Save [L]edger,"+
				"[P]rint player list, [D]isplay stats, [E]xit Program"<<endl;
		cout<<"Choice:\t";
		cin>>control;
		switch(toupper(control.at(0)))
		{
			case 'N':
				
				break;
			case 'A':
				
				break;
			case 'S':
				
				endP=searchView();
				break;
			case 'P':
				
				break;
			case 'D':
				
				break;
			case 'E':
				
				break;
			case 'L':
				endP=endProgram(ledger);
				break;
			default:
				cout<<"ERROR: Option Does Not Exist";
				break;
		}
		if(endP)
		{
			break;
		}
	}
	
	return 0;
}