/**
 * @file IStrategy.h
 */
#ifndef ISTRATEGY_H
#define ISTRATEGY_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <EntityProject/facade/common.h>
#include <EntityProject/graph.h>

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for IStrategy.
 * 
 * Handles IStrategy objects (different path options).  All concrete classes are
 * implemented in IStrategy.cc.  Inherits attributes from EntityProject.
 * 
 */
class IStrategy
{
    public:
        /**
         * @brief Used to set path given a start, end, and graph to navigate
         * 
         * @param[in] start vector of floats that is the starting point for the path
         * 
         * @param[in] end vector of floats that is the ending point for the graph
         * 
         * @param[in] g IGraph pointer that is used in case of SmartPath
         **/
        virtual std::vector<std::vector<float>> SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g) = 0;
    private:
        //stores the path that will be passed to drone
        std::vector< std::vector<float> > path_;
        //stores the graph that is passed into SetPath
        IGraph* graph_;
};
} //namespace csci3081

#endif
