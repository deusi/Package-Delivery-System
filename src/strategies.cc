#include "strategies.h"

namespace csci3081{
	
std::vector<std::vector<float>> SmartPath::SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g)
{
    //using the graph's built-in GetPath function
    start_ = start;
    end_ = end;
    path_ = g->GetPath(start_, end_);
    return path_;
}

std::vector<std::vector<float>> BeelinePath::SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g)
{
    //setting starting point, need to set twice for some reason
    path_.push_back(start);
    path_.push_back(start);
    //moving up, right above starting point
    std::vector<float> start_high{ start[0], 400, start[2] };
    path_.push_back(start_high);
    //moving until right above end point
    std::vector<float> end_high{ end[0], 400, end[2] };
    path_.push_back(end_high);
    //adding end point to path
    path_.push_back(end);
    return path_;
}


std::vector<std::vector<float>> ParabolicPath::SetPath(std::vector<float> start, std::vector<float> end, const IGraph* g)
{
    //used to adjust vertical stretch of parabola
    float heightTuner = 50.0; 
    //direction vector in horizontal plane
    direction_.push_back(end[0] - start[0]);
    direction_.push_back(end[2] - start[2]);
    //magnitude of direction, used to make steps roughly uniform 
    float mag = sqrt(direction_[0]*direction_[0] + direction_[1] * direction_[1]); 
    int steps = static_cast<int>(mag);
    //make steps even to line up parabola correctly
    if (steps % 2 == 1){
        steps ++;
    }
    //normalizes direction to have magnitude of approx. 1
    direction_[0] = direction_[0]/steps;
    direction_[1] = direction_[1]/steps;
    //starting point
    path_.push_back(start);
    //mult is used as the variable in the quadratic expression for height
    float mult;
    //adding points along path, using direction to move in horizontal and quadratic to move in vertical
    for (int i = 1; i<=steps; i++){
        //mult will be between 0 and 1, increasing as i reaches steps
        mult = (float)(i)/(float)(steps);
        path_.push_back(path_[i-1]);
        path_[i][0] += direction_[0];
        path_[i][2] += direction_[1];
        //derived from Tushar's post on Canvas
        path_[i][1] = -((-4*heightTuner + 2*start[1] + 2*end[1]) * pow(mult, 2.0) + (4*heightTuner - 3*start[1] - end[1]) * (mult)) + start[1];
    }
    //pushes end point onto path
    path_.push_back(end);
    return path_;
}

} //namespace csci3081
