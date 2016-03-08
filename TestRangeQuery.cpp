// Created by Marcello Martins on Saturday, October 3, 2015
// Last modified on Tuesday, October 6, 2015
// Test range queries 

/** @file TestRangeQuery.cpp */

#include <iostream> // cout, cin
#include <fstream>  // ifstream
#include <sstream>  // sstream
#include <cstdlib>  // EXIT_FAILURE
#include <string>   // strings
#include <chrono>   // now()
#include "SequenceMap.h"
#include "AvlTree.h"
using namespace std;

int main(int argc, char **argv) 
{
  if (argc != 4) 
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <string> <string2>" << endl;
    return 0;
  }

  cout << endl;
  cout << endl;

  string db_filename(argv[1]);
  string str1(argv[2]);
  string str2(argv[3]);

  string db_line;
  cout << "Input file is " << db_filename << " ";
  cout << "String 1 is " << str1 << " and string 2 is " << str2 << endl;

  //make and fill tree from db file
  AvlTree<SequenceMap> a_tree;
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
    cout << "Could not open DB_file, please check file name, exiting program..." << endl;
    exit (EXIT_FAILURE);
  }

  //make keys into sequence maps and print range
  SequenceMap Key1(str1);
  SequenceMap Key2(str2);
  a_tree.printRange(Key1, Key2);

  return 0;
}
