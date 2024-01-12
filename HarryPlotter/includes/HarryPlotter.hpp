#ifndef HARRYPLOTTER_HPP
#define HARRYPLOTTER_HPP

#include <vector>
#include <string>
#include <limits>
#include <map>

#define MAX_SIZE 1000

using point = std::pair<double, double>;
using line = std::vector<point>;
using plot = std::map<std::string, line>; // name, line data

class Plotter
{
private:
  const std::string name = "Harry";
  int width, height;
  point min = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()}, max = {0, 0};
  line singularLine;
  plot data;

public:
  Plotter();
  ~Plotter();
  void AddPoint(const double x, const double y, std::string lineName = "");
  void AddPoint(const int x, const int y, std::string lineName = "");
  void AddPoint(const point p, std::string lineName = "");
  void AddPoints(const std::vector<double> x, const std::vector<double> y, std::string lineName = "");
  void AddPoints(const std::vector<int> x, const std::vector<int> y, std::string lineName = "");
  void AddPoints(const std::vector<point> points, std::string lineName = "");
  void ExportToCSV(const std::string path = "csv/", const std::string filename = "export", const std::string lineLabel = "F(x)");
  void ExportToPNG(const std::string path = "./", const std::string filename = "export", const std::string xLabel = "x", const std::string yLabel = "y", const std::string lineLabel = "f(x)", const point resolution = {1920, 1080});
};

#endif