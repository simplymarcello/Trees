// Created by Marcello Martins on Saturday, October 3, 2015
// Last modified on Tuesday, October 6, 2015
// Header and implementation file for the SequenceMap

/** @file SequenceMap.h */

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
using namespace std; 

// SequenceMap class
//
// ************************CONSTRUCTORS********************
// SequenceMap()							--> default no paramaters
// SequenceMap( str )					--> inits recognition_sequence_
//															> to str
// SequenceMap( str, str )		--> inits recognition_sequence_ to
//															> first str and enzyme_acronyms_
// 															> to second str
// ******************PUBLIC OPERATIONS*********************
// void Merge( x )       	--> merges the x.enzyme_acronyms_
//													>	with the object’s enzyme_acronyms_
// ******************ERRORS********************************
// none

class SequenceMap
{
	public:

		/**
		 * default constructer
		 */
		SequenceMap() {}

		/**
		 * constructs a SequenceMap from one string
		 */
		SequenceMap(const string & a_rec_seq) : recognition_sequence_{a_rec_seq}, enzyme_acronyms_{} {}

		/**
		 * constructs a SequenceMap from two strings
		 */
		SequenceMap(const string & a_rec_seq, const string & an_enz_acro) : recognition_sequence_{a_rec_seq}, enzyme_acronyms_{an_enz_acro} {}

		/**
		 * copy constructor
		 */
		SequenceMap( const SequenceMap & rhs) : recognition_sequence_{rhs.recognition_sequence_}, enzyme_acronyms_{rhs.enzyme_acronyms_} {}

		/**
		 * move constructor
		 */
		SequenceMap( SequenceMap && rhs): recognition_sequence_{ std::move(rhs.recognition_sequence_) }, enzyme_acronyms_{ std::move(rhs.enzyme_acronyms_) } {}

		/**
		 * assignment operator
		 */
		SequenceMap & operator=( const SequenceMap & rhs )
		{
			string stmp(rhs.recognition_sequence_);
			vector<string> vtmp(rhs.enzyme_acronyms_);
			recognition_sequence_.swap(stmp);
			enzyme_acronyms_.swap(vtmp);
			return *this;
		}
		
		/**
		 * move assignment operator
		 */
		SequenceMap & operator=( SequenceMap && rhs)
		{
			recognition_sequence_ = std::move(rhs.recognition_sequence_);
			enzyme_acronyms_ = std::move(rhs.enzyme_acronyms_);
			return *this;
		}

		/**
		 * merge function
		 */
		void Merge(const SequenceMap & other_sequence )
		{
			enzyme_acronyms_.insert(enzyme_acronyms_.end(), other_sequence.enzyme_acronyms_.begin(), other_sequence.enzyme_acronyms_.end());
		}

		/**
		 * overloaded < operator, allows for comparing two recongintion sequences
		 */
		bool operator<(const SequenceMap & rhs) const
		{
			return recognition_sequence_ < rhs.recognition_sequence_;
		}

		/**
		 * overloaded < operator, allows for comparing a string to a recongintion sequence
		 */
		friend bool operator<( string& x, const SequenceMap & rhs)
		{
			return x < rhs.recognition_sequence_;
		}

		/**
		 * overloaded < operator, allows for comparing a recongintion sequence to a string
		 */
		friend bool operator<( const SequenceMap & lhs, string& x)
		{
			return lhs.recognition_sequence_ < x;
		}


		/**
		 * overloaded << operator
		 */
		friend ostream & operator<<( ostream& out, SequenceMap & rhs ) 
		{
			out << rhs.recognition_sequence_ << " - ";
			for ( vector<string>::iterator i = rhs.enzyme_acronyms_.begin(); i != rhs.enzyme_acronyms_.end(); ++i)
			{
				out << *i << " / ";
			}
			out << endl;
			return out;
		}

	private:
		string recognition_sequence_;
		vector<string> enzyme_acronyms_;

}; // SequenceMap 

#endif // SEQUENCE_MAP_H