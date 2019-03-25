#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef	struct TreeNode{
	struct TreeNode* parent;
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
	int value;
	int color;
}tn,*ptn;
#define RED 1
#define BLACK 2
#define null NULL
#define nil NULL
#define ISRED(p) (ISN(p)?false:p->color==1?true:false)
#define ISBLACK(p) (ISN(p)?false:p->color==2?true:false)
#define ISRC(p,c) (ISN(p)?false:p->rightChild==c?true:false)
#define ISLC(p,c) (ISN(p)?false:p->leftChild==c?true:false)
#define ISN(p) (p==NULL?true:false)
#define GETP(p) (p==NULL?NULL:p->parent)
#define GETL(p) (p==NULL?NULL:p->leftChild)
#define GETR(p) (p==NULL?NULL:p->rightChild)
#define GETGP(p) (ISN(p)||ISN(p->parent)?NULL:p->parent->parent)
#define GETU(p) (ISN(GETGP(p))?NULL:ISLC(GETGP(p)->leftChild,p)?GETGP(p)->rightChild:GETGP(p)->rightChild)
void printTreeNode(tn* root,int deep);
ptn createTreeNode(int value){
	ptn n;
	n=(ptn)malloc(sizeof(tn));
			
	n->parent=NULL;
	n->leftChild=NULL;
	n->rightChild=NULL;
	n->value=value;
	n->color=RED;
	return n;
}
ptn insertTreeNode(ptn* p){
	ptn move=p==NULL?NULL:(*p);
	ptn movep=p==NULL?NULL:(*p);
	ptn n;
	int value=0;
	for(fflush(stdin);scanf("%d",&value)!=1;fflush(stdin),value=0);
	
	if(value==-1){
		
		return NULL;
	}
		
	while(move!=NULL){
		
		movep=GETP(move);
		if(move->value<value){
			movep=move;
			move=move->leftChild;
			
		}else{
			movep=move;
			move=move->rightChild;
			
		}
	}
	
	n=createTreeNode(value);
			
	n->parent=movep;
	
	if(movep){
		
		if(movep->value<value){
			movep->rightChild=n;
			
		}else{
			movep->leftChild=n;
		}
	}
	return n;
	
}

void rightRotate(ptn* curr){
	
	if(ISN((*curr))||!GETR((*curr))) return;
	printf("a");
	ptn newNode=(*curr)->rightChild;
	ptn newNodeLeftChild=newNode->leftChild;
	
	
	if(newNodeLeftChild!=NULL){
		newNodeLeftChild->parent=(*curr);
	}
	newNode->parent=(*curr)->parent;
	(*curr)->rightChild=newNodeLeftChild;
	(*curr)->parent=newNode;
	newNode->leftChild=(*curr);
	(*curr)=newNode;
	
	
	
}
void leftRotate(tn** curr){
	if((*curr)==NULL||(*curr)->leftChild==NULL) return;
	tn* newNode=(*curr)->leftChild;
	tn* newNodeRightChild=newNode->rightChild;
	if(newNodeRightChild!=NULL){
		newNodeRightChild->parent=(*curr);
	}
	newNode->parent=(*curr)->parent;
	(*curr)->leftChild=newNodeRightChild;
	(*curr)->parent=newNode;
	newNode->rightChild=(*curr);
	(*curr)=newNode;
}



void dropTreeNode(ptn n){
	
	if(!n) return;
	dropTreeNode(n->leftChild);
	dropTreeNode(n->rightChild);
	free(n);
}

void printTreeNode(tn* root,int deep){
	
	
	if(root==NULL){
		
		return;
	}
	deep++;
	
	printTreeNode(root->rightChild,deep);
	
	
	for(int i=0;i<deep;i++){
		
		printf("  ");
	}
	
	printf("%d\n",root->value);	
	
	printTreeNode(root->leftChild,deep);
}
main(){
	
	ptn* proot=NULL;
	ptn root=NULL;
	ptn n;
	n=insertTreeNode(proot);
	root=ISN(n)?NULL:n;
	proot=ISN(n)?NULL:&n;
	while(n!=NULL){
		n=insertTreeNode(proot);
	}
	printTreeNode(root,0);
	
	rightRotate(proot);
	
	printTreeNode(root,0);
	
	leftRotate(proot);
	
	printTreeNode(root,0);
	dropTreeNode(root);
	
	
	
	
}
