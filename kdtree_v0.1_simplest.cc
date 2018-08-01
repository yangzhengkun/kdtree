//
// Created by yangzhengkun on 2018/8/1.
// reference: https://www.geeksforgeeks.org/k-dimensional-tree/
//
#include <iostream>

using namespace std;

// sample dimensions
const int k = 3;

struct Node
{
    int point[k];           // store k dimension sample
    Node *left, *right;

    Node() = default;

    Node(int arr[])
    {
        for (int i = 0; i < k; ++i)
            point[i] = arr[i];
        left = right = nullptr;
    }
};

/**
 * insert one node "point" to kdtree "root"
 * @param root root node of kdtree
 * @param point point to be inserted
 * @param depth current depth, initially 0
 * @return root node
 */
Node *insertNode(Node *root, int point[], unsigned depth)
{
    if (root == nullptr)
        return new Node(point);
    unsigned cd = depth % k;
    if (point[cd] < (root->point[cd]))
        root->left = insertNode(root->left, point, depth + 1);
    else
        root->right = insertNode(root->right, point, depth + 1);
    return root;
}

/**
 * insert "point" to kdtree "root", call insertNode()
 * @param root root node of kdtree
 * @param point point to be inserted
 * @return root node
 */
Node *insert(Node *root, int point[])
{
    return insertNode(root, point, 0);
}

/**
 * check if point1 and point2 share the same value in k-dimension
 * @param point1
 * @param point2
 * @return true if point1 == point2
 */
bool samePoint(int point1[], int point2[])
{
    for (int i = 0; i < k; ++i)
    {
        if (point1[i] != point2[i])
            return false;
    }
    return true;
}

/**
 * search point in kdtree root
 * @param root
 * @param point
 * @param depth
 * @return
 */
bool searchNode(Node *root, int point[], unsigned depth)
{
    if (root == nullptr)
        return false;
    if (samePoint(root->point, point))
        return true;

    unsigned cd = depth % k;
    if (point[cd] < root->point[cd])
        return searchNode(root->left, point, depth + 1);
    else
        return searchNode(root->right, point, depth + 1);

}


bool search(Node *root, int point[])
{
    return searchNode(root, point, 0);
}

/**
 * travel kdtree "root" in in-order
 * @param root
 */
void inOrder(Node *root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);

    for (int i : root->point)
        cout << i << " ";
    cout << endl;

    inOrder(root->right);
}

void preOrder(Node *root)
{
    if (root == nullptr)
        return;
    for (auto i : root->point)
        cout << i << " ";
    cout << endl;
    preOrder(root->left);
    preOrder(root->right);
}

/**
 * free the memory
 * @param root
 */
void destoryTree(Node *root)
{
    if (root == nullptr)
        return;
    destoryTree(root->left);
    destoryTree(root->right);
    delete root;
}

int main()
{
    Node *root = nullptr;
    int points[][k] = {{3,  6,  5},
                       {17, 15, 22},
                       {13, 15, 8},
                       {6,  12, 16},
                       {9,  1,  19},
                       {2,  7,  9},
                       {10, 19, 3}};
    /**
     *                      (3,6,5)
     *                      /     \
     *                 (2,7,9)  (17,15,22)
     *                           /     \
     *                     (6,12,16)  (13,15,8)
     *                         \         /
     *                       (9,1,19)(10,19,3)
     */
    int n = sizeof(points) / sizeof(points[0]);
    for (int i = 0; i < n; ++i)
    {
        root = insert(root, points[i]);
    }
    cout << "inorder:  \n";
    inOrder(root);
    cout << "preorder: \n";
    preOrder(root);

    int point[]{2, 7, 3};
    auto ret = search(root, point);
    cout << boolalpha << ret << endl;
    destoryTree(root);

    return 0;
}


