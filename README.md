Visualization and movement of primitive objects and camera in 3D space. Made with OpenGL.

A lot of the code came from ogldev tutorials: https://github.com/emeiri/ogldev

Tested on ubuntu 22.04.

## Setup and Configuration

0 - Clone the repo: git clone `git clone https://github.com/albud187/math_viz.git`

1a - Install dependancies using docker: Clone and setup the `ros-admin` docker image from https://github.com/albud187/ros-admin
This docker image is setup for C++ and python development focusing on ROS2 and OpenGL. It has all dependancies for this repo.
After cloning the `ros-admin` repo, edit the `dockerrun.sh` to volume mount this repository, then run the container using  `sh dockerrun.sh`


1b - Install dependancies without using docker: alternatively, if you don't want to use that docker image, you can just install dependancies as follows:

```
sudo apt update
sudo apt install -y g++ make freeglut3 freeglut3-dev libglew-dev libglew2.2 libmagick++-dev libassimp-dev libglfw3 libglfw3-dev libmeshoptimizer-dev libmeshoptimizer1d
sudo apt-get install -y libglfw3 libglfw3-dev
```

2 - Build the project. 
- Change to project directory and create `build` directory :
`cd math_viz`
`mkdir build`

- Navigate to build folder `math_viz/build`:
`cd build`

- Initialize cmake. On  `math_viz/build` execute:
`cmake ..`

- Build project. On `math_viz/build` execute:
`cmake --build .`

3 - Run the project.
- while on `math_viz/build` execute:
`./math_viz`

 You should see somehting that looks like this:
