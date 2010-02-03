#ifndef KOKKOS_TPINODE_HPP_
#define KOKKOS_TPINODE_HPP_

#include "Kokkos_StandardNodeMemoryModel.hpp"
#include "Kokkos_NodeHelpers.hpp"
#include <TPI.h>

namespace Teuchos {
  // forward declarations
  class ParameterList;
}

namespace Kokkos {

  template <class WDP>
  struct WDPPlusRange {
    WDPPlusRange(int Beg, int End, WDP Wdp) : wdp(Wdp), beg(Beg), end(End){}
    WDP wdp;
    int beg, end;
  };

  inline
  void tpi_work_span(TPI_Work* work, int beg, int end, int& ibeg, int& iend)
  {
    const int chunk = ( end - beg + work->count - 1 ) / work->count ;
  
    iend = chunk * ( work->rank + 1 ) + beg;
    ibeg = chunk * ( work->rank ) + beg;
  
    if ( end < iend ) { iend = end; }
  }

  template<class WDP>
  void tpi_execute(TPI_Work * work)
  {
    // get work/data pair
    const WDPPlusRange<WDP>* const_wdp_wrapper = static_cast<const WDPPlusRange<WDP>*>(work->info);
    WDPPlusRange<WDP>* wdp_wrapper = const_cast<WDPPlusRange<WDP>*>(const_wdp_wrapper);
    WDP wdp = wdp_wrapper->wdp;
    int beg = wdp_wrapper->beg, end = wdp_wrapper->end;
    int ibeg, iend;
    // determine my share of the work
    tpi_work_span(work, beg, end, ibeg, iend);
    // do my share of the work
    for (int i=ibeg; i<iend; ++i) {
      wdp.execute(i);
    }
  }

  template<class WDP>
  void tpi_reduction_work(TPI_Work * work)
  {
    const WDPPlusRange<WDP>* wdp_wrapper = static_cast<const WDPPlusRange<WDP>*>(work->info);
    int beg = wdp_wrapper->beg, end = wdp_wrapper->end;
    WDP wdp = wdp_wrapper->wdp;
    int ibeg, iend;
    tpi_work_span(work, beg, end, ibeg, iend);
  
    typedef typename WDP::ReductionType ReductionType;
    ReductionType tmpi;
    ReductionType &res = *(static_cast<ReductionType*>(work->reduce));
  
    for (int i=ibeg; i<iend; ++i) {
      tmpi = wdp.generate(i);
      res = wdp.reduce(res, tmpi);
    }
  }

  template<class WDP>
  void tpi_reduction_join(TPI_Work * work, const void* src)
  {
    typedef typename WDP::ReductionType ReductionType;
  
    const WDPPlusRange<WDP>* wdp_wrapper = static_cast<const WDPPlusRange<WDP>*>(work->info);
    WDP wdp = wdp_wrapper->wdp;
  
    ReductionType& work_reduce = *(static_cast<ReductionType*>(work->reduce));
    const ReductionType& src_reduce  = *(static_cast<const ReductionType*>(src));
  
    work_reduce = wdp.reduce(work_reduce, src_reduce);
  }

  template<class WDP>
  void tpi_reduction_init(TPI_Work * work)
  {
    typedef typename WDP::ReductionType ReductionType;
    *(static_cast<ReductionType*>(work->reduce)) = WDP::identity();
  }

  class TPINode : public StandardNodeMemoryModel {
    public:
  
      TPINode(Teuchos::ParameterList &plist);
  
      void init(int numThreads);
  
      ~TPINode();
  
      template <class WDP>
      static void parallel_for(int beg, int end, WDP wd) {
        WDPPlusRange<WDP> wdp_plus(beg,end,wd);
        TPI_Run_threads(tpi_execute<WDP>, &wdp_plus, 0 );
      }
  
      template <class WDP>
      static typename WDP::ReductionType 
      parallel_reduce(int beg, int end, WDP wd) {
        typedef typename WDP::ReductionType ReductionType;
        ReductionType result = WDP::identity();
        WDPPlusRange<WDP> wdp_plus(beg,end,wd);
        TPI_Run_threads_reduce(tpi_reduction_work<WDP>, &wdp_plus,
                               tpi_reduction_join<WDP>,
                               tpi_reduction_init<WDP>, sizeof(result), &result);
        return result;
      }
  
    private:
      int curNumThreads_;
  };

  template <> class ArrayOfViewsHelper<TPINode> : public ArrayOfViewsHelperTrivialImpl<TPINode> {};

} // end namespace Kokkos

#endif
