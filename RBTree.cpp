#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/**
*author:SrV-330 
*title:RBTree
*time:2019-03-26 22:12:28
*ps:can not typing Chinese??????
*/ 
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
		
	fixup(&p);
	
	return n;
	
}

void leftRotate(ptn* curr){
	
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
void rightRotate(tn** curr){
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
void fixup(ptn* p){
	if(!p) return;
	if(!GETP((*p))){
		(*p)->color=BLACK;	//*p is root 
	}else if(ISBLACK(GETP((*p)))){
		
		return; //parent node is black 
	}else if(ISRED(GETP((*p)))&&ISRED(GETU((*p)))){
		
		GETP((*p))->color=BLACK; // parent node is red
		GETU((*p))->color=BLACK; // uncle node is red
		GETGP((*p))->color=RED;  // grandpa node is black
		 fixup(GETGP((*p)));	 // *p is left or right child
	}else if(ISRED(GETP((*p)))&&(ISBLACK(GETU((*p)))||ISN(GETU((*p))))
				&&ISRC(GETP(*p),(*p))&&ISLC(GETGP((*p)),GETP((*p)))){ 
		leftRotate((*p));		 //*p is rgiht child
		(*p)=(*p)->leftChild;	 // parent node is red
		fixup(p);				 // uncle node is black	
	}else if(ISRED(GETP((*p)))&&(ISBLACK(GETU((*p)))||ISN(GETU((*p))))
				&&ISLC(GETP(*p),(*p))&&ISRC(GETGP((*p)),GETP((*p)))){
		rightRotate((*p));
		(*p)=(*p)->rightChild;
		fixup(p);
	
	}else if(ISRED(GETP((*p)))&&(ISBLACK(GETU((*p)))||ISN(GETU((*p))))
				&&ISLC(GETP(*p),(*p))&&ISLC(GETGP((*p)),GETP((*p)))){
		rightRotate(GETGP(*p));	 //*p is left child
		(*p)->color=BLACK;		 // parent node is red
		(*p)->leftChild->color=RED;	 // uncle node is black
	}else if(ISRED(GETP((*p)))&&(ISBLACK(GETU((*p)))||ISN(GETU((*p))))
				&&ISRC(GETP(*p),(*p))&&ISRC(GETGP((*p)),GETP((*p)))){
		leftRotate(GETGP((*p)));
		(*p)->color=BLACK;
		(*p)->rightChild->color=RED;
	}else{
		return;
	}
	
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
