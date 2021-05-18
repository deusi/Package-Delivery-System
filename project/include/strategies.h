/**
 * @file strategies.h
 */
#ifndef STRATEGIES_H
#define STRATEGIES_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include "IStrategy.h"
#include <math.h>
#include <EntityProject/facade/common.h>

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for the Smart Strategy.
 *
 * Generates a smart path for the drone to follow.
 *
 */
class SmartPath : public IStrategy {

public:
    /**
         * @brief Used to set smart path given a start, end, and graph to navigate
         *
         * @param[in] start vector of floats that is the starting point for the path
         *
         * @param[in] end vector of floats that is the ending point for the graph
         *
         * @param[in] g IGraph pointer to the graph
    **/
    std::vector<std::vector<float>> SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g) override;

private:
    //Path to return
    std::vector< std::vector<float> > path_;
    //Start position of path
    std::vector<float> start_;
    //End position of path
    std::vector<float> end_;
    //Graph of routes
    const IGraph* graph_;
};
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for the Beeline Strategy.
 *
 * Generates a beeline path for the drone to follow.
 *
 */
class BeelinePath : public IStrategy {

public:
    /**
         * @brief Used to set beeline path given a start, end, and graph to navigate
         *
         * @param[in] start vector of floats that is the starting point for the path
         *
         * @param[in] end vector of floats that is the ending point for the graph
         *
         * @param[in] g IGraph pointer to the graph, not used by Beeline route.
    **/
    std::vector<std::vector<float>> SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g) override;

private:
    //Path to return
    std::vector< std::vector<float> > path_;
};

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for the Parabolic Strategy.
 *
 * Generates a parabolic path for the drone to follow.
 *
 */

class ParabolicPath : public IStrategy {

public:
    /**
         * @brief Used to set parabolic path given a start, end, and graph to navigate
         *
         * @param[in] start vector of floats that is the starting point for the path
         *
         * @param[in] end vector of floats that is the ending point for the graph
         *
         * @param[in] g IGraph pointer to the graph, not used by Parabolic route.
    **/
    std::vector<std::vector<float>> SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g) override;

private:
    //Path to return
    std::vector< std::vector<float> > path_;
    //Direction drone will travel in horizontal plane
    std::vector<float> direction_;
};

} //namespace csci3081
#endif //STRATEGIES_H
