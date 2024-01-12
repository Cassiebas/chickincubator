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
  if (data.size() > MAX_SIZE)
    data.erase(data.begin());
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
    // std::cout << "Linename : " << linePair.first << "\n";
  }
  if ((int)min.second == (int)max.second) {
    min.second *= 0.99;
  }
  if ((int)min.first == (int)max.first) {
    max.first *= 1.01;
  }
  plotString << "set xrange [" << std::to_string(min.first) << ":" << std::to_string(max.first)
             << "]\nset yrange [" << std::to_string(min.second)
             << ":" << std::to_string(max.second) << "]\n"
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
  // std::cout << plotString.str() << "\n";
  plot << plotString.str();
}
