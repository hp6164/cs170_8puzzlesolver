#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> numberbank;
vector<vector<int>> table;
vector<int> row;

void input(int &rows);
bool Check0andNoDup(int& rows);
bool findnum(int n);

int main()
{
    int option = 0, temp = 0;

    //Puzzle solver
    int solve = 8;
    int rows = sqrt((solve + 1));
    for(int i = 0; i <= solve; i++)
    {
        numberbank.push_back(i);
    } 

    cout << "Welcome to EHP (Edgar,Harsh, Pranoy) "<< solve << " puzzle solver." << endl;
    cout << "Type '1' to use a defualt puzzle, or '2' to enter your own puzzle." << endl;
    cin >> option;
    while(option < 1 || option > 2)
    {
        cout << "Invalid, Please Try Again!" << endl;
        cout << "Type '1' to use a defualt puzzle, or '2' to enter your own puzzle." << endl;
        cin >> option;
    }
    switch (option)
    {
        case 1:
            break;
        
        case 2: cout << "Enter your puzzle, use a zero to represent the blank" << endl;
                for (int i = 0; i < rows; i++)
                {
                   cout << "Enter row " << i << " , use space or tabs between numbers:  "; 
                   input(rows);
                }
                if(!Check0andNoDup(rows))
                {
                    cout << "Error!" << endl;
                }
                else{
                    cout << "Passed" << endl;
                }
            break;
    }

    return 0;

}   

void input(int& rows)
{
    int temp = 0;
    for(int j = 0; j < rows; j++)
    {
        cin >> temp;
        row.push_back(temp);
    }
    table.push_back(row);
    row.clear();
}

bool Check0andNoDup(int& rows)
{
    bool b = false;
    bool temp = true;
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            if(table[i][j] == 0 )
            {
                b = true;
            }
            temp = findnum(table[i][j]);
            if (temp == false)
            {
                b = false;
                return b;
            }
        }
    }
    return b;
}

bool findnum(int n)
{
    int indexfound;
    bool found = false;
    for(int i = 0; i < numberbank.size(); i++)
    {
        if(numberbank[i] == n)
        {
            indexfound = i;
            found = true;
            break;   
        }
    }
    if(found == true)
    {
        numberbank.erase(numberbank.begin()+indexfound);
        return found;
    }
    return found;
}

