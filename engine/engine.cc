#include "engine.h"


img::EasyImage generate_2DImage(const ini::Configuration &configuration) {
    string inputFile;
    vector<double> color;
    vector<double> backgroundColor;
    int size = 0;
    // parsen van .ini bestand
    size = configuration["General"]["size"].as_int_or_die();
    backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    inputFile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();

    L2Dsysteem a = L2Dsysteem();
    std::list<Line2D> lines = a.parse(inputFile, color);
    return draw2DLines(lines, size, backgroundColor, false);
}

img::EasyImage generate_3DImage(const ini::Configuration &configuration) {
    int nrFigures;
    //vector<double> color;
    vector<double> backgroundColor;
    vector<double> eye;

    int size = 0;
    // parsen van .ini bestand
    size = configuration["General"]["size"].as_int_or_die();
    backgroundColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    eye = configuration["General"]["eye"].as_double_tuple_or_die();

    L3Dsysteem a = L3Dsysteem();
    std::list<Line2D> lines;

    if (configuration["General"]["type"].as_string_or_die() == "ZBuffering") {
        lines = a.parse(configuration, nrFigures, eye, true); // hier hebben we enkel de figuren nodig, niet de lijnen
        Figures3D figuren = a.figuren3D;
        return drawTriangles(size, backgroundColor, figuren);
    }
    else {
        lines = a.parse(configuration, nrFigures, eye, false);
    }
    if (configuration["General"]["type"].as_string_or_die() == "ZBufferedWireframe") {
        return draw2DLines(lines, size, backgroundColor, true); // zbuf lijnen
    }
    else {
        return draw2DLines(lines, size, backgroundColor, false); // lijnen zonder zbuf
    }
}

img::EasyImage generate_image(const ini::Configuration &configuration)
{
    string type = configuration["General"]["type"].as_string_or_die();

    if (type == "2DLSystem") {
        return generate_2DImage(configuration);
    }
    else if (type == "Wireframe" || type == "ZBufferedWireframe") {
        return generate_3DImage(configuration);
    }
    else if (type == "ZBuffering") {
        return generate_3DImage(configuration);
    }

}


//int runEngine(int argc, char const* argv[])
//{
//        int retVal = 0;
//        try
//        {
//                for(int i = 1; i < argc; ++i)
//                {
//                        ini::Configuration conf;
//                        try
//                        {
//                                std::ifstream fin(argv[i]);
//                                fin >> conf;
//                                fin.close();
//                        }
//                        catch(ini::ParseException& ex)
//                        {
//                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
//                                retVal = 1;
//                                continue;
//                        }
//
//                        img::EasyImage image = generate_image(conf);
//                        if(image.get_height() > 0 && image.get_width() > 0)
//                        {
//                                std::string fileName(argv[i]);
//                                std::string::size_type pos = fileName.rfind('.');
//                                if(pos == std::string::npos)
//                                {
//                                        //filename does not contain a '.' --> append a '.bmp' suffix
//                                        fileName += ".bmp";
//                                }
//                                else
//                                {
//                                        fileName = fileName.substr(0,pos) + ".bmp";
//                                }
//                                try
//                                {
//                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
//                                        f_out << image;
//
//                                }
//                                catch(std::exception& ex)
//                                {
//                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
//                                        retVal = 1;
//                                }
//                        }
//                        else
//                        {
//                                std::cout << "Could not generate image for " << argv[i] << std::endl;
//                        }
//                }
//        }
//        catch(const std::bad_alloc &exception)
//        {
//    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
//    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
//    		//(Unless of course you are already consuming the maximum allowed amount of memory)
//    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
//		//mark the test as failed while in reality it just needed a bit more memory
//                std::cerr << "Error: insufficient memory" << std::endl;
//                retVal = 100;
//        }
//        return retVal;
//}

void save_image(std::string iniFilename) {
    ini::Configuration conf;
    std::ifstream fin(iniFilename);
    fin >> conf;
    fin.close();
    img::EasyImage image = generate_image(conf);

    if(image.get_height() > 0 && image.get_width() > 0)
    {
            std::string fileName(iniFilename);
            std::string::size_type pos = fileName.rfind('.');
            if(pos == std::string::npos)
            {
                    //filename does not contain a '.' --> append a '.bmp' suffix
                    fileName += ".bmp";
            }
            else
            {
                    fileName = fileName.substr(0,pos) + ".bmp";
            }
            try
            {
                    std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                    f_out << image;

            }
            catch(std::exception& ex)
            {
                    std::cerr << "Failed to write image to file: " << ex.what() << std::endl;

            }
    }
    else
    {
            std::cout << "Could not generate image" << std::endl;
    }

}
