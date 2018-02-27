#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <set>

using namespace std;

int main()
{
	fstream fs;
	fs.open("input.txt", ios::in);
	
	int pack;
	fs>>pack;
	while(pack>0)
	{
		int NumOfPeo, NumOfPair;
		fs>>NumOfPeo>>NumOfPair;	
		
		vector < pair<int, int> > RawData(0);
		for(int i=0; i<NumOfPair; i++)
		{
			int TmpA, TmpB;
			fs>>TmpA>>TmpB;
			RawData.push_back(make_pair(TmpA, TmpB));
		}
		
		/*for(int i=0; i<RawData.size(); i++)
		{
			cout<<RawData[i].first<<" "<<RawData[i].second<<endl;
		}
		cout<<endl;*/
		
		vector < set<int>> Group(0);
		set<int> TmpSet;
		TmpSet.insert(RawData[0].first);TmpSet.insert(RawData[0].second);
		Group.push_back(TmpSet);
		
		
		for(int i=1; i<NumOfPair; i++)
		{
			int Index1=0, Index2=0;
			for(;Index1<Group.size() && Group[Index1].end()==Group[Index1].find(RawData[i].first); Index1++);			
			for(;Index2<Group.size() && Group[Index2].end()==Group[Index2].find(RawData[i].second); Index2++);
			if(Index1==Group.size()&&Index2==Group.size())
			{
				TmpSet.clear();
				TmpSet.insert(RawData[i].first);TmpSet.insert(RawData[i].second);
				Group.push_back(TmpSet);
			}
			else if(Index1!=Group.size()&&Index2==Group.size())
			{
				Group[Index1].insert(RawData[i].second);
			}
			else if(Index1==Group.size()&&Index2!=Group.size())
			{
				Group[Index2].insert(RawData[i].first);
			}
			else if(Index1!=Group.size()&&Index2!=Group.size()&&Index1>Index2)
			{
				for(set<int>::iterator it=Group[Index1].begin(); it!=Group[Index1].end(); it++)
				{
					Group[Index2].insert(*it);
				}
				Group.erase(Group.begin()+Index1);
			}
			else if(Index1!=Group.size()&&Index2!=Group.size()&&Index1<Index2)
			{
				for(set<int>::iterator it=Group[Index2].begin(); it!=Group[Index2].end(); it++)
				{
					Group[Index1].insert(*it);
				}
				Group.erase(Group.begin()+Index2);
			}
		}
		
		/*for(int i=0; i<Group.size(); i++)
		{
			for(set<int>::iterator it=Group[i].begin(); it!=Group[i].end(); it++)
			{
				cout<<*it<<' ';
			}
			cout<<endl;
		}
		cout<<endl;*/
		
		int TmpSize=0;
		for(int i=0 ;i<Group.size();i++)
		{
			if(Group[i].size()>TmpSize)
			{
				TmpSize=Group[i].size();
			}
		}
		
		cout<<TmpSize<<endl;
		
		pack--;
	}
		
	system("PAUSE");
	
	return 0;
}