#include <iostream>
#include "PathPlanning.h"

using namespace std;
int main()
{
    cout<<"Start Path Planning"<<endl;
    return 0;
}

class Node{
public:
    //构造函数，传入单元索引并计算单元中心坐标
    Node(H3Index _nodeIndex){
        nodeIndex = _nodeIndex;
        cellToLatLng(_nodeIndex, &nodeCentre);
    }
private:
    H3Index nodeIndex;//单元索引
    LatLng nodeCentre;//单元中心坐标
    Node* parentNode;//父节点
    double gCost = 0;
    double hCost = 0;
    double fCost = 0;
};

void pathPlanningByAStar(Node startNode, Node endNode){
    
}