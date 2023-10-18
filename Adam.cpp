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

    Point theta(initial_parameters.get_coordinates());
    bool converged = false; // this might need better initialization
    // initialize moments as zeros
    std::vector<double> mt(theta.get_dimension(), 0), vt(theta.get_dimension(), 0);

    for (size_t t=0; t < max_iterations && !converged; t++) { // loop of iterations
        // save old theta to compute distance later
        Point thetaPrev(theta.get_coordinates());
        // extract the batch
        std::vector<int> batch = create_batch();
        for (size_t i=0; i<theta.get_dimension(); i++) { // loop of components of theta
            // update the gradient components and moments
            const double gt = evaluate_partial_derivative_batch(i, theta, batch);
            mt[i] = gamma1 * mt[i] + (1-gamma1) * gt;
            vt[i] = gamma1 * vt[i] + (1-gamma2) * pow(gt, 2);
            double mHat = mt[i] / (1-pow(gamma1,t+1));
            double vHat = vt[i] / (1-pow(gamma2, t+1));
            const double change = alpha * mHat / (sqrt(vHat) + epsilon);
            // update ith component of theta
            theta.set_coordinate(i, theta.get_coordinate(i) - change);
            // check boundaries and clip
            if (theta.get_coordinate(i) < inf_limits[i])
                theta.set_coordinate(i, inf_limits[i]);
            if (theta.get_coordinate(i) > sup_limits[i])
                theta.set_coordinate(i, sup_limits[i]);
        }
        // evaluate f at the two points
        const double fValue = evaluate_batch(theta, batch);
        const double fPrevValue = evaluate_batch(thetaPrev, batch);

        converged = (std::abs(fValue - fPrevValue) < tolerance) || // change in f
            (theta.distance(thetaPrev) < tolerance); // change in theta
    }

    return theta;
}
