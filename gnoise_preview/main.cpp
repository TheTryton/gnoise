#include <iostream>
#include <chrono>
#include "preview_flow_chart/widget/preview_widget.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    preview_widget widget;
    widget.show();
    return app.exec();
}