#include "HuffCode.hpp"
#include <cstdio>
#include <vector>
#include <unordered_map>

std::unordered_map<char,std::string> huffmanTable;//散装哈夫曼编码表

void travPre_R_show(BinNodePosi(HuffChar) x ,std::string code = "")
{
	if (!x) return;
	// std::cout << x->data.ch << ' ';
	// travPre_R_show(x->lc);
	// travPre_R_show(x->rc);
    if(!x->lc && !x->rc) huffmanTable[x->data.ch] = code;
    if(x->lc) {travPre_R_show(x->lc,code + '0');}
    if(x->rc) {travPre_R_show(x->rc,code + '1');}
}

int main()
{   
	char file[45] = "/home/crayzamb/projects/DS2024/exp3/word.txt";//若选择编译运行请修改file路径（linux端无法导入相对路径
	unsigned int* freq = statistics(file);//根据样本文件，统计各字符的出现频率
	HuffForest* forest = initForest(freq); delete freq; //创建Huffman森林
	HuffTree* tree = generateTree(forest); delete forest;//构造Huffman编码树
    // HuffTable* table - generateTable(tree);
	std::cout << "哈夫曼树前序遍历之后的哈夫曼编码表为：" << std::endl;
	travPre_R_show(tree->root());//初始化编码表
    for(const auto&i : huffmanTable)
    {
        char data = i.first;
        std::string code = i.second;
        std::cout << data<<": "<< code<<std::endl;
    }
    std::cout<<std::endl;
    /*bitmap没学，不用*/
    // for(int i = 2;i<argc;i++) 
    // {
    //     Bitmap* codeString = new Bitmap;
    //     int n = encode(table,codeString,argv[i]);
    //     decode(tree,codeString,n);
    //     codeString = nullptr;
    // }
    // table = nullptr;
    tree = nullptr;
    return 0;
}