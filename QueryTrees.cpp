// Created by Marcello Martins on Saturday, October 3, 2015
// Last modified on Tuesday, October 6, 2015
// Test single query

/** @file QueryTrees.cpp */

#include <iostream> // cout, cin
#include <fstream>  // ifstream
#include <sstream>  // sstream
#include <string>   // strings
#include "SequenceMap.h"
#include "AvlTree.h"
#include "BinarySearchTree.h"
using namespace std;

template <class T>
void QueryTree(T &, const string, const string);

int main(int argc, char **argv) 
{
  if (argc != 3) 
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }

  string db_filename(argv[1]);
  string param_tree(argv[2]);

  if (param_tree == "BST") 
  {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(a_tree, db_filename, param_tree);
  }

  else if (param_tree == "AVL") 
  {
    AvlTree<SequenceMap> a_tree;
    QueryTree(a_tree, db_filename, param_tree);
  }

  else 
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;

  return 0;
}

template <class T>
void QueryTree(T & a_tree, string db_filename, string tree_type)
{
    cout << endl;
    cout << endl;

    cout << "Input filename is " << db_filename << endl;
    cout << "I will run the " << tree_type << " code" << endl;

    //fill tree from db file
    string db_line, input;
    ifstream db_file(db_filename); 
    if (db_file.is_open()) 
    {
      stringstream ss{};
      char c;
      while (getline(db_file, db_line))
      {
        string an_enz_acro, a_reco_seq;
        ss.str(db_line);
        while(ss >> c)
        {
          if (c == '/')
            break;
          an_enz_acro += c;
        }
        while(ss >> c)
        {
          if (c == '/')
          {
            SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
            a_tree.insert(new_sequence_map);
            a_reco_seq = "";
            if (ss.peek() == '/')
              break;
            continue;
          }
          a_reco_seq += c;
        }
      }
    }

    else
    {
      cout << "Could not open file, please check file name." << endl;
      return;
    }

    //prompt user for input and search tree
    cout << "Please enter a recognition sequence to search for in the BinarySearchTree: ";
    cin >> input;
    SequenceMap query_sequence_map(input);
    cout << "Searching tree... \nQuery output: ";
    a_tree.printNode(query_sequence_map);
    cout << "End of the " << tree_type << " code" << endl;

    cout << endl;
    cout << endl;
}
