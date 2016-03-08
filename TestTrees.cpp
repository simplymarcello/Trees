// Created by Marcello Martins on Saturday, October 3, 2015
// Last modified on Tuesday, October 6, 2015
// Test tree types

/** @file TestTrees.cpp */

#include <iostream> // cout, cin
#include <fstream>  // ifstream
#include <sstream>  // sstream
#include <cstdlib>  // EXIT_FAILURE
#include <string>   // strings
#include <chrono>   // now()
#include <cmath>    // log()
#include "SequenceMap.h"
#include "AvlTree.h"
#include "BinarySearchTree.h"

using namespace std;

template <class T>
void TestTree(T &, string, string, string );

int main(int argc, char **argv)
{
  if (argc != 4) 
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }

  string db_filename(argv[1]);
  string query_filename(argv[2]);
  string param_tree(argv[3]);

  if (param_tree == "BST") 
  {
    BinarySearchTree<SequenceMap> a_tree; 
    TestTree(a_tree, db_filename, query_filename, param_tree);
  }

  else if (param_tree == "AVL") 
  {
    AvlTree<SequenceMap> a_tree; 
    TestTree(a_tree, db_filename, query_filename, param_tree);
  }

  else 
      cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;

  return 0;
}

template <class T>
void TestTree(T & a_tree, string db_filename, string query_filename, string tree_type )
{
  cout << endl;
  cout << endl;

  string db_line, query_line, removal_line;
  int totalNodes, successful_queries = 0, successful_removals = 0, failed_queries = 0, failed_removals = 0;
  double avgDepth, treeRatio;

  cout << "Input file is " << db_filename << ", and query file is " << query_filename << endl;
  cout << "I will run the " << tree_type << " code" << endl;
  cout << endl;

  //time and fill tree from db file
  const auto begin_time_construction = chrono::high_resolution_clock::now();
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
    cout << "Could not open DB_file, please check file name, and try again." << endl;
    return;
  }
  const auto end_time_construction = chrono::high_resolution_clock::now();

  //display time to fill results
  cout << "Time to construct " << tree_type << " tree: " 
       << chrono::duration_cast<chrono::nanoseconds>(end_time_construction-begin_time_construction).count() << " ns" << endl;
  cout << "Time to construct " << tree_type << " tree: " 
       << chrono::duration_cast<chrono::milliseconds>(end_time_construction-begin_time_construction).count() << " ms" << endl;

  //calculate total nodes, average depth and tree ratio and display results
  totalNodes = a_tree.countNodes();
  avgDepth = a_tree.avgDepth();
  treeRatio = avgDepth / ( log(totalNodes)/log(2) );
  cout << "This " << tree_type << " tree has " << totalNodes << " nodes" << endl;
  cout << "The average depth of this " << tree_type << " tree is " << avgDepth << endl;
  cout << "The ratio of average depth to log_2 n for this " << tree_type << " tree is " << treeRatio << endl;
  cout << endl;

  //time and query tree from db file
  const auto begin_time_query = chrono::high_resolution_clock::now();
  ifstream query_file(query_filename); 
  if (query_file.is_open()) 
  {
    while (getline(query_file, query_line))
    {
      SequenceMap query_sequence_map(query_line);
      a_tree.contains(query_sequence_map) ? successful_queries++ : failed_queries++;
    }
  }
  const auto end_time_query = chrono::high_resolution_clock::now();

  //display time and query results
  cout << "Total number of successful queries from " << query_filename << " in " << tree_type << " tree: " << successful_queries << endl;
  cout << "Total number of failed queries from " << query_filename << " in " << tree_type << " tree: " << failed_queries << endl;
  cout << "Time to complete queries in " << tree_type << " tree: " 
       << chrono::duration_cast<chrono::nanoseconds>(end_time_query-begin_time_query).count() << " ns" << endl;
  cout << "Time to complete queries in " << tree_type << " tree: " 
       << chrono::duration_cast<chrono::milliseconds>(end_time_query-begin_time_query).count() << " ms" << endl;
  cout << endl;

  //time and remove nodes from db file
  const auto begin_time_removals = chrono::high_resolution_clock::now();
  ifstream removal_file(query_filename); 
  if (removal_file.is_open()) 
  {
    while (getline(removal_file, removal_line))
    {
      SequenceMap removal_sequence_map(removal_line);
      a_tree.remove(removal_sequence_map) ? successful_removals++ : failed_removals++;
      getline(removal_file, removal_line);
    }
  }
  const auto end_time_removals = chrono::high_resolution_clock::now();

  //display results from removal
  cout << "Total number of successful removals in " << query_filename << " from " << tree_type << " tree: " << successful_removals << endl;
  cout << "Total number of failed removals in " << query_filename << " from " << tree_type << " tree: " << failed_removals << endl;
  cout << "Time to complete removals from " << tree_type << " tree: "
       << chrono::duration_cast<chrono::nanoseconds>(end_time_removals-begin_time_removals).count() << " ns" << endl;
  cout << "Time to complete removals from " << tree_type << " tree: " 
       << chrono::duration_cast<chrono::milliseconds>(end_time_removals-begin_time_removals).count() << " ms" << endl;
  cout << endl;

  //recalculate total nodes, average depth and tree ratio and display results
  totalNodes = a_tree.countNodes();
  avgDepth = a_tree.avgDepth();
  treeRatio = avgDepth / ( log(totalNodes)/log(2) );
  cout << "This " << tree_type << " tree has " << totalNodes << " nodes" << endl;
  cout << "The average depth of this " << tree_type << " tree is " << avgDepth << endl;
  cout << "The ratio of average depth to log_2 n for this " << tree_type << " tree is " << treeRatio << endl;

  cout << "End of the " << tree_type << " code" << endl;

  cout << endl;
  cout << endl;

}