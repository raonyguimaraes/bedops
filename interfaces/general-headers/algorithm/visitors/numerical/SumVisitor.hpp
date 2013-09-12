/*
  FILE: SumVisitor.hpp
  AUTHOR: Shane Neph & Scott Kuehn
  CREATE DATE: Mon Aug 27 10:17:36 PDT 2007
  PROJECT: windowing-visitors
  ID: $Id:$
*/

// Macro Guard
#ifndef CLASS_WINDOW_SUM_VISITOR_H
#define CLASS_WINDOW_SUM_VISITOR_H


// Files included
#include "data/measurement/AssayMeasurement.hpp"
#include "data/measurement/NaN.hpp"


namespace Visitors {

  //=====
  // Sum
  //=====
  template <
            typename Process,
            typename BaseVisitor
           >
  struct Sum : public BaseVisitor {

    typedef BaseVisitor BaseClass;
    typedef Process ProcessType;
    typedef typename BaseClass::reference_type T1;
    typedef typename BaseClass::mapping_type T2;

    explicit Sum(const ProcessType& pt = ProcessType())
        : pt_(pt), sum_(0), counter_(0)
      { /* */ }

    inline void Add(T2* bt)
      { sum_ += *bt; ++counter_; }

    inline void Delete(T2* bt)
      { sum_ -= *bt; --counter_; }

    inline void DoneReference() {
      static const Signal::NaN nan = Signal::NaN();
      if ( 0 < counter_ )
        pt_.operator()(sum_);
      else
        pt_.operator()(nan);
    }

    virtual ~Sum()
      { /* */ }

  protected:
    ProcessType pt_;
    typename Signal::AssayMeasurement<T2>::value_type sum_;
    int counter_;
  };

} // namespace Visitors

#endif // CLASS_WINDOW_SUM_VISITOR_H