#ifndef HARRYPLOTTER_HPP
#define HARRYPLOTTER_HPP

#include <vector>
#include <string>
#include <limits>

using point = std::pair<double, double>;
class Plotter {
    private:
        const std::string name = "Harry";
        int width, height;
        point min = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()}, max = {0,0};
        std::vector<point> data;
        std::string DoubleToString(double value);
    public:
        Plotter();
        ~Plotter();
        void AddPoint(const double x, const double y);
        void AddPoint(const int x, const int y);
        void AddPoint(const point p);
        void AddPoints(const std::vector<double> x, const std::vector<double> y);
        void AddPoints(const std::vector<int> x, const std::vector<int> y);
        void AddPoints(const std::vector<point> p);
        bool ResizePlot(const int width, const int height);
        void ExportAsPNG(const std::string path = "./", const std::string filename = "export", const std::string xLabel = "x", const std::string yLabel = "y", const std::string lineLabel = "f(x)", const point resolution = {1920, 1080});
};

#endif