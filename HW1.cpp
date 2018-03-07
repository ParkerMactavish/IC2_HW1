//complie with MinGW

#include <iostream>//for standard input out put
#include <fstream>//for file input
#include <vector>//for STL vector
#include <cstdlib>//for system command
#include <set>//for STL set

using namespace std;

int main()
{
	fstream fs;//file opening
	fs.open("input.txt", ios::in);
	
	int pack;//pack stands for how many set of data will be inputted
	fs>>pack;
	while(pack>0)
	{
		int NumOfPeo, NumOfPair;//NumOfPeo stands for the number of people, and NumOfPair stands for the number of pairs of data
		fs>>NumOfPeo>>NumOfPair;	
		
		vector < pair<int, int> > RawData(0);//declare a vector of pairs to load the data inputted
		for(int i=0; i<NumOfPair; i++)//get the data from the file
		{
			int TmpA, TmpB;
			fs>>TmpA>>TmpB;
			RawData.push_back(make_pair(TmpA, TmpB));
		}
		
		//test to see if RawData is correct
		/*for(int i=0; i<RawData.size(); i++)
		{
			cout<<RawData[i].first<<" "<<RawData[i].second<<endl;
		}
		cout<<endl;*/
		
		vector < set<int>> Group(0);//declare a vector of set to load all the group, a set is a group
		set<int> TmpSet;//declare a temporary set to contain the first pair in the data
		TmpSet.insert(RawData[0].first);TmpSet.insert(RawData[0].second);//insert the first pair of data into TmpSet
		Group.push_back(TmpSet);//push the TmpSet into Group as the very first group
		
		
		for(int i=1; i<NumOfPair; i++)//Then get the following pairs into grouping stage
		{
			int Index1=0, Index2=0;//declare two Index to find the group that the pair.first and pair.second are in
			for(;Index1<Group.size() && Group[Index1].end()==Group[Index1].find(RawData[i].first); Index1++);//find the pair.first's group			
			for(;Index2<Group.size() && Group[Index2].end()==Group[Index2].find(RawData[i].second); Index2++);//find the pair.second's group
			if(Index1==Group.size()&&Index2==Group.size())//first case: if the two in the pair are both not in any group
			{
				TmpSet.clear();
				TmpSet.insert(RawData[i].first);TmpSet.insert(RawData[i].second);//group them together
				Group.push_back(TmpSet);//push the group into Group
			}
			else if(Index1!=Group.size()&&Index2==Group.size())//second case: if first is in one of the groups, and second is alone
			{
				Group[Index1].insert(RawData[i].second);//put second into the group
			}
			else if(Index1==Group.size()&&Index2!=Group.size())//third case: if second is in one of the groups, and first is alone
			{
				Group[Index2].insert(RawData[i].first);//put first into the group
			}
			else if(Index1!=Group.size()&&Index2!=Group.size()&&Index1>Index2)//fourth case: if first and second are in groups but not in the same group and the index of the group where second is in is smaller
			{
				for(set<int>::iterator it=Group[Index1].begin(); it!=Group[Index1].end(); it++)//move the elements in the group of first to the group of second
				{
					Group[Index2].insert(*it);
				}
				Group.erase(Group.begin()+Index1);//erase the group of first
			}
			else if(Index1!=Group.size()&&Index2!=Group.size()&&Index1<Index2)//fifth case: if first and second are in groups but not in the same group and the index of the group where first is in is smaller
			{
				for(set<int>::iterator it=Group[Index2].begin(); it!=Group[Index2].end(); it++)//move the elements in the group of second to the group of first
				{
					Group[Index1].insert(*it);
				}
				Group.erase(Group.begin()+Index2);//erase the group of second
			}
		}
		
		//test if the goruping stage is correct
		/*for(int i=0; i<Group.size(); i++)
		{
			for(set<int>::iterator it=Group[i].begin(); it!=Group[i].end(); it++)
			{
				cout<<*it<<' ';
			}
			cout<<endl;
		}
		cout<<endl;*/
		
		
		int TmpSize=0;//declare a TmpSize to store the number of elements of the biggest group
		for(int i=0 ;i<Group.size();i++)//go through all of the groups
		{
			if(Group[i].size()>TmpSize)
			{
				TmpSize=Group[i].size();
			}
		}
		
		cout<<TmpSize<<endl;//print the biggest size
		
		pack--;
	}
		
	system("PAUSE");
	
	return 0;
}