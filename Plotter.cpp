//
// Created by inte.vleminckx on 11/05/2021.
//

#include "Plotter.h"

Plotter::Plotter(vector<long> &TFA, vector<long> &BRZ, string vergelijkingsType)
{

    string path = "../" + vergelijkingsType + "comparison.html";

    fPlot.open(path);
    createHTML(TFA, BRZ, vergelijkingsType);
    fPlot.close();
}

void Plotter::createHTML(vector<long> &TFA, vector<long> &BRZ, string &vergelijkingsType)
{

    string htmlTabTitle = vergelijkingsType + " comparison";
    string titleXas = "Number of minimized DFA's";
    string titleYas;

    if (vergelijkingsType == "Speed") titleYas = "Minimisation time";
    if (vergelijkingsType == "Memory") titleYas = "Memory usage";

    string plotTitle = vergelijkingsType + " comparison";
    string lineColorTFA = "#00beff";
    string lineColorBRZ = "#59ff00";
    string markerColorTFA = "#00518f";
    string markerColorBRZ = "#0d5800";
    string markerType = "circle";
    string lineNameTFA = "Table filling algorithm";
    string lineNameBRZ = "Brzozoswki algorithm";


    fPlot << "<!DOCTYPE HTML>\n";
    fPlot << "<html>\n";
    fPlot << "\n";

    //Geeft de tab van de html een title
    fPlot << "<head>\n";
    fPlot << "\t<title>\n";
    fPlot << "\t\t" << "\"" << htmlTabTitle << "\"" << "\n";
    fPlot << "\t</title>\n";
    fPlot << "</head>\n";
    fPlot << "\n";

    //Beginnen aan het script voor de chart te tekenen
    fPlot << "<head>\n";
    fPlot << "\t<script>\n";
    fPlot << "\t\t" << "window.onload = function () {" << "\n";

    //maken nieuw object aan
    fPlot << "\t\t\t" << "var chart = new CanvasJS.Chart(\"chartContainer\", {" << "\n";

    //toevoegen van de char options
    fPlot << "\t\t\t\t" << "animationEnabled: true," << "\n";
    fPlot << "\t\t\t\t" << "theme: \"dark2\"," << "\n";

    //Title van de chart
    fPlot << "\t\t\t\t" << "title:{" << "\n";
    fPlot << "\t\t\t\t\t" << "text:" << "\"" << plotTitle << "\"" << "\n";
    fPlot << "\t\t\t\t" << "}," << "\n";

    //X-as informatie
    fPlot << "\t\t\t\t" << "axisX:{" << "\n";
    fPlot << "\t\t\t\t\t" << "title:" << "\"" << titleXas << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "includeZero:" << "true," << "\n";
    fPlot << "\t\t\t\t\t" << "interval:" << "1," << "\n";
    fPlot << "\t\t\t\t\t" << "crosshair: {" << "\n";
    fPlot << "\t\t\t\t\t\t" << "enabled:" << "true," << "\n";
    fPlot << "\t\t\t\t\t\t" << "snapToDataPoint:" << "true" << "\n";
    fPlot << "\t\t\t\t\t" << "}" << "\n";
    fPlot << "\t\t\t\t" << "}," << "\n";

    //Y-as informatie
    fPlot << "\t\t\t\t" << "axisY:{" << "\n";
    fPlot << "\t\t\t\t\t" << "title:" << "\"" << titleYas << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "includeZero:" << "true," << "\n";
    fPlot << "\t\t\t\t\t" << "crosshair: {" << "\n";
    fPlot << "\t\t\t\t\t\t" << "enabled:" << "true" << "\n";
    fPlot << "\t\t\t\t\t" << "}" << "\n";
    fPlot << "\t\t\t\t" << "}," << "\n";

    //toolTip
    fPlot << "\t\t\t\t" << "toolTip:{" << "\n";
    fPlot << "\t\t\t\t\t" << "shared:" << "true" << "\n";
    fPlot << "\t\t\t\t" << "}," << "\n";

    //legende
    fPlot << "\t\t\t\t" << "legend:{" << "\n";
    fPlot << "\t\t\t\t\t" << "verticalAlign:" << "\"bottom\"," << "\n";
    fPlot << "\t\t\t\t\t" << "horizontalAlign:" << "\"center \"," << "\n";
    fPlot << "\t\t\t\t\t" << "dockInsidePlotArea:" << "false" << "\n";
    fPlot << "\t\t\t\t" << "}," << "\n";

    //data
    //TFA
    fPlot << "\t\t\t\t" << "data: [{" << "\n";
    fPlot << "\t\t\t\t\t" << "type:" << "\"line\"," << "\n";
    fPlot << "\t\t\t\t\t" << "showInLegend:" << "true," << "\n";
    fPlot << "\t\t\t\t\t" << "name:" << "\"" << lineNameTFA << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "markerType:" << "\"" << markerType << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "markerColor:" << "\"" << markerColorTFA << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "color:" << "\"" << lineColorTFA << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "dataPoints: [" << "\n";

    //toevoegen van de TFA waardes
    createCoordinates(TFA);

    fPlot << "\t\t\t\t\t" << "]" << "\n";
    fPlot << "\t\t\t\t" << "}," << "\n";

    fPlot << "\t\t\t\t" << "{" << "\n";

    //BRZ
    fPlot << "\t\t\t\t\t" << "type:" << "\"line\"," << "\n";
    fPlot << "\t\t\t\t\t" << "showInLegend:" << "true," << "\n";
    fPlot << "\t\t\t\t\t" << "name:" << "\"" << lineNameBRZ << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "markerType:" << "\"" << markerType << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "markerColor:" << "\"" << markerColorBRZ << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "color:" << "\"" << lineColorBRZ << "\"," << "\n";
    fPlot << "\t\t\t\t\t" << "dataPoints: [" << "\n";

    //toevoegen van de BRZ waardes
    createCoordinates(BRZ);

    fPlot << "\t\t\t\t\t" << "]" << "\n";
    fPlot << "\t\t\t\t" << "}]" << "\n";

    //sluiten van options
    fPlot << "\t\t" << "});" << "\n";

    //Renderchart
    fPlot << "\t\t" << "chart.render();" << "\n";
    fPlot << "\t" << "}" << "\n";

    //Einde van het script
    fPlot << "\t</script>\n";
    fPlot << "</head>\n";

    //table style
    fPlot << "<style> \n";
    fPlot << "\t" << ".styled-table\n";
    fPlot << "\t" << "{\n";
    fPlot << "\t\t" << "border-collapse: collapse;\n";
    fPlot << "\t\t" << "margin: 25px 0;\n";
    fPlot << "\t\t" << "font-size: 0.9em;\n";
    fPlot << "\t\t" << "font-family: sans-serif;\n";
    fPlot << "\t\t" << "min-width: 98vw;\n";
    fPlot << "\t\t" << "background-color: #32373a;\n";
    fPlot << "\t\t" << "color: white;\n";
    fPlot << "\t\t" << "text-align: center;\n";
    fPlot << "\t\t" << "border-radius: 10px 10px 10px 10px;\n";
    fPlot << "\t\t" << "overflow: hidden;\n";
    fPlot << "\t\t" << "box-shadow: 0 0 20px rgba(0,0,0,0.25);\n";
    fPlot << "\t" << "}\n";

    fPlot << "\t" << ".styled-table thead tr\n";
    fPlot << "\t" << "{\n";
    fPlot << "\t\t" << "background-color: #32373a;\n";
    fPlot << "\t\t" << "color: white;\n";
    fPlot << "\t\t" << "text-align: center;\n";
    fPlot << "\t\t" << "font-weight: bold;\n";
    fPlot << "\t\t" << "font-size: 18px;\n";
    fPlot << "\t" << "}\n";

    fPlot << "\t" << ".styled-table th,\n";
    fPlot << "\t" << ".styled-table td\n";
    fPlot << "\t" << "{\n";
    fPlot << "\t\t" << "padding: 12px 15px;\n";
    fPlot << "\t" << "}\n";

    fPlot << "\t" << ".styled-table tbody tr\n";
    fPlot << "\t" << "{\n";
    fPlot << "\t\t" << "border-bottom: 1px solid white;\n";
    fPlot << "\t" << "}\n";

    fPlot << "</style> \n";

    //table
    fPlot << "<table class=\"styled-table\">\n";
    fPlot << "\t" << "<thead>\n";
    fPlot << "\t" << "<tr>\n";
    fPlot << "\t\t" << "<th>Number of minimized DFA's</th>\n";
    fPlot << "\t\t" << "<th>Table filling algoritme</th>\n";
    fPlot << "\t\t" << "<th>Brzozowski algoritme</th>\n";
    fPlot << "\t" << "</tr>\n";
    fPlot << "\t" << "</thead>\n";
    fPlot << "\t" << "<tbody>\n";

    createTable(TFA, BRZ);

    fPlot << "\t" << "</tbody>\n";
    fPlot << "</table>\n";

    fPlot << "<body>\n";
    fPlot << "<div id=\"chartContainer\" style=\"height: 370px; width: 99%;\"></div>\n";
    fPlot << "<script src=\"https://canvasjs.com/assets/script/canvasjs.min.js\"></script>\n";

    //einde body
    fPlot << "</body> \n";
    //einde html
    fPlot << "</html> \n";

}

