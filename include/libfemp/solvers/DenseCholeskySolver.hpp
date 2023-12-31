#ifndef FEMP_DENSECHOLESKYSOLVER_HPP
#define FEMP_DENSECHOLESKYSOLVER_HPP

#include <stdio.h>

#include <la/Matrix.hpp>
#include <la/ProgressIndicatorStrategy.hpp>
#include <la/output.hpp>
#include <la/solvers/Cholesky.hpp>
#include <libfemp/AnalysisResult.hpp>
#include <libfemp/solvers/Solver.hpp>

namespace fem {

template <typename Scalar>
class DenseCholeskySolver : public Solver<Scalar> {
 protected:
  lalib::Matrix<Scalar> L;

 public:
  enum Solver<Scalar>::Error initialize(Equation& equation,
                                        ProgressIndicatorStrategy* progress);
  enum Solver<Scalar>::Error solve(Equation& equation,
                                   ProgressIndicatorStrategy* progress);
  enum Solver<Scalar>::Error cleanup(Equation& equation,
                                     ProgressIndicatorStrategy* progress);
};

template <typename Scalar>
enum Solver<Scalar>::Error DenseCholeskySolver<Scalar>::initialize(
    Equation& equation,
    ProgressIndicatorStrategy*) {
  assign(L, equation.K);
  return Solver<Scalar>::ERR_OK;
}

template <typename Scalar>
enum Solver<Scalar>::Error DenseCholeskySolver<Scalar>::solve(
    Equation& equation,
    ProgressIndicatorStrategy*) {
  // using namespace std;
  // cout << "K\n" << K << "\n\nL:\n" << L << endl;
  lalib::cholesky(equation.K, equation.d, equation.f, L);

  return Solver<Scalar>::ERR_OK;
}

template <typename Scalar>
enum Solver<Scalar>::Error DenseCholeskySolver<Scalar>::cleanup(
    Equation&,
    ProgressIndicatorStrategy*) {
  return Solver<Scalar>::ERR_OK;
}

}  // namespace fem

#endif
