#include "HarryPlotter.hpp"
#include "gnuplot-iostream.h"
#include <sstream>

Plotter::Plotter()
{
  singularLine.clear();
}

Plotter::~Plotter()
{
}

void Plotter::AddPoint(const double x, const double y, std::string lineName)
{
  AddPoint({x, y}, lineName);
}

void Plotter::AddPoint(const int x, const int y, std::string lineName)
{
  AddPoint((double)x, (double)y, lineName);
}

void Plotter::AddPoint(const point p, std::string lineName)
{
  if (lineName == "")
  {
    singularLine.push_back(p);
    // std::cout << "\t\tlineName empty\n";
  }
  else
  {
    // std::cout << "\t\tlineName not empty\n";
    data[lineName].push_back(p);
  }
  if (p.first < min.first)
    min.first = p.first;
  if (p.second < min.second)
    min.second = p.second;
  if (p.first > max.first)
    max.first = p.first;
  if (p.second > max.second)
    max.second = p.second;
}

void Plotter::AddPoints(const std::vector<double> x, const std::vector<double> y, std::string lineName)
{
  for (double d_x : x)
  { // d_ for data[lineName]type
    for (double d_y : y)
    {
      AddPoint({d_x, d_y}, lineName);
    }
  }
}

void Plotter::AddPoints(const std::vector<int> x, const std::vector<int> y, std::string lineName)
{
  for (int i_x : x)
  { // d_ for datatype
    for (int i_y : y)
    {
      AddPoint(i_x, i_y, lineName);
    }
  }
}

void Plotter::AddPoints(const std::vector<point> points, std::string lineName)
{
  for (point p : points)
  {
    AddPoint(p, lineName);
  }
}

std::string Plotter::DoubleToString(double value)
{
  std::ostringstream origin;
  origin << value;
  std::string str = origin.str();
  return str;
}

void Plotter::ExportToCSV(const std::string path, const std::string filename, const std::string lineLabel)
{
  std::vector<std::vector<double>> allData;
  std::vector<double> rowData;
  std::vector<std::string> lineNames;
  std::ofstream file(path + filename + ".csv");
  if (!singularLine.empty())
  {
    data[lineLabel] = singularLine; // std::map<std::string, std::vector<std::pair<double, double>>> data
  }
  for (std::pair<std::string, line> linePair : data)
  {
    lineNames.push_back(linePair.first);
  }
  for (unsigned int i = 0; i < data[lineNames.at(0)].size(); i++)
  {
    rowData.push_back(data[lineNames.at(0)].at(i).first);
    for (std::string lineName : lineNames)
    {
      rowData.push_back(data[lineName].at(i).second);
    }
    allData.push_back(rowData);
    rowData.clear();
  }
  for (std::vector<double> dataRow : allData)
  {
    for (double dataField : dataRow)
    {
      file << dataField << ",";
    }
    file << "\n";
  }
  file << std::endl;
  file.close();
}

void Plotter::ExportToPNG(const std::string path, const std::string filename, const std::string xLabel, const std::string yLabel, const std::string lineLabel, const point resolution)
{
  Gnuplot plot;
  std::stringstream plotString;
  std::vector<std::string> lineNames;
  ExportToCSV(path + "csv/", filename, lineLabel);
  if (!singularLine.empty())
  {
    data[lineLabel] = singularLine; // std::map<std::string, std::vector<std::pair<double, double>>> data
  }
  if (data.empty())
    return;
  for (std::pair<std::string, line> linePair : data)
  {
    lineNames.push_back(linePair.first);
    std::cout << "Linename : " << linePair.first << "\n";
  }
  plotString << "set xrange [" << DoubleToString(abs(max.first - min.first) > 1 ? min.first : 0) << ":" << DoubleToString(max.first)
             << "]\nset yrange [" << DoubleToString(min.second - ((abs(max.second - min.second) > 1 ? abs(max.second - min.second) * 0.1 : max.second * 0.01) + max.second == 0 ? 1 : 0)) // 10 percent of max extra in y range or if 0 add one to y range
             << ":" << DoubleToString(max.second + ((abs(max.second - min.second) > 1 ? abs(max.second - min.second) * 0.1 : max.second * 0.01) + max.second == 0 ? 1 : 0)) << "]\n"
             << "set xlabel '" << xLabel << "'\n"
             << "set ylabel '" << yLabel << "'\n"
             << "set term 'pngcairo'\n"
             << "set datafile separator ','\n"
             << "set output '" << path << filename << ".png'\n";
  plotString << "plot ";
  unsigned int column = 2;
  for (unsigned int i = 0; i < lineNames.size(); i++)
  {
    plotString << "'" << path << "csv/" << filename << ".csv'"
               << "using 1:" << column++ << " with lines title '" << lineNames.at(i) << "'"; //, '' using 1:3 with lines title 'Double'\n";
    if (i != lineNames.size() - 1)
    {
      plotString << ",";
    }
    else
    {
      plotString << "\n";
    }
  }
  plotString << "unset output\n";
  std::cout << plotString.str() << "\n";
  plot << plotString.str();
}
