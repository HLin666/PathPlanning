#pragma once
#include "include/h3api.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

class Node{
public:
    //构造函数，传入单元索引并计算单元中心坐标
    Node(H3Index _nodeIndex){
        nodeIndex = _nodeIndex;
        cellToLatLng(_nodeIndex, &nodeCentre);
    }
        H3Index getNodeIndex() const{ return nodeIndex; }
        LatLng getNodeCentre() const{ return nodeCentre; }
        Node* getParentNode() const{ return parentNode; }
    	int getG() { return g; }
		int getH() const{ return h; }
		int getF() const{ return f; }
        void setParentNode(Node* _parentNode){ parentNode = _parentNode; }
        void setG(){
            if(parentNode == nullptr) g = 0 + 1;//1待修改
            else g = parentNode->getG() + 1;//1待修改
        }
        void setH(Node goalNode){
            double lat1 = nodeCentre.lat;
		    double lon1 = nodeCentre.lng;
		    double lat2 = goalNode.getNodeCentre().lat;
		    double lon2 = goalNode.getNodeCentre().lng;
		    //按弧度计算的Haversine公式
		    double dlat = lat2 - lat1;
		    double dlon = lon2 - lon1;
		    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
		    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
		    double distance = 6371000.0 * c; // 地球半径m
		    h = distance;// 返回单位m
        }
        void setF(Node goalNode){
            setG();
			setH(goalNode);
			f = g+h;
        }
private:
    H3Index nodeIndex;//单元索引
    LatLng nodeCentre;//单元中心坐标
    Node* parentNode = nullptr;//父节点
    double g = 0;
    double h = 0;
    double f = 0;
};

vector<H3Index> callBack(Node* currentNode){
	vector<H3Index> path;
	while(currentNode!=NULL){
		path.push_back(currentNode->getNodeIndex());
		currentNode = currentNode->getParentNode();
	}
	return path;
}

void printPath(vector<H3Index> path){
	for(auto index : path){
		cout << index << endl;
	}
}

vector<Node*> getNeighborNodes(Node* currentNode){
	vector<Node*> neighborNodes;//存放返回值
    H3Index neighborIndex[7];//存放构造节点的七个索引
    gridDisk(currentNode->getNodeIndex(), 1, neighborIndex);
    for(auto index : neighborIndex){
        neighborNodes.push_back(new Node(index));
    }
	return neighborNodes;
}

//小根堆比较器
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->getF() > b->getF();
    }
};

void pathPlanningByAStar(Node startNode, Node goalNode){
    //准备数据容器
	unordered_map<H3Index, Node*> closeList; // 哈希表，查找更快。已选中的节点
    priority_queue<Node*, vector<Node*>, Compare> openList; // 优先队列，越小的f值越优先。待计算子节点
	vector<Node*> neighborNodes; // 存放邻居节点

    //A*起始准备
    closeList.insert({startNode.getNodeIndex(), &startNode});
	Node* currentNode = &startNode;
	currentNode->setF(goalNode);
	openList.push(currentNode);

    //开始搜索
    while(!openList.empty()){
		if(openList.top()==&startNode) openList.pop();//弹出指向起始节点的指针
		if (currentNode->getNodeIndex()==goalNode.getNodeIndex()){
			cout << "Find the goal!Cost:" <<currentNode->getG()<< endl;
			vector<H3Index> path = callBack(currentNode);
			printPath(path);
			break;
		}
		// 1.生成currentNode的6邻域neighborNodes,neighborNodes的父指针指向currentNode
		neighborNodes = getNeighborNodes(currentNode);
		// 2.将neighborNodes放入openList
		for(auto neighborNode : neighborNodes){
			// 3.判断neighborNode是否在closeList中，如果在，则跳过
			if(closeList.find(neighborNode->getNodeIndex())!= closeList.end())
				continue;
			neighborNode->setF(goalNode);
			openList.push(neighborNode);
			closeList.insert({neighborNode->getNodeIndex(), neighborNode});
		}
		// 4.取出openList中f值最小的节点，作为下一个currentNode
		currentNode = openList.top();
		openList.pop();
	}
}
