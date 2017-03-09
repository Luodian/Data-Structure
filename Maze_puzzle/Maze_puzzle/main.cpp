//
//  main.cpp
//  Maze_puzzle
//
//  Created by 李博 on 2016/11/5.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <functional>

using namespace std;
#define mem(a,x) memset(a,x,sizeof(a))

const int dr[] = {1,-1,0,1, -1,0,1,0};
const int dc[] = {1,-1,1,-1, 0,-1,0,-1};
char maze[50][50];
bool vis[50][50];
int r,c;
int minn = 1<<29;
bool Finded;
struct coord
{
    int x;
    int y;
    coord(int a = 0,int b = 0)
    {
        x = a;
        y = b;
    }
}path[200],minimal_path[200];
int LengthOfPath = 0;
int LengthOfMinimal = 0;
int count_path = 0;

void init()
{
    mem(maze,0);
    mem(vis,0);
    Finded = 0;
    count_path = 0;
    LengthOfMinimal = 0;
    LengthOfPath = 0;
    cout<<"Please Input the scale of the maze: ";
    cin>>r>>c;
    
}
void generator()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dis(1,2);
    auto dice = std::bind(dis,generator);
    for (int i = 0 ; i < r; ++i)
    {
        for (int j = 0 ; j  < c; ++j)
        {
            if(dice() == 1)
            {
                maze[i][j] = '*';
            }
            else
            {
                maze[i][j] = '@';
            }
        }
    }
}

void ShowPuzzle()
{
    for (int i = 0 ; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cout<<maze[i][j]<<"  ";
        }
        cout<<"\n";
    }
}

void Print_path(struct coord *path,int n)
{
    cout<<"( 0, 0 )";
    for (int i = 0; i < n; ++i)
    {
        cout<<"( "<<path[i].x<<" , "<<path[i].y<<" )";
    }
    cout<<"\n";
}

void decopy(struct coord *v1,struct coord *v2)
{
    for (int i = 0; i < LengthOfPath; ++i)
    {
        v1[i] = v2[i];
    }
    LengthOfMinimal = LengthOfPath;
}
void Find_Minimal(int x,int y,int step)
{
    int tx,ty;
    coord newcoord;
    if (x == r - 1 && y == c - 1)
    {
        minn = min(step,minn);
        Finded = 1;
        count_path ++;
        Print_path(path,step);
        if(minn == step)
        {
            LengthOfPath = minn;
            decopy(minimal_path,path);
        }
        return;
    }
    for (int i = 0; i < 8; ++i)
    {
        tx = x + dc[i];
        ty = y + dr[i];
        if (tx < 0 || tx >= r || ty < 0 || ty >= c)
        {
            continue;
        }
        if (maze[tx][ty] == '*' && vis[tx][ty] == 0)
        {
            vis[tx][ty] = 1;
            newcoord.x = tx;
            newcoord.y = ty;
            path[step] = newcoord;
            Find_Minimal(tx,ty,step+1);
            vis[tx][ty] = 0;
        }
    }
}


int main(int argc, const char * argv[])
{
    init();
    cout<<"\nThe random maze is: \n\n";
    generator();
    ShowPuzzle();
    cout<<"\n";
    Find_Minimal(0,0,0);
    cout<<"\n";
    cout<<"We have totaly found "<<count_path<<" paths\n";
    cout<<"\n";
    if(Finded)
    {
        cout<<"The minimal distance is: ";
        cout<<minn<<"\n";
        cout<<"The minial path is: ";
        Print_path(minimal_path,minn);
    }
}
