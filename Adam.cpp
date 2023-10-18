//
// Created by Roberto Sala on 12/09/23.
//

#include "Adam.h"
#include <random>
#include <cmath>


std::vector<int> Adam::create_batch() {

    std::vector<int> indices;

    for (std::size_t i = 0; i < dim_batch; ++i)
        indices.push_back(distribution(generator));

    return indices;

}


double Adam::evaluate_batch(const Point &parameters, const std::vector<int> & batch) const {

    double value = 0.0;

    for (const auto i : batch)
        value += f.evaluate(observations[i], parameters);

    return value / batch.size();

}


double Adam::evaluate_partial_derivative_batch(std::size_t j, const Point &parameters, const std::vector<int> & batch) const {

    double value = 0.0;

    for(const auto i : batch) {
        value += f.evaluate_partial_derivative(j, observations[i], parameters);
    }

    return value / batch.size();

}


void Adam::set_f(const FunctionRn &f_) {

    f = f_;

}


void Adam::set_observations(const std::vector<Point> &observations_) {

    observations = observations_;

}


void Adam::set_dim_batch(unsigned int dim_batch_) {

    dim_batch = dim_batch_;

}


void Adam::set_tolerance(double tolerance_) {

    tolerance = tolerance_;

}


void Adam::set_max_iterations(unsigned int max_iterations_) {

    max_iterations = max_iterations_;

}


void Adam::set_inf_limits(const std::vector<double> &inf_limits_) {

    inf_limits = inf_limits_;

}


void Adam::set_sup_limits(const std::vector<double> &sup_limits_) {

    sup_limits = sup_limits_;

}


const FunctionRn & Adam::get_f() const {

    return f;

}


const std::vector<Point> & Adam::get_observations() const {

    return observations;

}


unsigned int Adam::get_dim_batch() const {

    return dim_batch;

}


double Adam::get_tolerance() const {

    return tolerance;

}


unsigned int Adam::get_max_iterations() const {

    return max_iterations;

}


const std::vector<double> & Adam::get_inf_limits() const {

    return inf_limits;

}


const std::vector<double> & Adam::get_sup_limits() const {

    return sup_limits;

}


Point Adam::solve(const Point &initial_parameters) {

    const size_t N = initial_parameters.get_dimension(); // retrieve number of parameters
    size_t t=0; // time index
    Point theta (initial_parameters.get_coordinates()); // theta, point holding parameter info
    // previous observations of theta (theta_0 = initial_parameters)
    Point thetaPrev;
    // estimate of moments (two vectors of N elements), more memory efficient than Points
    std::vector<double> mt(N, 0), vt(N, 0);
    // ith component of gradient and corrected moments
    double gt, mHat, vHat, change;
    // variable to hold batch indexes
    std::vector<int> batch;
    // booleans to check convergence
    double thetaDistance, fDistance;
    bool thetaDistanceSignificant, fDistanceSignificant, maxIterationsUnreached;

    do {
        // update time index, previous observations and extract batch
        ++t;
        thetaPrev.set_coordinates(theta.get_coordinates());
        batch = create_batch();

        // element-wise updating of theta
        for (size_t i=0; i<N; ++i) {
            // evaluate gradient component and update moments
            gt = evaluate_partial_derivative_batch(i, thetaPrev, batch);
            mt[i] = gamma1 * mt[i] + (1-gamma1) * gt;
            vt[i] = gamma2 * vt[i] + (1-gamma2) * pow(gt, 2);
            mHat = mt[i] / (1-pow(gamma1, t));
            vHat = vt[i] / (1-pow(gamma2, t));
            change = alpha * mHat / (sqrt(vHat) + epsilon);
            theta.set_coordinate(i, thetaPrev.get_coordinate(i) - change);
            // check if theta is outside the bounds
            if ( (theta.get_coordinate(i)<inf_limits[i]) ||
                (theta.get_coordinate(i)>sup_limits[i]))
                // nudge it back in by using the average of the gradient
                // rationale is that if we ended out of bounds there is some sort of a local
                // minimum
                theta.set_coordinate(i, thetaPrev.get_coordinate(i) + mHat);

        }
        // evaluate convergence
        thetaDistance = theta.distance(thetaPrev);
        thetaDistanceSignificant = (thetaDistance > tolerance);
        // simple abs cast to int
        fDistance = std::abs(evaluate_batch(theta, batch) - evaluate_batch(thetaPrev, batch));
        fDistanceSignificant = ( fDistance > tolerance);
        maxIterationsUnreached = (t<max_iterations);

    }
    while (thetaDistanceSignificant && fDistanceSignificant && maxIterationsUnreached);

    return theta;
}