void Plotter::createCoordinates(vector<long> &points)
{
    for (int i = 0; i < points.size(); ++i)
    {
        if (i != points.size()-1)
        {
            fPlot << "\t\t\t\t\t\t" << "{ x:" << to_string(i + 1) << ", y: " << to_string(points[i]) << "}, \n";
        }
        else
        {
            fPlot << "\t\t\t\t\t\t" << "{ x:" << to_string(i + 1) << ", y: " << to_string(points[i]) << "} \n";
        }
    }
}

void Plotter::createTable(vector<long> &TFA, vector<long> &BRZ)
{

    int maxLength = max(TFA.size(), BRZ.size());

    for (int i = 0; i < maxLength; ++i)
    {
        fPlot << "\t" << "<tr>\n";

        fPlot << "\t\t" << "<td>" << i+1 << "</td>\n";

        if (i < TFA.size()) fPlot << "\t\t" << "<td>" << TFA[i] << "</td>\n";
        else fPlot << "\t\t" << "<td>" << " " << "</td>\n";

        if (i < BRZ.size()) fPlot << "\t\t" << "<td>" << BRZ[i] << "</td>\n";
        else fPlot << "\t\t" << "<td>" << " " << "</td>\n";
        fPlot << "\t" << "</tr>\n";
    }

}

