#include <iostream>
#include <string>
#include <fstream>

#define MAXVALUE 32767

using namespace std;
typedef struct {
	char ch;
	int left, right;
	int parent;
	int weight;
 }huffmanNode,*huffmanTree;

typedef char** huffmanCode;

void CountFile(string fileName, int *counter) {
	
	ifstream ifs;
	ifs.open(fileName, ios::in);
	char ch;
	while (ifs && ifs.get(ch)) {
		if (ch >= 'a' && ch <= 'z') {
			int i = (int)ch - (int)'a';
			counter[i]++;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			int i = (int)ch - (int)'A';
			counter[i]++;
		}
	}
//��⣺
	for (int i = 0; i < 26; i++)
		cout << (char)((int)'a' + i) << " " << counter[i] << endl;
}

void InitHuffmanTree(huffmanTree& Tree,int *counter) {
	Tree = (huffmanNode*)malloc(52 * sizeof(huffmanNode));
	for (int i = 1; i < 52; i++) {
		Tree[i].parent = -1;
		Tree[i].left = Tree[i].right = -1;
		Tree[i].ch = NULL;
		Tree[i].weight = 0;
	}
	for (int i = 1; i <= 26; i++) {
		Tree[i].ch = (char)((int)'a' + i-1);
		Tree[i].weight = counter[i-1];
	}

//��⣺
//	for (int i = 0; i < 52; i++) {
//		cout << i << " " << Tree[i].ch << " " << Tree[i].weight <<" "<< Tree[i].left << " " << Tree[i].right << endl;
//	}
}

void CreateHuffmanTree(huffmanTree& Tree) {
	//�ҵ�parent=-1����С�����ڵ� 
	int min1, min2;
	int lnum, rnum;
	for (int i = 27; i < 52; i++) {
		min1 = min2 = MAXVALUE;
		lnum = rnum = -1;
		for (int j = 1; j <= i-1; j++) {
			if (Tree[j].weight < min1 && Tree[j].parent == -1)
			{
				min2 = min1;
				rnum = lnum;						//������min1С�ģ���min1��ֵ�͸��ڶ�С��min2���±�Ҳ����
				min1 = Tree[j].weight;
				lnum = j;						//Ȼ����С�ĸ�min1���±�ͬ��
			}
			else if (Tree[j].weight < min2 && Tree[j].parent == -1)		//�жϵڶ�С
			{
				min2 = Tree[j].weight;
				rnum = j;
			}
		}
		Tree[lnum].parent = Tree[rnum].parent = i;
		Tree[i].left = lnum;
		Tree[i].right = rnum;
		Tree[i].weight = Tree[lnum].weight + Tree[rnum].weight;
	}

//��⣺
	cout << "NUM" << "\t" << "CHAR" << "\t" << "PARENT" << "\t" << "WEIGHT" << "\t" << "LEFT" << "\t" << "RIGHT" << endl;

	for (int i = 1; i < 52; i++) {
		cout << i << "\t" << Tree[i].ch << "\t" << Tree[i].parent<<"\t" << Tree[i].weight << "\t" << Tree[i].left << "\t" << Tree[i].right << endl;
	}
}

void HuffmanTreeCode(huffmanCode& hc, huffmanTree Tree) {
	hc = (huffmanCode)malloc(sizeof(huffmanCode) * 26 + 1);
	cout << "HuffmanTreeCode" << endl;

	for (int i = 1; i <=26; i++) {
		char *code = (char*)malloc(sizeof(char)*26);
		code[0] = '\0';

		int num = 1;
		for (int k = i;Tree[k].parent != -1; num++) {
			if (Tree[Tree[k].parent].left == k) code[num] = '0';
			else code[num] = '1';
			k = Tree[k].parent;
		}
		num--;

		hc[i] = (char*)malloc(sizeof(char* )*num);
		//�ߵ�
		for (int k = 0; k <= num; k++) {
			hc[i][k] = code[num-k];
		}
		free(code);
	}
	for (int i = 1; i <= 26; i++)
	{
		printf("%c:\t", Tree[i].ch);
		printf("%s\n", hc[i]);
	}
			
}

void OutFile(string ifileName, string ofileName, huffmanCode hc) {
	ifstream ifs;
	ifs.open(ifileName, ios::in);
	ofstream ofs;
	ofs.open(ofileName, ios::out);

	char ch;
	while (ifs && ifs.get(ch)) {
		if (ch >= 'a' && ch <= 'z') {
			ofs << hc[(int)(ch - 'a') + 1];
		}
		else if (ch >= 'A' && ch <= 'Z') {
			ofs << hc[(int)(ch - 'A') + 1];
		}
	}
}

int main() {
//���룺
	//�����ļ�
	string fileName;
	cout << "enter the name of input-file : ";
	cin >> fileName;

	//�ļ��ַ�ͳ��
	int counter[26] = {0};
	CountFile(fileName,counter);

	huffmanTree Tree;
	huffmanCode hc;

	//��Ӧ�ַ�������������У����ڳ�ʼ�����������ڵ�
	InitHuffmanTree(Tree, counter);

	//������������
	CreateHuffmanTree(Tree);

	//�γ��ַ������Ʊ��룬�洢���ֵ���
	HuffmanTreeCode(hc, Tree);

	//�ٴα����ļ������ַ�ӳ��Ϊ��Ӧ�Ķ����Ʊ���
	string outfileName;
	cout << "enter the name of output-file : ";
	cin >> outfileName;
	OutFile(fileName, outfileName, hc);

	//д���ļ�





//���룺
	//����������ļ�





	//�����ļ����������Ʊ���ת��Ϊ�ַ�





	//д���ļ�



}