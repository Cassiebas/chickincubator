#include "HarryPlotter"
#include "gnuplot-iostream.h"

Plotter::Plotter() {
}

Plotter::~Plotter() {
}

void Plotter::AddPoint(const double x, const double y) {
    AddPoint({x,y});
}

void Plotter::AddPoint(const int x, const int y) {
    AddPoint((double)x, (double)y);
}

void Plotter::AddPoint(const point p) {
    data.push_back(p);
    if (p.first < min.first)
        min.first = p.first;
    if (p.second < min.second)
        min.second = p.second;
    if (p.first > max.first)
        max.first = p.first;
    if (p.second > max.second)
        max.second = p.second;
}

void Plotter::AddPoints(const std::vector<double> x, const std::vector<double> y) {
    for (double d_x : x) { //d_ for datatype
        for (double d_y : y) {
            AddPoint({d_x, d_y});
        }
    }
}

void Plotter::AddPoints(const std::vector<int> x, const std::vector<int> y) {    
    for (int i_x : x) { //d_ for datatype
        for (int i_y : y) {
            AddPoint(i_x, i_y);
        }
    }
}

void Plotter::AddPoints(const std::vector<point> p) {
    for (point p_p : p) {
        data.push_back(p_p);
    }
}

bool Plotter::ResizePlot(const int width, const int height) { //resizes what data is shown
    
    return true;
}

std::string Plotter::DoubleToString(double value) {
    std::ostringstream origin;
    origin << value;
    std::string str = origin.str();
    return str;
}

void Plotter::ExportAsPNG(const std::string path, const std::string filename, const std::string xLabel, const std::string yLabel, const std::string lineLabel, const point resolution) {
    Gnuplot plot;
    plot << "set xrange [" << DoubleToString(min.first) << ":" << DoubleToString(max.first) << "]\nset yrange [" << DoubleToString(min.second) << ":" << DoubleToString(max.second) << "]\n";
    plot << "set xlabel '" << xLabel << "'\n";
    plot << "set ylabel '" << yLabel << "'\n";
    plot << "$DATA << EOD\n";  
    for (unsigned int i = 1; i < data.size(); i++) { 
        plot << DoubleToString(data.at(i-1).first) << " " << DoubleToString(data.at(i-1).second) << " " 
             << DoubleToString(data.at(i).first) << " " << DoubleToString(data.at(i).second) << "\n";
    }
    plot << DoubleToString(data.at(data.size()-1).first) << " " << DoubleToString(data.at(data.size()-1).second) << " " 
     << DoubleToString(data.at(data.size()-1).first) << " " << DoubleToString(data.at(data.size()-1).second) << "\n";
    plot << "EOD\n";
    // << plot.file1d((std::vector<std::pair<double, double>>)data)
    // plot << "plot $DATA with lines title '" << filename << "'\n";
    plot << "set term 'pngcairo'\n" <<
             "set output '" << path << filename << ".png'\n" <<
            //  "replot\n" <<
             "plot $DATA with lines title '" << lineLabel << "'\n" <<
             "unset output\n";

    // std::cout << (std::string)"set xrange [" << DoubleToString(min.first) << ":" << DoubleToString(max.first+1) << "]\nset yrange [" << DoubleToString(min.second) << ":" << DoubleToString(max.second+1) << "]\n";
    // std::cout << "$DATA << EOD\n"; 
    // for (unsigned int i = 1; i < data.size(); i++) { 
    //     std::cout << DoubleToString(data.at(i-1).first) << " " << DoubleToString(data.at(i-1).second) << " " 
    //               << DoubleToString(data.at(i).first) << " " << DoubleToString(data.at(i).second) << "\n";
    // }
    // std::cout << DoubleToString(data.at(data.size()-1).first) << " " << DoubleToString(data.at(data.size()-1).second) << " " 
    //  << DoubleToString(data.at(data.size()-1).first) << " " << DoubleToString(data.at(data.size()-1).second) << "\n";
    // std::cout << "EOD\n";
    // // std::cout << "plot $DATA with lines title '" << filename << "'\n";
    // std::cout << "set term 'pngcairo'\n" <<
    //          "set output '" << path << filename << ".png'\n" <<
    //         //  "replot\n" <<
    //          "plot $DATA with lines title '" << filename << "'\n" <<
    //          "unset output\n";
}
