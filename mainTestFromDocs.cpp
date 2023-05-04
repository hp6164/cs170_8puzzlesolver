#include <iostream>
#include <vector>
#include "src\game.h"
#include "src\node.h"
// #include <cmath>

using namespace std;

void checkInput(int x);
void chooseSearch();
Game* g;

int main()
{
    int x = 0;
    do
    {
        cout<<endl;
        cout<<"--------------------"<<endl;
        cout<<"\tMenu\t"<<endl;
        cout<<"--------------------"<<endl;
        cout<<"1. Trivial"<<endl;
        cout<<"2. Very Ez"<<endl;
        cout<<"3. Ez"<<endl;
        cout<<"4. Doable"<<endl;
        cout<<"5. Oh Boy"<<endl;
        cout<<"6. Not Possible"<<endl;
        cout<<"7. Custom"<<endl;
        cout<<"10. exit"<<endl;
        cin>>x;
        checkInput(x);

    } while(x != 10);

    return 0;
}

void checkInput(int in)
{
    switch (in)
    {
    case 1:
        /* code */
        g = new Game({{1,2,3},{4,5,6},{7,8,0}});
        chooseSearch();
        break;
    case 2:
        /* code */
        g = new Game({{1,2,3},{4,5,6},{7,0,8}});
        chooseSearch();
        break;
    case 3:
        /* code */
        g = new Game({{1,2,0},{4,5,3},{7,8,6}});
        chooseSearch();
        break;
    case 4:
        /* code */
        g = new Game({{0,1,2},{4,5,3},{7,8,6}});
        chooseSearch();
        break;
    case 5:
        /* code */
        g = new Game({{8,7,1},{6,0,2},{5,4,3}});
        chooseSearch();
        break;
    case 6:
        /* code */
        g = new Game({{1,2,3},{4,5,6},{8,7,0}});
        chooseSearch();
        break;
    case 7:
        /* code */
       cout<<"custom not yet implmented"<<endl;
       cout<<"";
        break;
    case 10:
        /* code */
       cout<<"exiting"<<endl;
        break;
    
    default:
        cout<<"Invalid Input"<<endl;
        break;
    }
}

void chooseSearch()
{
    int x;
        cout<<endl;
        cout<<"--------------------"<<endl;
        cout<<"\tOptions\t"<<endl;
        cout<<"--------------------"<<endl;
        cout<<"1. UCS aka Just BFS"<<endl;
        cout<<"2. A* Tile"<<endl;
        cout<<"3. A* Euclids"<<endl;
        cout<<"10. exit"<<endl;
        cin>>x;

    switch (x)
    {
    case 1:
        g->search_UCS();
        break;
    case 2:
        g->search_Misplace();
        break;
    case 3:
        g->search_Euclidean();
        break;
    
    case 10:
        cout<<"Canceling..."<<endl;
        break;
    
    default:
        cout<<"Invalid Input"<<endl;
        break;
    }
}