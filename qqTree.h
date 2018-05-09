/*
 * qqTreeAndStarMap.h
 *
 *  Created on: 2017-7-4
 *      Author: meng
 */

#ifndef QQTREE_H_
#define QQTREE_H_
#include <string>
#include <vector>

using namespace std;

class StarEdge;
class StarNode;
class StarMap;


//TreeNode定义了多分支树的一个节点。
class TreeNode {
public:
	TreeNode* father=nullptr; //父节点
	int mFather=-1;//存储该节点是其父节点的第几个son。方便查找。
	vector<TreeNode*> son; //子节点们
	string str="-1"; //对于叶子节点，是物种名。也可以是编号等其他名称。这里非叶子节点用于存储trust的字符串
	double flength=0; //存储该节点到其父节点的距离。
	string slength="0";//length的字符串
	int level=0;//level为此节点到根节点的级别差
	double trust=-1; //存储该节点的可信度。
	int subTreeSize=-1; //存储以该节点为根节点的树的叶子节点数量
	int id=0;//存储节点编号，可以区分每个节点。

	//以下三个变量用于存储将来或许会用到的其他可能的变量。
	int intData=0;
	string strData="";
	double doubleData=0;


	//定义成员函数。
	void setLevel(int le);//设定该节点的level为le，其子节点也跟着进行设定
	void deleteSubTree();//删除自本节点（包括本节点)以下的整棵树。如果father存在，其会丢失这个son。
	string outputSubTree();//以括号和逗号分割树输出的方式，输出整棵树。根节点没有Trust和Length。
	string outputSubTree(int isRoot);//输出整棵树，isRoot为1表明是根，为0表明不是根。
	int calSize();//计算本节点和各个子节点的TreeSize
	vector<TreeNode*> getNodes();//获取所有节点
	vector<TreeNode*> getLeafNodes();//获取所有叶子节点
	vector<TreeNode*> getNotLeafNodes();//获取所有非叶子节点
	void setID();//给节点编号，总根为0号。编号顺序按照getNodes顺序
	TreeNode* setRoot();//以本节点为根叶重新画树，返回新的根。注意，老树不会被更改，最好手动删掉
	TreeNode* copyTree();//复制一颗一样的树，多占用一倍内存。
	TreeNode* findRoot();//返回当前节点所属的最高root。最高root没有father。
	TreeNode* findNode(string fstr);//在当前节点的和其子节点中寻找str是fstr的Node;
	TreeNode* findNode(int fid);//在当前节点和其子节点中寻找id是fid的Node;
	void copyValues(TreeNode* tr);//内容复制，只复制值。
	void deleteFakeNode();//删除伪节点(只有两子，无父，无名节点和只有一子一父的无名节点)
	void changeFather(int sToF);//将第sToF个son转换为新的father。注意，后面所有的节点都会跟着更改。（用于setRoot函数）
	TreeNode();
	TreeNode(TreeNode *fa,int mFa,string st,double fl,string sl,double tru);//基本构造函数，逐个赋值。
//	TreeNode(string &tStr);//从括号和逗号分割的string中，读取一棵树
	TreeNode(string tStr,int isRoot);//做上面一样的事情，用于递归，isRoot=0表明不是root节点。
//	TreeNode(StarMap &smap, string &rootLeafStr);//利用星形图建立树。根叶子节点名称为rootLeafStr
//	TreeNode(StarNode* sNode);//利用星形图的某个节点（作为根叶子/第一叶子）建立树
//	TreeNode(StarNode* sNode,int from);//从星形图的某个节点开始，from是father方向，建立子树。
	TreeNode(TreeNode *tr);//复制一棵树
	virtual ~TreeNode();
};
//MultiTree定义了一个多分支树
//class MultiTree {
//public:
//	vector<TreeNode*> nodes;//用于存储所有的节点。0号节点是根节点
//
//	vector<TreeNode*> getLeafNodes();
//	vector<TreeNode*> getNotLeafNodes();
//	string outputTree();//输出到括号和逗号分割的string，根节点没有TRUST和LENGTH
//	void calLevel();//计算节点的level
//	MultiTree(string treeStr);//读取括号分隔的字符串建立树
//	MultiTree(StarMap smap,string rootLeafStr);//利用星形图建立树。根叶子节点名称为rootLeafStr
//	MultiTree(StarNode* sNode);//利用星形图的某个节点（作为根叶子/第一叶子）建立树
//	MultiTree(TreeNode* tr);//用已有的一个节点，构造一棵树。（即为以此节点为根的子树）
//	MultiTree();
//	virtual ~MultiTree();
//};
/*
//下面的类表示星形图的一个节点
class StarNode{
public:
    vector<StarEdge*> edge;
    vector<int> mEdge;
    string str="";
    double trust=0;
    int id=0;

	//以下三个变量用于存储将来或许会用到的其他可能的变量。
	int intData=0;
	string strData="";
	double doubleData=0;

    void setEdgeNum(int n);
    StarNode();
    virtual ~StarNode();
};
class StarEdge{
public:
    vector<StarNode*> node;
    int mNode[2];
    string slength="";
    double length=0;
    int id=0;
    StarEdge();
    virtual ~StarEdge();
};
class StarMap{
public:
	vector<StarNode*> nodes;
	vector<StarEdge*> edges;

    StarNode* findLeaf(string &leafStr);//寻找名为leafStr的叶子节点并返回。若有多个则返回最近的


	StarMap();
//	StarMap(MultiTree mtr);//利用多分支树建立星形图
	StarMap(TreeNode *tr);//利用多分支树的某个节点建立星形图，其nodes的第0个元素就是这个节点。
	virtual ~StarMap();
};

*/

#endif /* QQTREE_H_ */

