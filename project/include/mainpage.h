/*! \mainpage CSCI 3081 Delivery Simulation Project

# Introduction

## Simulation Setup
### Obtaining Code
To obtain code, clone the repo onto a local machine.

    git clone https://github.umn.edu/umn-csci-3081-s21/repo-iter3-10-24.git

The project code can be found inside the project directory inside the repository.

### Compiling Code
Code currently does not need configuration, can be compiled and ran right away. It requires Docker to create a docker image,
and Doxygen to generate documentation.
First, build and run the Docker image:

    cd repo-iter3-10-24
    bin/build-env.sh
    bin/run-env.sh

Then, change directory to the project folder, and run make clean followed by make.

    cd project
    make clean
    make

At this point, the code has been compiled and the simulation is ready to execute.

### Executing Simulation
The simulation can be started by entering bin/run.sh from the project directory.

    cd project
    bin/run.sh

To run various scenes, the bin/run.sh command can be provided with an optional argument, equal to one of
- scenes/all_features_no_recharge_station.json
- scenes/all_features.json
- scenes/beeline_drone.json
- scenes/custom_low_battery.json
- scenes/drone_and_robot_many_deliveries.json
- scenes/drone_and_robot.json
- scenes/drone_cant_carry_two_packages.json
- scenes/drone_delivers_two_packages_at_once_for_different_customers.json
- scenes/drone_delivers_two_packages_at_once.json
- scenes/drone_low_battery_a.json
- scenes/drone_low_battery_b.json
- scenes/parabolic_drone.json
- scenes/robot_cant_carry_two_packages.json
- scenes/robot_delivers_two_packages_at_once.json
- scenes/robot.json
- scenes/smart_drone.json
- scenes/two_customers.json
- scenes/two_packages_two_drones.json
- scenes/umn.json

After the bin/run.sh command is executed, open to a web browser and navigate to the link http://127.0.0.1:8081/ to see the
simulation in action.

Once the simulation has run to completion, press the "Kill Simulation" button found on the webpage, or type Ctrl-C in the
terminal to kill the process.

## About The Code

### General Overview
As a result of provided code, a map of the University of Minnesota can be generated in the simulation and figures representing various entities
can be added to the map when initialized properly. The entity types added to the scene for deliverable 1 are customer, package,
and drone. The goal is to have drones go to packages, pick them up, and deliver them to the proper destinations.  In iteration 2, robots were added
(like drones, but can only move on the ground) and battery functionality was implemented.  Further, more complex scheduling involving multiple packages,
customers, and deliver-ers (drones and robots) were added.

The code written handles this task through the facade of the delivery_simulation class. First, entities are created, then they
are added to the map, and then a delivery is scheduled. The creation of entities is done through a composite factory pattern--
using the classes CompositeFactory, DroneFactory, RobotFactory, CustomerFactory, BatteryFactory, and PackageFactory. Upon creation, each entity's details
(position, direction, id, name, etc.) are initialized properly. See the section below for more information on the composite
factory pattern. Provided code then adds the created entities to the simulation on the map in the browser.

Deliveries are scheduled as a result of ScheduleDelivery being called in delivery_simulation, and this consequently picks a
drone/robot with the least number of ongoing deliveries to handle the delivery, and assigns a package a customer and a drone/robot a
package. The package is able to get the information about its destination and the drone/robot can subsequently get the destination as well.

Throughout the simulation running, the Update function in the delivery_simulation class is called every every few milliseconds.
This Update function in delivery_simulation cycles through all the entities in the system, and calls each Drone/Robot's Update function.
It also checks if each package is delivered (drones/robots and packages have a status_ attribute to them, representing their current states).
If a package is delivered, it sets it to a location off the map.

The drone/robot's Update function handles each drone/robot status individually: Idle, FlyingToPackage, and DeliveringPackage. Robots (and drones
that are assigned the "smart" route, which is generated using the provided A* algorithm) follows roads and avoids collisions with buildings while
updating its position. After they reache their package, they "pick it up" by always setting the package position to their current position while
delivering the package.  Once they reach the customer, they set the package status to delivered which allows for the Update function of
delivery_simulation to take the package off the map. The drone/robot then changes its status to Idle and remains in the same location unless there
is another package to deliver, which in that case it starts moving and repeats the cycle again.

Robots (package transporters that were restricted to moving on the ground) were only implemented in deliverable 2. Additional paths for drones were
also implemented through the use of a strategy pattern.  The path options are now smart (as in deliverable 1), beeline (drone moves up to avoid running
into buildings, travels to directly above destination, then moves down to destination), and parabolic (drone moves in a parabola, reaching a given max height,
in order to reduce risk of clipping buildings but maintaining greater efficiency.

Battery functionality was implemented in Iteration 2. Both drone and robot have a battery. Battery drains only if the entity is moving. How fast the
battery drains is dependent on the movement speed. Unless battery_capacity is passed as a part of JSON string, all batteries are initialized with the
default capacity of 10000. When an entity runs out of battery, it stops moving and its state changes to idle. If it was carrying a package, the package
is dropped on the ground level and rescheduled for delivery with the next available entity.

### Discussion of the Composite Factory Pattern
The code makes use of the Composite Factory Pattern to produce entities. This means that the entities are created through a
composite factory, which holds a list of component factories.

A benefit of the composite factory pattern is the reinforcement of OCP--the Open Close Principle. The composite factory class
and member factory classes are closed for modification and don't need to be modified to work, but the design is open for
expansion in that more factories can be added afterwards to expand on the functionality of the code. The factory pattern is
also not too difficult to implement.

However, the composite factory pattern can end up being unnecessarily cumbersome with the creation of many new classes for
each entity, especially if the entity creation process is quite simple. In the case of this project with this iteration, the
DroneFactory, CustomerFactory, and PackageFactory classes were quite simple, and the creation of each entity could have been
handled with very few lines in a much more concise manner using a concrete factory.

![Composite Factory Diagram](../CompositeFactoryUML.PNG "Composite Factory Diagram")


### Discussion of Other Factory Patterns

There are two other factory patterns that were discussed in class, the Simple (Concrete) Factory Pattern and the Abstract
Factory Pattern.

The simple factory pattern is quite easy to implement, and can have very compact code. All of the entities will be created as
a result of iterating through a switch statement on the type of entity to create, and each case will create an entity. For
example, code similar to that below can be made to emulate a simple factory:

    switch(JsonHelper::GetString(details, "type")) {
        case "drone" :
            return new Drone(details);
            break;
        case "package" :
            return new Package(details);
            break;
        case "customer" :
            return new Customer(details);
            break;
        default :
            return nullptr;
    }

This design does have drawbacks, however. It violates OCP, as it is not closed to modification. Every time a new entity is
added to the project design, the switch statement will need to be modified. Additionally, if the creation of entities is
more complex, then the switch statement can get quite complex and confusing. However, for a simple case of entity creation
where the number of entities will not change over time, the simple factory design can work well. This can work for solely
deliverable 1 of the project, but is not a good idea given that more entities will be added in the future.

An example UML diagram of a simple factory is provided below:

![Simple Factory Diagram](../SimpleFactoryUML.PNG "Simple Factory Diagram")

Abstract factory patterns allow for pushing the creation of objects into subclasses, and lets the program use polymorphism
during runtime. It allows for the different entities to be isolated from each other in the code, and, like other factory
designs, can help hide how the objects are created from the outside clients using the code.

However, the addition of more entities can get quite complex as there are multiple interfaces to modify and take care of.
The code can become unnecessarily complex as well, requiring many interfaces for potentially a simple creation task, as in
this iteration.

An example UML diagram of an abstract factory is provided below. To allow for legibility, the contents of the classes were
removed.

![Abstract Factory Diagram](../AbstractFactoryUML.PNG "Abstract Factory Diagram")

### Using The Strategy Pattern
We added an IStrategy class (strategies.cc, strategies.h, and IStrategy.h (interface)) that hold the strategy pattern class and
three concrete strategies (SmartPath, BeelinePath, and ParabolicPath).  Then, we added a IStrategy*
member attribute to each Drone and Robot, and gave it a specific type based on the information taken
from the JSON.  This allowed for abstracting the different paths into code that didn't take up space
in the implementation of Drone, and is accessible by any package transporter.  Moreover, using Strategy
Pattern here makes it easy to modify the pathing algorithms, add different types of paths, and more.
Resources I used included Piazza, the Lab 14 writeup, and a document posted to Canvas by a TA (Tushar Gowda).

The strategy pattern allows for greater flexibility while significantly reducing the amount of code needed
for the implementation. The strategy pattern allowed us to easily set up the drone path based on the
provided arguments.

An UML diagram of the strategy pattern implemented in our project is provided below.

![Strategy Pattern Diagram](../StrategyPattern.png "Strategy Pattern Diagram")

We struggled most with the parabolic path, and it required some working through the math independently and
double-checking that our types (float vs int) were correct before we were able to implement successfully.

### Observer Pattern Design Discussion
To my astonishment, my code for the observers worked first try. I was shocked, as were my groupmates. Refactoring took place
in order to clean up repeated code, and the creation of helper functions in json_helper.h was the largest change.

The observer tracks any changes in the status of the observed subjects (drones, robots, packages). Then,
observer creates notifications for any interested parties once the onserved subjects' status changes.
In our implementation, we onserve all of the entities and get notifications both through webpage and the
console. This allows us to get the current status of the entities alonside any potential problems that they
might have encountered. Additionally, the observer pattern allows customers to know the status of their
delivery (in real-world scenario).

An UML diagram of the observer pattern implemented in our project is provided below.

![Observer Pattern Diagram](../ObserverPattern.png "Observer Pattern Diagram")

## Enhancing and Extending the Package Delivery System

Our team decided to extend Drone and Robot functionality. We modified our code,
so Drones and Robots now have carrying capacity, and each package has a weight.
Both of these arguments can be passed as JSON arguments. Otherwise, they are set
to default. The default for package weight is 2 kg, while the default for Drone
and Robot carrying capacity is 10 kg and 25 kg, respectively. The drones and the
robots can now carry multiple packages as long as they don’t exceed their maximum
carrying capacity. In case if the total weight of multiple packages is greater
than the maximum carrying capacity, the entity will deliver the packages one by one.
If a single package has a weight greater than the maximum carrying capacity of an
entity, the package will not be delivered.

Additionally, we created maximum speed for entities. If the maximum speed argument
is present in the JSON file, we will set the entities’ max speed to the value.
Otherwise, it defaults to 30 m/s. If the speed is higher than the maximum speed
allowed, the speed will be set to maximum speed instead. Both max speed and speed
arguments are positive decimals and reflect how fast the entity moves.

## Team Documentation

### Team Members

Ayush Ram (ram00009): Development Lead

Jacob Rice (rice0296): Project Manager

Aniket Nuthalapati (nutha010): Scheduler

Denis Rybkin (rybki001): Reporter

### Team Meetings

For Iteration 2, First Deliverable, our team had three separate meetings. The first meeting was on Saturday,
March 27th, 2021. During this meeting, we discussed our roles within the team and performed the initial setup
of the project repository. The second meeting was on Monday, March 28th, 2021. For this meeting, we split
priorities between all the group members and started working on implementing the project. The third meeting
happened on Thursday, April 1st, 2021. During this meeting, we shared the project's progress and outlined the
future directions for the final deliverable.

For Iiteration 2, Second Deliverable, we had two separate meetings and were keeping in touch regarding different parts of the
iteration for the project's duration. We had our first meeting on March 31st, 2021. We discussed the
implementation of the robot class, observer pattern, and additional google tests during that meeting.
Our second meeting was on April 16th, 2021. We discussed the implementation of the battery functionality,
the strategy pattern, changes to the tests and the documentation, and the bugs that we encountered while
implementing the project. Additionally, we utilized Discord throughout the duration of the project to get
additional feedback on our implementations.

For Deliverable 3, we had two meetings on Saturday, April 24th, 2021 and Thursday, April 29th, 2021.
For the first meeting, we discussed the feature that we want to implement and for the second meeting
we discussed the progress and obstacles we encountered. Additionally, we were constantly in touch
through Discord regarding the progress of the project, including modifications to functionality,
addition of tests, debugging and documentation.

### Tasks and Priorities

Priority Level 1: Ayush Ram

Priority Level 2: Jacob Rice

Priority Level 3: Aniket Nuthalapati

Priority Level 4: Denis Rybkin

Extending the Package Delivery System: Every Team Member

Additionally, every team member participated in creating and resolving project issues, code reviews and merges.

### Contributions

#### Ayush Ram:
- Lead the development of the project
- Cleaned up Iteration 1 code
- Added missing tests from Iteration 1
- Implemented priority 1 (adding robots, tests for robots, ability for multiple drones/robots to deliver packages)
- Contributed to documentation
- Updated UML for Iteration 2
- Updated UML for Iteration 3
- Participated in Testing and debugging
- Refactored the code for better readability and increased performance

#### Jacob Rice:
- Managed the team and the progress of the project
- Implemented priority 2 (observer pattern)
- Added tests for observer pattern
- Contributed to documentation
- Implemented functionality to carry multiple packages
- Updated weight and max weight functionality
- Participated in testing and debugging

#### Aniket Nuthalapati:
- Scheduled meetings and events for the project development sessions
- Implemented priority 3 (strategy pattern)
- Added tests for strategy pattern
- Contributed to documentation
- Implemented tests for new functionality
- Participated in discussion and development of new features
- Participated in testing and debugging

#### Denis Rybkin:
- Documented and reported the progress of the project
- Implemented priority 4 (battery functionality)
- Added tests for battery functionality
- Contributed to documentation
- Updated speed and max speed functionality
- Participated in testing and debugging
- Created custome scenes
- Modified documentation for Deliverable 3
- Participated in testing and debugging

### Assesment of team Members

#### Ayush Ram:
- Jacob Rice: Fully contributed
- Aniket Nuthalapati: Fully contributed
- Denis Rybkin: Fully contributed

#### Jacob Rice:
- Ayush Ram: Fully contributed
- Aniket Nuthalapati: Fully contributed
- Denis Rybkin: Fully contributed

#### Aniket Nuthalapati:
- Ayush Ram: Fully contributed
- Jacob Rice: Fully contributed
- Denis Rybkin: Fully contributed

#### Denis Rybkin:
- Ayush Ram: Fully contributed
- Jacob Rice: Fully contributed
- Aniket Nuthalapati: Fully contributed

## Known Issues/Bugs

For some of the simulations with multiple drone/robot entities, no routes are displayed before the entity
picks up the package. The source of this bug is unknown, and it is speculated to be a front-end related bug.

When a drone/robot runs out of battery, it drops the package to the ground level. However, the model of the
box remains suspended in the air, even though its actual position is updated to be on the ground level.
Tried multiple approaches to update the visuals, but it remains suspended anyway. Suspect that it is related
to the fron-end implementation.

*/
