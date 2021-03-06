/*
  FILE: BedBaseVisitor.hpp
  AUTHOR: Shane Neph & Scott Kuehn
  CREATE DATE: Dec. 7, 2009
  PROJECT: utility
  ID: $Id$
*/

//
//    BEDOPS
//    Copyright (C) 2011, 2012, 2013 Shane Neph, Scott Kuehn and Alex Reynolds
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

#ifndef _VISITOR_POST_PROCESSING_
#define _VISITOR_POST_PROCESSING_

#include <iostream>
#include <ostream>
#include <string>

#include "data/measurement/NaN.hpp"
#include "utility/PrintTypes.hpp"


namespace Visitors {

  namespace Helpers {

    //=============
    // DoNothing()
    //=============
    struct DoNothing {
      void operator()(...) const { /* */ }
    };


    //======
    // Keep
    //======
    template <typename ValueType>
    struct Keep {
      Keep() : isNan_(false), value_(0)
        { }

      template <typename T>
      void operator()(T* t) {
        value_ = static_cast<ValueType>(*t);
        isNan_ = false;
      }

      template <typename T>
      void operator()(const T& t) {
        value_ = static_cast<ValueType>(t);
        isNan_ = false;
      }

      void operator()(const Signal::NaN&) {
        isNan_ = true;
      }

      bool isNan_;
      ValueType value_;
    };

  
    //=========
    // Print()
    //=========
    struct Print {
      Print(std::ostream& os = std::cout, const std::string& fieldSep = "\t")
        : os_(os), fieldSep_(fieldSep)
        { /* */ }
  
      template <typename T>
      void operator()(T* t) {
        os_ << *t;
      }

      template <typename T>
      void operator()(const T& t) {
        os_ << t;
      }
  
      template <typename T, typename U>
      void operator()(const T& t, const U& u) {
        os_ << t << fieldSep_ << u;
      }
  
      template <typename T, typename U, typename V>
      void operator()(const T& t, const U& u, const V& v) {
        os_ << t << fieldSep_ << u << fieldSep_ << v;
      }
  
    protected:
      std::ostream& os_;
      std::string fieldSep_;
    };
  
  
    //===========
    // Println()
    //===========
    struct Println {
      Println(std::ostream& os = std::cout, const std::string& fieldSep = "\t")
        : os_(os), fieldSep_(fieldSep)
        { /* */ }

      template <typename T>
      void operator()(T* t) {
        os_ << *t << std::endl;
      }
  
      template <typename T>
      void operator()(const T& t) {
        os_ << t << std::endl;
      }
  
      template <typename T, typename U>
      void operator()(const T& t, const U& u) {
        os_ << t << fieldSep_ << u << std::endl;
      }
  
      template <typename T, typename U, typename V>
      void operator()(const T& t, const U& u, const V& v) {
        os_ << t << fieldSep_ << u << fieldSep_ << v << std::endl;
      }
  
    protected:
      std::ostream& os_;
      std::string fieldSep_;
    };

    //============
    // PrintDelim
    //============
    struct PrintDelim {
      explicit PrintDelim(const std::string& delim = "|")
        : delim_(delim)
      { /* */ }

      void operator()() const {
        PrintTypes::Print(delim_.c_str());
      }

    private:
      std::string delim_;
    };

  } // namespace Helpers

} // namespace Visitors

#endif // _VISITOR_POST_PROCESSING_
