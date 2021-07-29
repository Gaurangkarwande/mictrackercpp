#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVTKImageIO.h"

#include <vtkImageViewer2.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTIFFReader.h>
#include <vtkObjectFactory.h>
#include <vtkImageAppend.h>



using namespace boost::system;
namespace filesys = boost::filesystem;
#ifndef USING_BOOST
#define USING_BOOST
#endif

using namespace cv;

template class std::vector<Mat>;


/*
 * Get the list of all files in given directory and its sub directories.
 *
 * Arguments
 *     dirPath : Path of directory to be traversed
 *     dirSkipList : List of folder names to be skipped
 *
 * Returns:
 *     vector containing paths of all the files in given directory and its sub directories
 *
 */
int main()
{
    std::string data_path = "/home/gaurang/My Projects/micTracker/OPCtracking_software_3D/Data";
    std::vector<std::string> listOfFiles = getAllFilesInDir(data_path);
    std::sort(listOfFiles.begin(), listOfFiles.end(), [](std::string a, std::string b){
        return std::stoi(a.substr(66, a.length() - 70)) < std::stoi(b.substr(66, b.length() - 70));
        //return std::stoi(a.substr(133, a.length() - 137)) < std::stoi(b.substr(133, b.length() - 137));
    });
    std::string multi_image_path = listOfFiles[0];
    std::string single_image_file = "/home/gaurang/Pictures/sample.png";
    std::string outputFileName = "../output.tiff";

    /*
    using PixelType=unsigned char;
    constexpr unsigned int Dimension= 3;
    using ImageType = itk::Image< PixelType, Dimension >;

    using ReaderType = itk::ImageFileReader< ImageType >;
    using WriterType = itk::ImageFileWriter< ImageType >;

    ReaderType::Pointer reader = ReaderType::New();
    WriterType::Pointer writer = WriterType::New();

    reader->SetFileName( multi_image_path);
    writer->SetFileName( outputFileName );

    writer->SetInput( reader->GetOutput() );

    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & err )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }
    */

    std::vector<Mat> mats;
    imreadmulti(multi_image_path, mats);

    vtkSmartPointer<vtkImageAppend> volume = vtkSmartPointer<vtkImageAppend>::New();
    //putInto3D(&volume, &mats);
    /*
    int sizeYRaw = *mats[0].size.p;
    int sizeXRaw = *mats[0].step.p;
    int sizeZRaw = static_cast<int>(mats.size());
    int sizeTRaw = static_cast<int>(listOfFiles.size());

    int rangeY[] = {105, 254};
    int rangeX[] = {150, 299};
    int rangeZ[] = {0, sizeZRaw - 1};
    int rangeT[] = {60, 79};

    int sizeY = rangeY[1] - rangeY[0] + 1;
    int sizeX = rangeX[1] - rangeX[0] + 1;
    int sizeZ = rangeZ[1] - rangeZ[0] + 1;
    int sizeT = rangeT[1] - rangeT[0] + 1;

    int pcSigma = 3;
    int minSize = 50;
    int maxSize = 10000;

    Mat img = mats[56];
    if(img.empty())
    {
        std::cout << "Could not read the image: " << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }
     */

    return 0;
}

/*
void putInto3D(vtkSmartPointer<vtkImageAppend> volume, std::vector<Mat> *mats)
{
    //vtkSmartPointer<vtkImageAppend> volume =
     //       vtkSmartPointer<vtkImageAppend>::New();

    volume->SetAppendAxis(2);

    for (int a = 0; a < mats->size(); a++)
    {

        //Convert OpenCV data to vtkImageData
        vtkSmartPointer<vtkImageData> outputVtkImage =
                vtkSmartPointer<vtkImageData>::New();
        outputVtkImage->ShallowCopy(convertCVMatToVtkImageData(mats[a], true));

        //Add the vtkImageData as input
        volume->AddInputData(outputVtkImage);
    }

    volume->Update();
    //render_2d_slices(volume);
}
 */