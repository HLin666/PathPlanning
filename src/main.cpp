#include <iostream>
#include "PathPlanning.h"

using namespace std;
int main()
{
    cout<<"Start Path Planning"<<endl;
    // Node start(H3Index("8828308001fffff"));//如此强转可否达到效果？
    // Node goal(H3Index("882830802bfffff"));//没有效果
    Node start(613196569660882943);
    Node goal(613196569704923135);
    pathPlanningByAStar(start,goal);
    return 0;
}