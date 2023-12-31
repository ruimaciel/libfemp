#ifndef FEMP_ANALYSISRESULT_HPP
#define FEMP_ANALYSISRESULT_HPP

// libfemp includes
#include <libfemp/ElementResults/ElementResults.hpp>
#include <libfemp/ElementResults/ResultsRanges.hpp>
#include <libfemp/Point3D.hpp>
#include "Equation.hpp"

// la includes
#include <la/Matrix.hpp>
#include <la/Vector.hpp>

// boost includes
#include <boost/tuple/tuple.hpp>

// std includes
#include <map>

namespace fem {

/**
 * Stores all the relevant analysis results which are generated by
 * fem::Analysis and are needed in post-processing.
 */
struct AnalysisResult {
  AnalysisResult();
  AnalysisResult(const AnalysisResult&);

  // The FEM equation bit
  Equation equation;

  std::map<size_t, boost::tuple<size_t, size_t, size_t>> lm;

  // A map between the reference to a node and the displacements of it's DoF
  std::map<size_t, fem::Point3D> displacements;

  // map between a element reference and the element's recovered values
  std::map<element_ref_t, ElementResults*> results;

  // this replaces the above code
  ResultsRanges<double> ranges;

  // the model's energy
  double energy;

  double volume;

  // elapsed time in miliseconds (taken from Qt's qint64
  long long int elapsed_time;

  void clear();
};

}  // namespace fem

#endif
