/*
 * MultiTree.cpp
 *
 *  Created on: 2017-7-4
 *      Author: Meng Qiu
 */
#include "qqStrFuns.h"
#include "qqTree.h"
#include <iostream>
using namespace std;
/*
MultiTree::MultiTree() {
	// TODO Auto-generated constructor stub
}
MultiTree::~MultiTree() {
	// TODO Auto-generated destructor stub
}
*/
TreeNode::TreeNode(TreeNode *fa,int mFa,string st,double fl,string sl,double tru):
		father(fa),mFather(mFa),str(st),flength(fl),slength(sl),trust(tru){}//基本构造函数，逐个赋值。

/*
TreeNode::TreeNode(string &tStr){//从括号和逗号分割的string中，读取一棵树
	TreeNode(tStr,1);
}
*/

TreeNode::TreeNode(string tStr,int isRoot){//做上面一样的事情，用于递归，isRoot=0表明不是root节点。
	if(tStr[tStr.length()-1]==';')tStr.pop_back();
	int is,le,ns,i;
	string::size_type sz;
	if(tStr[0]=='('){
		le=0;
		is=1;
		for(i=0;i<tStr.length();i++){
			if(tStr[i]=='(')le++;
			if(tStr[i]==')')le--;
			if(le==0)break;
			if(tStr[i]==','&&le==1){
				son.push_back(new TreeNode(tStr.substr(is,i-is),0));
				is=i+1;
			}
		}
		son.push_back(new TreeNode(tStr.substr(is,i-is),0));
		is=i+1;
		for(i=0;i<son.size();i++){
			son[i]->father=this;
			son[i]->mFather=i;
		}
		tStr=tStr.substr(is);
		if((is=tStr.find(":"))!=string::npos){
			str=tStr.substr(0,is);
			slength=tStr.substr(is+1);
			flength=stod(slength,&sz);
			trust=stod(str,&sz);
		}
		else{
			str=tStr;
			if(str.length()>0)trust=stod(str,&sz);
		}

	}
	else{
		if((is=tStr.find(":"))!=string::npos){
			str=tStr.substr(0,is);
			slength=tStr.substr(is+1);
			flength=stod(slength,&sz);
		}
		else{
			str=tStr;
		}

	}
	if(isRoot==1){
		if(str.size()==0){
			str="-1";
			trust=-1;
		}
		setLevel(0);
		calSize();
	}
}
/*
TreeNode::TreeNode(StarMap &smap, string &rootLeafStr){//利用星形图建立树。根叶子节点名称为rootLeafStr
	StarNode* sNode;
	sNode=smap.findLeaf(rootLeafStr);
	TreeNode(sNode);
}
TreeNode::TreeNode(StarNode* sNode){//利用星形图的某个叶子节点，作为根叶子建立树
	if(sNode->edge.size()!=1){
		cout<<"ERROR, sNode Must Be a Leaf Node, From TreeNode(StarNode* sNode)"<<endl;
		return;
	}
	father=nullptr;
	mFather=-1;
	slength="0";
	flength=0;
	str="";
	trust=-1;
	son.clear();
	TreeNode* trx;
//	trx=new TreeNode(this,0,);
//	son.push_back();

}
TreeNode::TreeNode(StarNode* sNode,int from){//从星形图的某个节点开始，from是father方向，建立子树。

}
*/

TreeNode::TreeNode(TreeNode *tr){//复制一棵树,建立树。
	int i;
	*this=*tr;
	father=nullptr;
	son.clear();
	for(i=0;i<(tr->son.size());i++){
		son.push_back(new TreeNode(tr->son[i]));
		son[i]->father=this;
		son[i]->mFather=i;
	}
}

TreeNode::TreeNode() {
	// TODO Auto-generated constructor stub
}

TreeNode::~TreeNode() {
	// TODO Auto-generated destructor stub
}


void TreeNode::setLevel(int le){//设定该节点的level为le，其子节点也跟着进行设定
	level=le;
	int i;
	for(i=0;i<son.size();i++)son[i]->setLevel(le+1);
}

void TreeNode::deleteSubTree(){//删除自本节点（包括本节点)以下的整棵树。如果father存在，其会丢失这个son。
	int i;
	for(i=0;i<son.size();i++)son[i]->deleteSubTree();
	(father->son).erase((father->son).begin()+mFather);
	for(i=mFather;i<(father->son).size();i++)father->son[i]->mFather=i;
	delete this;
}

