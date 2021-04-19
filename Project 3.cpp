// Project 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;
class TreeNode
{

public:
    struct Record
    {
        string Region;
        string Country;
        string ItemType;
        string Channel;
        string Priority;
        string OrderDate;
        long ID;
        string ShipDate;
        string UnitsSold;
        string UnitPrice;
        string UnitCost;
        string TotalRevenue;
        string TotalCost;
        string TotalProfit;
    };

    Record record;
    int height = 0;
    int BalFactor = 0;
    TreeNode* left = NULL;
    TreeNode* right = NULL;

};

int getHeight(TreeNode* root)
{
    //Code from quiz 4
    if (root == NULL)
        return 0;
    int hl = getHeight(root->left); //traverse left subtree
    int hr = getHeight(root->right); //traverse right subtree

    return max(hl, hr) + 1;
}

TreeNode* rotateLeft(TreeNode* root)
{
    TreeNode* child = root->right;
    TreeNode* grandchild = child->left;
    child->left = root;
    root->right = grandchild;

    return child;

}

TreeNode* rotateRight(TreeNode* root)
{
    TreeNode* child = root->left;
    TreeNode* grandchild = child->right;
    child->right = root;
    root->left = grandchild;

    return child;

}

TreeNode* insert(TreeNode* root, TreeNode* newNode)
{
    if (root == NULL)
        return newNode;
    

    if (root)
    {
        if (newNode->record.ID < root->record.ID)
        {
            root->left = insert(root->left, newNode);
            root->height += 1;
        }
        else if (newNode->record.ID > root->record.ID)
        {
            root->right = insert(root->right, newNode);
            root->height += 1;
        }
        else
        {
            return root;
        }

        //Checking tree balance and rotating
        root->BalFactor = getHeight(root->left) - getHeight(root->right);

        if (root->BalFactor > 1 && root->left->record.ID  > newNode->record.ID)
            return rotateRight(root);
        else if (root->BalFactor < -1 && root->right->record.ID  < newNode->record.ID)
            return rotateLeft(root);
        else if (root->BalFactor > 1 && root->left->record.ID < newNode->record.ID)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        else if (root->BalFactor < -1 && root->right->record.ID  > newNode->record.ID)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }
    
}

TreeNode* readFile(string filename, TreeNode* root)
{
    ifstream database(filename);

    if (database.is_open())
    {
        string line;
        getline(database, line);

        while (getline(database, line))
        {
            stringstream ss(line);
            TreeNode* newNode = new TreeNode();
            getline(ss, newNode->record.Region, ',');
            getline(ss, newNode->record.Country, ',');
            getline(ss, newNode->record.ItemType, ',');
            getline(ss, newNode->record.Channel, ',');
            getline(ss, newNode->record.Priority, ',');
            getline(ss, newNode->record.OrderDate, ',');
            string token;
            getline(ss, token, ',');
            newNode->record.ID = stoi(token);
            getline(ss, newNode->record.ShipDate, ',');
            getline(ss, newNode->record.UnitsSold, ',');
            getline(ss, newNode->record.UnitPrice, ',');
            getline(ss, newNode->record.UnitCost, ',');
            getline(ss, newNode->record.TotalRevenue, ',');
            getline(ss, newNode->record.TotalCost, ',');
            getline(ss, newNode->record.TotalProfit, '\n');

            root = insert(root, newNode);
        }

        return root;
    }
}

void search(TreeNode* root, int ID)
{
    //Search for node with specific ID
    while (root)
    {
        if (root->record.ID == ID)
        {
            cout << "Region: " << root->record.Region << endl;
            cout << "Country: " << root->record.Country << endl;
            cout << "Item Type: " << root->record.ItemType << endl;
            cout << "Sales Channel: " << root->record.Channel << endl;
            cout << "Order Priority: " << root->record.Priority << endl;
            cout << "Order Date: " << root->record.OrderDate << endl;
            cout << "Ship Date: " << root->record.ShipDate << endl;
            cout << "Units Sold: " << root->record.UnitsSold << endl;
            cout << "Unit Price: " << root->record.UnitPrice << endl;
            cout << "Unit Cost: " << root->record.UnitCost << endl;
            cout << "Total Revenue: " << root->record.TotalRevenue << endl;
            cout << "Total Cost: " << root->record.TotalCost << endl;
            cout << "Total Profit: " << root->record.TotalProfit << endl;
            break;
        }
        else if (ID < root->record.ID)
            root = root->left;
        else
            root = root->right;
    }
    if (root == NULL)
        cout << "No Record Exists." << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
