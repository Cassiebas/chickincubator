#include <iostream>
#include "HarryPlotter"

int main() {
    Plotter plot;
    plot.AddPoint({0,0});
    plot.AddPoint({1,1});
    plot.AddPoint({2,2});
    plot.AddPoint({3,3});
    plot.AddPoint({4,4});
    plot.ExportAsPNG();
    return 0;
}