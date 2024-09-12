#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;
class strint
{
public:
    int freq;
    string symbol;
    strint(int f = -1, string s = "")
    {
        freq = f;
        symbol = s;
    }
};
class TreeNode
{
public:
    strint data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int t = -1)
    {
        data.freq = t;
        data.symbol = "";
        left = NULL;
        right = NULL;
    }
    TreeNode(strint d)
    {
        data.freq = d.freq;
        data.symbol = d.symbol;
        left = NULL;
        right = NULL;
    }
};
class Heap
{
public:
    TreeNode *arr;
    int size;
    int count;
    Heap(int s = 0)
    {
        arr = new TreeNode[s];
        count = 0;
    }
};
int reverseBits(int n, int totbits)
{
    int rev = 0;
    while (totbits > 0)
    {
        rev <<= 1;
        if (n & 1 == 1)
            rev ^= 1;
        n >>= 1;
        totbits--;
    }
    return rev;
}
void insertHeap(Heap *heap, TreeNode *item)
{
    heap->count++;
    int i = heap->count - 1;
    while (i > 0 && item->data.freq < (heap->arr[(i - 1) / 2]).data.freq)
    {
        heap->arr[i] = heap->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->arr[i] = *item;
}
void PrecolateDown(Heap *heap, int i)
{
    if (i >= heap->count)
    {
        return;
    }
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l >= heap->count)
    {
        return;
    }
    if (r >= heap->count)
    {
        r = i;
    }
    int min;
    if (heap->arr[l].data.freq != -1 && heap->arr[l].data.freq < heap->arr[i].data.freq)
    {
        min = l;
    }
    else
    {
        min = i;
    }
    if (heap->arr[r].data.freq != -1 && heap->arr[r].data.freq < heap->arr[min].data.freq)
    {
        min = r;
    }
    if (min != i)
    {
        swap(heap->arr[i], heap->arr[min]);
    }
    else
    {
        return;
    }
    PrecolateDown(heap, min);
}
TreeNode *deleteHeapMin(Heap *heap)
{
    TreeNode *node = new TreeNode(-1);
    if (heap->count <= 0)
    {
        return node;
    }
    node->data.freq = heap->arr[0].data.freq;
    node->data.symbol = heap->arr[0].data.symbol;
    node->left = heap->arr[0].left;
    node->right = heap->arr[0].right;
    heap->arr[0] = heap->arr[heap->count - 1];
    heap->arr[heap->count - 1].data.freq = -1;
    heap->count--;
    if (heap->arr[0].data.freq != -1)
        PrecolateDown(heap, 0);
    return node;
}
uint8_t hashFunction(char ch)
{
    uint8_t key = ch;
    return key;
}
void inOrder(TreeNode *node)
{
    if (node)
    {
        inOrder(node->left);
        cout << node->data.symbol << endl;
        cout << node->data.freq << endl;
        inOrder(node->right);
    }
}
int totalNodes(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int l = totalNodes(root->left);
    int r = totalNodes(root->right);
    return 1 + l + r;
}
bool search(string source, char key)
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i] == key)
        {
            return true;
        }
    }
    return false;
}
void displayHuffmanCode(TreeNode *root, int code)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        char ch = root->data.symbol[0];
        cout << (int)ch << " " << ch << "  " << code << endl;
        return;
    }
    displayHuffmanCode(root->left, code * 10);
    displayHuffmanCode(root->right, code * 10 + 1);
}
int main()
{
    int hashTable[256][2]{0};
    char freq;
    ifstream inf{"dsa.pdf", ios::binary};
    if (!inf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
        return 1;
    }
    inf.seekg(0, ios::end);
    unsigned int length_of_file = inf.tellg();
    inf.seekg(0, ios::beg);
    string input;
    input.resize(length_of_file);
    inf.read(&input[0], length_of_file);
    // string input = static_cast<string>(buff);
    inf.close();
    // ostringstream ss;
    // ss << inf.rdbuf(); // reading data
    // string input = ss.str();
    // inf.close();

    // int length_of_file = input.size();
    unsigned char read;

    for (int i = 0; i < length_of_file; i++)
    {
        hashTable[hashFunction(input[i])][1]++;
        hashTable[hashFunction(input[i])][0] = hashFunction(input[i]);
    }
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256 - i - 1; j++)
        {
            if (hashTable[j][1] < hashTable[j + 1][1])
            {
                swap(hashTable[j][0], hashTable[j + 1][0]);
                swap(hashTable[j][1], hashTable[j + 1][1]);
            }
        }
    }
    int sum = 0;
    for (int k = 0; k < 256; k++)
    {
        sum += hashTable[k][1];
    }
    int i;
    for (i = 0; i < 256; i++)
    {
        if (hashTable[i][1] > 0)
        {
            // cout << static_cast<char>(hashTable[i][0]) << "=>" << hashTable[i][1] << endl;
        }
        else
        {
            cout << "here " << i << endl;
            break;
        }
    }
    int numberOFsymbols = i;
    cout << "number of symbols=" << numberOFsymbols << endl;
    Heap *heap = new Heap(i + 1);
    for (int j = 0; j < i; j++)
    {
        if (hashTable[j][1] > 0)
        {
            string temp = " ";
            temp[0] = (static_cast<unsigned char>(hashTable[j][0]));
            TreeNode *node = new TreeNode(strint(hashTable[j][1], temp));
            insertHeap(heap, node);
        }
    }
    TreeNode *root = NULL;
    while (heap->count > 0)
    {
        TreeNode *node = NULL;
        TreeNode *node1 = NULL;
        if (heap->count > 0)
            node1 = deleteHeapMin(heap);
        else
            break;
        if (node1->data.freq != -1)
        {
            node = new TreeNode;
            node->left = node1;
            node->data.freq = node1->data.freq;
            node->data.symbol.append(node1->data.symbol);
            TreeNode *node2 = NULL;
            if (heap->count > 0)
                node2 = deleteHeapMin(heap);
            else
                break;
            if (node2->data.freq != -1)
            {
                node->right = node2;
                node->data.freq = node->data.freq + node2->data.freq;
                node->data.symbol.append(node2->data.symbol);
            }
        }
        insertHeap(heap, node);
        if (heap->count == 1)
        {
            break;
        }
    }
    root = &(heap->arr[0]);
    // displayHuffmanCode(root, 1);
    ofstream outf{"compressed.txt", ios::binary};
    if (!outf)
    {
        return 1;
    }
    read = numberOFsymbols;
    outf << read;
    unsigned int totalbytes = root->data.freq;
    outf << totalbytes << '\n';
    TreeNode *trv;
    for (int i = 0; i < numberOFsymbols; i++)
    {
        trv = root;
        unsigned char *code = new unsigned char[32]{0};
        int noOFbits = 0;
        char read = hashTable[i][0];
        int cnt = 0;
        while (true)
        {
            if (trv->data.symbol.length() == 1)
            {
                if (trv->data.symbol[0] - read == 0)
                    break;
            }
            code[cnt] = code[cnt] >> 1;

            if (search(trv->left->data.symbol, read))
            {
                trv = trv->left;
            }
            else if (search(trv->right->data.symbol, read))
            {
                trv = trv->right;
                code[cnt] = code[cnt] | (128);
            }
            else
            {
                cout << "error";
            }
            noOFbits++;
            if (noOFbits % 8 == 0)
            {
                cnt++;
            }
        }
        outf << read;
        outf << (char)noOFbits;
        int m = 0;
        if (noOFbits % 8 == 0)
        {
            cnt--;
        }
        do
        {
            outf << code[m];
            m++;
        } while (m <= (cnt));

        delete[] code;
    }
    unsigned char ch = 0;
    TreeNode *travel;
    int noOFbits = 0;
    i = 0;
    for (int i = 0; i < length_of_file; i++)
    {
        travel = root;
        while (true)
        {
            if (noOFbits >= 8)
            {
                outf << ch;
                ch = 0;
                noOFbits = 0;
            }
            if (travel->data.symbol.length() == 1)
            {
                if (travel->data.symbol[0] - input[i] == 0)
                    break;
            }
            ch = ch >> 1;
            if ((search(travel->left->data.symbol, input[i])))
            {
                travel = travel->left;
            }
            else
            {
                travel = travel->right;
                ch = ch | (128);
            }
            noOFbits++;
        }
    }
    ch = ch >> (8 - noOFbits);
    outf << ch;
    outf.close();
    input.clear();
    outf.open("decompressed.pdf", ios::binary);
    inf.open("compressed.txt", ios::binary);
    ostringstream ss1;
    ss1 << inf.rdbuf();
    string input1 = ss1.str();
    inf.close();
    int j = 0;
    numberOFsymbols = 0;
    numberOFsymbols = (unsigned char)(input1[j]);
    j++;
    totalbytes = 0;
    do
    {
        totalbytes = totalbytes * 10 + ((int)input1[j] - 48);
        j++;
    } while (input1[j] != '\n');
    if (totalbytes > 0 && numberOFsymbols == 0)
    {
        numberOFsymbols = 256;
    }
    j++;
    int count = 0;

    TreeNode *rootnode = new TreeNode(0);
    TreeNode *traversal = rootnode;
    while (count < numberOFsymbols)
    {
        unsigned char symbol, noofbits, code;

        symbol = input1[j];
        j++;

        noofbits = input1[j];
        j++;
        int bitNoint = (int)noofbits;
        traversal = rootnode;
        int jpt;
        while (bitNoint > 0)
        {
            if (bitNoint >= 8)
            {
                jpt = 8;
            }
            else
            {
                jpt = bitNoint;
            }

            code = input1[j];
            if (jpt < 8)
            {
                code = code >> (8 - jpt);
            }
            j++;
            while (jpt > 0)
            {
                int rem = code % 2;
                code = code / 2;
                jpt--;
                if (rem == 0)
                {
                    if (traversal->left == NULL)
                    {
                        string temp = " ";
                        temp[0] = symbol;
                        traversal->left = new TreeNode(strint(0, temp));
                    }
                    traversal = traversal->left;
                }
                else
                {
                    if (traversal->right == NULL)
                    {
                        string temp = " ";
                        temp[0] = symbol;
                        traversal->right = new TreeNode(strint(0, temp));
                    }
                    traversal = traversal->right;
                }
            }
            bitNoint = bitNoint - 8;
        }

        count++;
    }
    traversal = rootnode;
    char check;
    check = input1[j];
    while (totalbytes > 0)
    {

        read = input1[j];
        check = read;
        j++;
        int bitsOperated = 0;
        while (bitsOperated < 8)
        {
            int rem = read % 2;
            read = read / 2;

            if (rem == 0)
            {
                traversal = traversal->left;
                if (traversal->left == NULL && traversal->right == NULL)
                {
                    outf << traversal->data.symbol;
                    traversal = rootnode;
                    totalbytes--;
                }
            }
            else
            {
                traversal = traversal->right;
                if (traversal->left == NULL && traversal->right == NULL)
                {
                    outf << traversal->data.symbol;
                    traversal = rootnode;
                    totalbytes--;
                }
            }
            if (totalbytes == 0)
            {
                break;
            }
            bitsOperated++;
        }
    }
    outf.close();
    return 0;
}