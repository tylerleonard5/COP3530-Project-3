// BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BST
{
public:
    struct node {
        node* left;
        node* right;
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

    node* root;

    node* makeEmpty(node* root) {
        if (root == NULL)
            return NULL;
        else {
            makeEmpty(root->left);
            makeEmpty(root->right);
            delete root;
        }
        return NULL;
    }

    node* insert(int id, node* root, vector<string> data) {
        if (root == NULL) {
            root = new node;
            root->ID = id;
            root->Region = data.at(0);
            root->Country = data.at(1);
            root->ItemType = data.at(2);
            root->Channel = data.at(3);
            root->Priority = data.at(4);
            root->OrderDate = data.at(5);
            root->ShipDate = data.at(7);
            root->UnitsSold = data.at(8);
            root->UnitPrice = data.at(9);
            root->UnitCost = data.at(10);
            root->TotalRevenue = data.at(11);
            root->TotalCost = data.at(12);
            root->TotalProfit = data.at(13);
            root->left = NULL;
            root->right = NULL;
        }
        else if (id < root->ID)
            root->left = insert(id, root->left, data);
        else if (id > root->ID)
            root->right = insert(id, root->right, data);
        return root;
    }

    vector<string> find(node* root, int id) {
        vector<string> search_row;
        search_row.clear();
        if (root == NULL) {
            return search_row;
        }
        else if (id < root->ID)
            return search_row = find(root->left, id);
        else if (id > root->ID)
            return search_row = find(root->right, id);
        else {
            search_row.push_back(root->Region);
            search_row.push_back(root->Country);
            search_row.push_back(root->UnitsSold);
            search_row.push_back(root->UnitPrice);
            search_row.push_back(root->UnitCost);
            search_row.push_back(root->TotalRevenue);
            search_row.push_back(root->TotalCost);
            search_row.push_back(root->TotalProfit);
            return search_row;
        }
    }

    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(vector<vector<string>> matrix) {
        for (int i = 0; i < matrix.size() - 1; i++) {
            vector<string> row = matrix[i];
            root = insert(stoi(row[6]), root, row);
        }
    }

    vector<string> search(int x) {
        vector<string> data = find(root, x);
        return data;
    }

    vector<vector<string>> readFile(string filename)
    {
        ifstream database(filename);
        vector<vector<string>> matrix;
        string temp;

        if (database.is_open())
        {
            string line;
            getline(database, line); //read in the first line reserved for column names

            while (!database.eof())
            {
                vector<string> row;
                for (int i = 0; i < 13; i++) {
                    getline(database, temp, ',');
                    row.push_back(temp);
                }
                getline(database, temp, '\n');
                row.push_back(temp);
                matrix.push_back(row);
            }

            return matrix;
        }
    }
};