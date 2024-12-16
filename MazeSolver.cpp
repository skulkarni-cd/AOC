#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <queue>
#include <vector>
#include <cmath>

struct MazeSize
{
  int width;
  int height;
};

struct Point
{
  int x, y;
};

enum Direction
{
  BEGIN = -1,
  X,
  Y
};

MazeSize ReadMaze(const std::string& fName, std::string& buf)
{
  std::ifstream file(fName);

  buf = std::move(std::string((std::istreambuf_iterator<char>(file)), 
    std::istreambuf_iterator<char>()));

  MazeSize size;
  size.height =  size.width = (int)std::sqrt(buf.length());

  return size;
}

Direction direction(const Point& p1, const Point& p2)
{
  if (p1.x == p2.x)
    return X;

  return Y;
}

int solveMaze(const std::string& maze, const Point& src, const Point& dest, const MazeSize& size)
{
  std::queue<Point> Queue;
  std::vector<bool> visited(maze.length(), false);

  int cost = 0;

  Queue.push(src);

  Point prevPoint = src;
  Direction prevDir = BEGIN;

  while (!Queue.empty())
  {
    Point point = Queue.front();
    Queue.pop();

    if (point.x == dest.x && point.y == dest.y)
      break;

    // neighbours
    std::vector<Point> neighbours(4, {-1, -1});
    
    if (point.x < size.width - 1)
      neighbours[0] = {point.x + 1 , point.y};

    if (point.x > 0)
      neighbours[1] = {point.x - 1, point.y};
    
    if (point.y < size.height - 1)
      neighbours[2] = {point.x, point.y + 1};
    
    if (point.y > 0)
      neighbours[3] = {point.x, point.y - 1};

    for (int i = 0; i < 4; ++i)
    {
      // out of bounds neighbours or boundary
      if (neighbours[i].x == -1 || neighbours[i].y == -1)
        continue;

      int idx = size.width * neighbours[i].y + neighbours[i].x;
      if (maze[idx] == '.' && !visited[idx])
      {
        visited[idx] = true;
        Queue.push(neighbours[i]);

        Direction currentDir = direction(prevPoint, neighbours[i]);

        if (prevDir != currentDir && prevDir != BEGIN)
        {
          cost = cost + 1000;
        }
        else
          cost = cost + 1;

        prevDir = currentDir;
        prevPoint = neighbours[i];
      }
    }
  }

  return cost;
}

int main()
{
  std::string maze;
  MazeSize size = ReadMaze("16-Dec-input.txt", maze);

  Point src, dest;

  int pos = maze.find('S', 0);

  src.x = pos % size.width;
  src.y = pos / size.width;

  pos = maze.find('E', 0);

  dest.x = pos % size.width;
  dest.y = pos / size.width;

  int cost = solveMaze(maze, src, dest, size);

  std::cout << cost << std::endl;

  return 0;
}
