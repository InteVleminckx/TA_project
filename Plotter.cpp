//
// Created by inte.vleminckx on 11/05/2021.
//

#include "Plotter.h"

Plotter::Plotter(vector<long> &TFA, vector<long> &BRZ, string vergelijkingsType)
{

    string path = "../" + vergelijkingsType + "comparison.html";

    plot.open(path);
    createHTML(TFA, BRZ, vergelijkingsType);
    plot.close();
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
    plot << "\t\t\t\t\t" << "interval:" << "1," << "\n";
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

    //table style
    plot << "<style> \n";
    plot << "\t" << ".styled-table\n";
    plot << "\t" << "{\n";
    plot << "\t\t" << "border-collapse: collapse;\n";
    plot << "\t\t" << "margin: 25px 0;\n";
    plot << "\t\t" << "font-size: 0.9em;\n";
    plot << "\t\t" << "font-family: sans-serif;\n";
    plot << "\t\t" << "min-width: 98vw;\n";
    plot << "\t\t" << "background-color: #32373a;\n";
    plot << "\t\t" << "color: white;\n";
    plot << "\t\t" << "text-align: center;\n";
    plot << "\t\t" << "border-radius: 10px 10px 10px 10px;\n";
    plot << "\t\t" << "overflow: hidden;\n";
    plot << "\t\t" << "box-shadow: 0 0 20px rgba(0,0,0,0.25);\n";
    plot << "\t" << "}\n";

    plot << "\t" << ".styled-table thead tr\n";
    plot << "\t" << "{\n";
    plot << "\t\t" << "background-color: #32373a;\n";
    plot << "\t\t" << "color: white;\n";
    plot << "\t\t" << "text-align: center;\n";
    plot << "\t\t" << "font-weight: bold;\n";
    plot << "\t\t" << "font-size: 18px;\n";
    plot << "\t" << "}\n";

    plot << "\t" << ".styled-table th,\n";
    plot << "\t" << ".styled-table td\n";
    plot << "\t" << "{\n";
    plot << "\t\t" << "padding: 12px 15px;\n";
    plot << "\t" << "}\n";

    plot << "\t" << ".styled-table tbody tr\n";
    plot << "\t" << "{\n";
    plot << "\t\t" << "border-bottom: 1px solid white;\n";
    plot << "\t" << "}\n";

    plot << "</style> \n";

    //table
    plot << "<table class=\"styled-table\">\n";
    plot << "\t" << "<thead>\n";
    plot << "\t" << "<tr>\n";
    plot << "\t\t" << "<th>Number of minimized DFA's</th>\n";
    plot << "\t\t" << "<th>Table filling algoritme</th>\n";
    plot << "\t\t" << "<th>Brzozowski algoritme</th>\n";
    plot << "\t" << "</tr>\n";
    plot << "\t" << "</thead>\n";
    plot << "\t" << "<tbody>\n";

    createTable(TFA, BRZ);

    plot << "\t" << "</tbody>\n";
    plot << "</table>\n";

    plot << "<body>\n";
    plot << "<div id=\"chartContainer\" style=\"height: 370px; width: 99%;\"></div>\n";
    plot << "<script src=\"https://canvasjs.com/assets/script/canvasjs.min.js\"></script>\n";

    //einde body
    plot << "</body> \n";
    //einde html
    plot << "</html> \n";

}

void Plotter::createCoordinates(vector<long> &points)
{
    for (int i = 0; i < points.size(); ++i)
    {
        if (i != points.size()-1)
        {
            plot << "\t\t\t\t\t\t" << "{ x:" << to_string(i+1) << ", y: " << to_string(points[i]) << "}, \n";
        }
        else
        {
            plot << "\t\t\t\t\t\t" << "{ x:" << to_string(i+1) << ", y: " << to_string(points[i]) << "} \n";
        }
    }
}

void Plotter::createTable(vector<long> &TFA, vector<long> &BRZ)
{

    int maxLength = max(TFA.size(), BRZ.size());

    for (int i = 0; i < maxLength; ++i)
    {
        plot << "\t" << "<tr>\n";

        plot << "\t\t" << "<td>" << i << "</td>\n";

        if (i < TFA.size()) plot << "\t\t" << "<td>" << TFA[i] << "</td>\n";
        else plot << "\t\t" << "<td>" << " " << "</td>\n";

        if (i < BRZ.size()) plot << "\t\t" << "<td>" << BRZ[i] << "</td>\n";
        else plot << "\t\t" << "<td>" << " " << "</td>\n";
        plot << "\t" << "</tr>\n";
    }

}

