
# C++ Maze Pathfinder

A universtiy project written in C++ that solves a given maze using the DFS algorithm.

## Additional Information

Cells along the path may also contain pieces of food that can be consumed.
Currently, the project does not take into account the requirement to consume all the food available inside a maze before reaching the final destination.

NOTE: Start and End values will be automatically be determined if not provided upon the creation of custom maze text files.
## Custom Mazes (.txt)

For testing and creating custom maze text files:
- First line must include the desired width and height Ex. "4 3"  or "7 7"
- Maze generation key:
    - 0 - Open
    - 1 - Wall
    - 2 - Start
    - 4 - End
    - 8 - Food

##### Include new text file as a command line argument and you're all set!
## Usage/Examples

```
7 7
2 0 0 1 0 0 0
0 1 0 1 0 1 0
0 1 0 1 0 1 0
0 1 0 1 0 1 0
0 1 0 0 0 1 0
0 1 1 1 1 1 0
0 0 0 0 0 0 4

```

![App Screenshot](https://imgur.com/a/exQ3mN5)

```
3 3
0 1 1
0 1 0
1 0 0

```

![App Screenshot](https://imgur.com/V3WQo8Z)

## To Do

- Allow for a variety in pathfinding algorithm options

- Require and test the accuracy of consuming all the food in a maze before completion