string TreeNode::outputSubTree(){//以括号和逗号分割树输出的方式，输出整棵树。根节点没有Trust和Length。
	return outputSubTree(1);
}

string TreeNode::outputSubTree(int isRoot){//输出整棵树，isRoot为1表明是根，为0表明不是根。
	int i;
	string out="";
	if(son.size()>0){
		out="(";
		for(i=0;i<son.size();i++){
			out+=(son[i]->outputSubTree(0)+",");
		}
		out.pop_back();
		out+=")";
	}
	if(isRoot)return out+";";
	return out+str+":"+slength;
}

int TreeNode::calSize(){//计算本节点和各个子节点的TreeSize
	if(son.size()==0){
		subTreeSize=1;
		return 1;
	}
	int i;
	subTreeSize=0;
	for(i=0;i<son.size();i++)subTreeSize+=son[i]->calSize();
	return subTreeSize;
}

vector<TreeNode*> TreeNode::getNodes(){//获取所有节点
	int i,j;
	vector<TreeNode*> nodes,tmp;
	nodes.push_back(this);
	for(i=0;i<son.size();i++){
		tmp=son[i]->getNodes();
		for(j=0;j<tmp.size();j++)nodes.push_back(tmp[j]);
	}
	return nodes;
}

vector<TreeNode*> TreeNode::getLeafNodes(){//获取所有叶子节点
	int i,j;
	vector<TreeNode*> nodes,tmp;
	if(son.size()==0)nodes.push_back(this);
	else{
		for(i=0;i<son.size();i++){
			tmp=son[i]->getLeafNodes();
			for(j=0;j<tmp.size();j++)nodes.push_back(tmp[j]);
		}
	}
	return nodes;

}

vector<TreeNode*> TreeNode::getNotLeafNodes(){//获取所有非叶子节点
	int i,j;
	vector<TreeNode*> nodes,tmp;
	if(son.size()>0){
		nodes.push_back(this);
		for(i=0;i<son.size();i++){
			tmp=son[i]->getNotLeafNodes();
			for(j=0;j<tmp.size();j++)nodes.push_back(tmp[j]);
		}
	}
	return nodes;
}

void TreeNode::setID(){//给节点编号，总根为0号。编号顺序按照getNodes顺序
	vector<TreeNode*> nodes=getNodes();
	int i;
	for(i=0;i<nodes.size();i++)nodes[i]->id=i;
	return;
}

TreeNode* TreeNode::setRoot(){//以本节点为根叶重新画树，返回新的根。树结构完全更改。
	int i;
	if(father==nullptr)return this;
	if(father->father==nullptr&&father->son.size()==2)return father;
	(findRoot())->deleteFakeNode();
	TreeNode * nr;//新建一个伪根,是无父两子的。
	nr=new TreeNode(nullptr,-1,"-1",0,"0",-1);
	nr->son.push_back(this);
	father->son[mFather]=nr;
	father->changeFather(mFather);
//	cout<<father->outputSubTree(0)<<endl;
	father=nr;
	mFather=0;
	return nr;
}

TreeNode* TreeNode::copyTree(){//以当前节点为根，复制一颗一样的树，多占用一倍内存。
	TreeNode * ntr=new TreeNode();
	int i;
	*ntr=*this;
	ntr->father=nullptr;
	ntr->son.clear();
	for(i=0;i<son.size();i++){
		ntr->son.push_back(son[i]->copyTree());
		ntr->son[i]->father=ntr;
		ntr->son[i]->mFather=i;
	}
	return ntr;
}

TreeNode* TreeNode::findRoot(){//返回当前节点所属的最高root。最高root没有father。
	if(father==nullptr)return this;
	else return father->findRoot();
}

TreeNode* TreeNode::findNode(string fstr){//在当前节点的和其子节点中寻找str是fstr的Node;
//	cout<<str<<" "<<fstr<<endl;
	if(str==fstr)return this;
	int i;
	TreeNode* found;
	for(i=0;i<son.size();i++){
		found=son[i]->findNode(fstr);
		if(found!=nullptr)return found;
	}
	return nullptr;
}

TreeNode* TreeNode::findNode(int fid){//在当前节点和其子节点中寻找id是fid的Node;
	if(id==fid)return this;
	int i;
	TreeNode* found;
	for(i=0;i<son.size();i++){
		found=son[i]->findNode(fid);
		if(found!=nullptr)return found;
	}
	return nullptr;
}

void TreeNode::deleteFakeNode(){//删除伪节点(只有两子，且其中至少一个不是叶子，无父节点 和 只有一子一父的节点 和 只有一子无父节点)
	TreeNode* temp;
	int trueSon=-1,i;
	//先考虑两子无父
	if(father==nullptr&&son.size()==2){
		if(son[0]->flength==0)trueSon=0;
		else if(son[1]->flength==0)trueSon=1;
		else if(son[0]->son.size()>0)trueSon=0;
		else if(son[1]->son.size()>0)trueSon=1;
	}
	if(trueSon!=-1){//本节点就是伪节点
		//将trueSon作为新的父节点，收入另一个子节点。
		son[trueSon]->son.push_back(son[1-trueSon]);
		son[1-trueSon]->mFather=son[trueSon]->son.size()-1;
		//将trueSon的长度合并到另一个子节点。
		son[1-trueSon]->flength+=son[trueSon]->flength;
		son[1-trueSon]->slength=to_string(son[1-trueSon]->flength);
		son[trueSon]->flength=0;
		son[trueSon]->slength="0";
		son[trueSon]->father=nullptr;
		son[trueSon]->mFather=-1;
		//把trueSon复制过来，然后删了
		temp=son[trueSon];
		copyValues(temp);
		for(i=0;i<temp->son.size();i++)temp->son[i]->father=this;
		delete temp;
	}
	//再考虑一子无父
	if(father==nullptr&&son.size()==1){
		son[0]->father=nullptr;
		son[0]->mFather=-1;
		temp=son[0];
		copyValues(temp);
		father=nullptr;
		for(i=0;i<temp->son.size();i++)temp->son[i]->father=this;
		delete temp;
	}
	//再考虑一子一父
	if(father!=nullptr&&son.size()==1){
		son[0]->father=father;
		son[0]->mFather=mFather;
		son[0]->flength+=flength;
		son[0]->slength=to_string(son[0]->flength);
		temp=son[0];
		copyValues(temp);
		for(i=0;i<temp->son.size();i++)temp->son[i]->father=this;
		delete temp;
	}
	for(i=0;i<son.size();i++)son[i]->deleteFakeNode();
}

void TreeNode::changeFather(int sToF){//将第sToF个son转换为新的father。注意，后面所有的节点都会跟着更改。（用于setRoot函数）
	//考虑总父节点。
	int i;
	if(father==nullptr){
		son[sToF]->son.push_back(this);
		father=son[sToF];
		mFather=father->son.size()-1;
		flength=son[sToF]->flength;
		slength=son[sToF]->slength;
		son.erase(son.begin()+sToF);
		for(i=sToF;i<son.size();i++){
			son[i]->mFather=i;
		}
	}
	else{
		father->changeFather(mFather);
		son[sToF]->son.push_back(this);
		father=son[sToF];
		mFather=father->son.size()-1;
		flength=son[sToF]->flength;
		slength=son[sToF]->slength;
		son.erase(son.begin()+sToF);
		for(i=sToF;i<son.size();i++){
			son[i]->mFather=i;
		}

	}
}

void TreeNode::copyValues(TreeNode* tr){//内容复制，只复制值。
	father=tr->father; //父节点
	mFather=tr->mFather;//存储该节点是其父节点的第几个son。方便查找。
	son=tr->son; //子节点们
	str=tr->str; //对于叶子节点，是物种名。也可以是编号等其他名称。这里非叶子节点用于存储trust的字符串
	flength=tr->flength; //存储该节点到其父节点的距离。
	slength=tr->slength;//length的字符串
	level=tr->level;//level为此节点到根节点的级别差
	trust=tr->trust; //存储该节点的可信度。
	subTreeSize=tr->subTreeSize; //存储以该节点为根节点的树的叶子节点数量
	id=tr->id;//存储节点编号，可以区分每个节点。

	//以下三个变量用于存储将来或许会用到的其他可能的变量。
	intData=tr->intData;
	strData=tr->strData;
	doubleData=tr->doubleData;
}

