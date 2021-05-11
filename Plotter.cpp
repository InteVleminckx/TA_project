//
// Created by inte.vleminckx on 11/05/2021.
//

#include "Plotter.h"

Plotter::Plotter(vector<double> &TFA, vector<double> &BRZ)
{
    string path = "../snelheidsvergelijking.html";

    plot.open(path);
    createHTML(TFA, BRZ);
    plot.close();
}

void Plotter::createHTML(vector<double> &TFA, vector<double> &BRZ)
{

    string htmlTabTitle = "Speed comparison";
    string titleXas = "Number of minimisations";
    string titleYas = "Minimisation time";
    string plotTitle = "Speed comparison";
    string lineColorTFA = "#00beff";
    string lineColorBRZ = "#59ff00";
    string markerColorTFA = "#00518f";
    string markerColorBRZ = "#0d5800";
    string markerType = "circle";
    string lineNameTFA = "Table filling algorithm";
    string lineNameBRZ = "Brzozoswki algorithm";


    plot << "<!DOCTYPE HTML>\n";
    plot << "<html>\n";
    plot << "\n";

    //Geeft de tab van de html een title
    plot << "<head>\n";
    plot << "\t<title>\n";
    plot << "\t\t" << "\"" <<  htmlTabTitle << "\"" <<  "\n";
    plot << "\t</title>\n";
    plot << "</head>\n";
    plot << "\n";

    //Beginnen aan het script voor de chart te tekenen
    plot << "<head>\n";
    plot << "\t<script>\n";
    plot << "\t\t" << "window.onload = function () {" << "\n";

    //maken nieuw object aan
    plot << "\t\t\t" << "var chart = new CanvasJS.Chart(\"chartContainer\", {" << "\n";

    //toevoegen van de char options
    plot << "\t\t\t\t" << "animationEnabled: true," << "\n";
    plot << "\t\t\t\t" << "theme: \"dark2\"," << "\n";

    //Title van de chart
    plot << "\t\t\t\t" << "title:{" << "\n";
    plot << "\t\t\t\t\t" << "text:" << "\"" << plotTitle << "\"" << "\n";
    plot << "\t\t\t\t" << "}," << "\n";

    //X-as informatie
    plot << "\t\t\t\t" << "axisX:{" << "\n";
    plot << "\t\t\t\t\t" << "title:" << "\"" << titleXas << "\"," << "\n";
    plot << "\t\t\t\t\t" << "includeZero:" << "true," << "\n";
    plot << "\t\t\t\t\t" << "crosshair: {" << "\n";
    plot << "\t\t\t\t\t\t" << "enabled:" << "true," << "\n";
    plot << "\t\t\t\t\t\t" << "snapToDataPoint:" << "true" << "\n";
    plot << "\t\t\t\t\t" << "}" << "\n";
    plot << "\t\t\t\t" << "}," << "\n";

    //Y-as informatie
    plot << "\t\t\t\t" << "axisY:{" << "\n";
    plot << "\t\t\t\t\t" << "title:" << "\"" << titleYas << "\"," << "\n";
    plot << "\t\t\t\t\t" << "includeZero:" << "true," << "\n";
    plot << "\t\t\t\t\t" << "crosshair: {" << "\n";
    plot << "\t\t\t\t\t\t" << "enabled:" << "true" << "\n";
    plot << "\t\t\t\t\t" << "}" << "\n";
    plot << "\t\t\t\t" << "}," << "\n";

    //toolTip
    plot << "\t\t\t\t" << "toolTip:{" << "\n";
    plot << "\t\t\t\t\t" << "shared:" << "true" << "\n";
    plot << "\t\t\t\t" << "}," << "\n";

    //legende
    plot << "\t\t\t\t" << "legend:{" << "\n";
    plot << "\t\t\t\t\t" << "verticalAlign:" << "\"bottom\"," << "\n";
    plot << "\t\t\t\t\t" << "horizontalAlign:" << "\"center \"," << "\n";
    plot << "\t\t\t\t\t" << "dockInsidePlotArea:" << "false" << "\n";
    plot << "\t\t\t\t" << "}," << "\n";

    //data
    //TFA
    plot << "\t\t\t\t" << "data: [{" << "\n";
    plot << "\t\t\t\t\t" << "type:" << "\"line\"," << "\n";
    plot << "\t\t\t\t\t" << "showInLegend:" << "true," << "\n";
    plot << "\t\t\t\t\t" << "name:" << "\"" << lineNameTFA << "\"," << "\n";
    plot << "\t\t\t\t\t" << "markerType:" << "\"" << markerType << "\"," << "\n";
    plot << "\t\t\t\t\t" << "markerColor:" << "\"" << markerColorTFA << "\"," << "\n";
    plot << "\t\t\t\t\t" << "color:" << "\"" << lineColorTFA << "\"," << "\n";
    plot << "\t\t\t\t\t" << "dataPoints: [" << "\n";

    //toevoegen van de TFA waardes
    createCoordinates(TFA);

    plot << "\t\t\t\t\t" << "]" << "\n";
    plot << "\t\t\t\t" << "}," << "\n";

    plot << "\t\t\t\t" << "{" << "\n";

    //BRZ
    plot << "\t\t\t\t\t" << "type:" << "\"line\"," << "\n";
    plot << "\t\t\t\t\t" << "showInLegend:" << "true," << "\n";
    plot << "\t\t\t\t\t" << "name:" << "\"" << lineNameBRZ << "\"," << "\n";
    plot << "\t\t\t\t\t" << "markerType:" << "\"" << markerType << "\"," << "\n";
    plot << "\t\t\t\t\t" << "markerColor:" << "\"" << markerColorBRZ << "\"," << "\n";
    plot << "\t\t\t\t\t" << "color:" << "\"" << lineColorBRZ << "\"," << "\n";
    plot << "\t\t\t\t\t" << "dataPoints: [" << "\n";

    //toevoegen van de BRZ waardes
    createCoordinates(BRZ);

    plot << "\t\t\t\t\t" << "]" << "\n";
    plot << "\t\t\t\t" << "}]" << "\n";

    //sluiten van options
    plot << "\t\t" << "});" << "\n";

    //Renderchart
    plot << "\t\t" << "chart.render();" << "\n";
    plot << "\t" << "}" << "\n";

    //Einde van het script
    plot << "\t</script>\n";
    plot << "</head>\n";
    plot << "<body>\n";
    plot << "<div id=\"chartContainer\" style=\"height: 370px; width: 100%;\"></div>\n";
    plot << "<script src=\"https://canvasjs.com/assets/script/canvasjs.min.js\"></script>\n";

    //einde body
    plot << "</body> \n";
    //einde html
    plot << "</html> \n";

}

void Plotter::createCoordinates(vector<double> &points)
{
    for (int i = 0; i < points.size(); ++i)
    {
        if (i != points.size()-1)
        {
            plot << "\t\t\t\t\t\t" << "{ x:" << to_string(i) << ", y: " << to_string(points[i]) << "}, \n";
        }
        else
        {
            plot << "\t\t\t\t\t\t" << "{ x:" << to_string(i) << ", y: " << to_string(points[i]) << "} \n";
        }
    }
}