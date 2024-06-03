
// Include all neccessary header files
#include <opencv2/opencv.hpp>
#include <iostream>

// Function to detect triangles
void detectTriangle(cv::Mat& image, const std::vector<cv::Point>& approx, int x, int y) 
{
    cv::putText(image, "Triangle", cv::Point(x-35, y-0.8), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
}


// Function to detect squares or rectangles or trapeziums
void detectSquareRectangleTrapezium(cv::Mat& image, const std::vector<cv::Point>& approx, int x, int y) 
{
    // Calculates the bounding rectangle for contour approximation
    // In simple words, calculates the smallest rectangle which encloses the shape
    cv::Rect boundingRect = cv::boundingRect(approx);
    double aspectRatio = static_cast<double>(boundingRect.width)/boundingRect.height;

    // Calculating the Euclidean Distance between two contour approximation points
    double dist1 = cv::norm(approx[0] - approx[1]);
    double dist2 = cv::norm(approx[2] - approx[3]);

    // If the distance between the opposite sides are not equal ---> Trapezium
    if (dist1 != dist2) 
    {
        cv::putText(image, "Trapezium", cv::Point(x-30, y-25), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    } 
    
    // If the aspect ratio is close to 1 ---> Square
    else if(std::abs(aspectRatio - 1) < 0.03) 
    {
        cv::putText(image, "Square", cv::Point(x-30, y-15), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    } 
    
    // Else ---> Rectangle
    else 
    {
        cv::putText(image, "Rectangle", cv::Point(x-35, y-5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    }
}


// Function to detect pentagons
void detectPentagon(cv::Mat& image, int x, int y) 
{
    cv::putText(image, "Pentagon", cv::Point(x-35, y-5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
}


// Function to detect hexagons
void detectHexagon(cv::Mat& image, int x, int y) 
{
    cv::putText(image, "Hexagon", cv::Point(x-25, y-5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
}


// Function to detect octagons or rectangles with curved surface edges
void detectOctagonOrRectangle(cv::Mat& image, const std::vector<cv::Point>& approx, int x, int y) 
{
    // Calculate the lengths of all sides
    std::vector<double> sideLengths;

    for (size_t j = 0; j < approx.size(); j++) 
    {
        /*
            For every vertex of the contour approximation
            v1 is calculated via current vertex - previous vertex
        */
        cv::Point v1 = approx[j] - approx[(j - 1 + approx.size()) % approx.size()];
        double length = cv::norm(v1);
        sideLengths.push_back(length);  
    }

    // Check if all side lengths are approximately equal
    bool isOctagon = true;
    double epsilon = 10.0;  // Threshold for side length difference

    for (size_t j = 0; j < sideLengths.size(); j++) 
    {
        double diff = std::abs(sideLengths[j] - sideLengths[0]);
        
        if (diff > epsilon) 
        {
            isOctagon = false;
            break;
        }
    }

    // If side lengths are approximately equal ---> Octagon
    if (isOctagon) 
    {
        cv::putText(image, "Octagon", cv::Point(x - 35, y - 5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    } 
    
    // If difference is not equal i.e., greater than threshold ---> Rectangle
    else 
    {
        cv::putText(image, "Rectangle", cv::Point(x - 35, y - 5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    }
}


// Function to detect circles or ellipses
void detectCircleEllipse(cv::Mat& image, const std::vector<cv::Point>& approx, int x, int y) 
{
    // Calculation of the minimum ellipse which covers the shape
    cv::RotatedRect ellipse = cv::fitEllipse(approx);

    // Aspect ratio is calculated on the basis of the min radius to maximum radius
    double ratio = std::min(ellipse.size.width, ellipse.size.height) / std::max(ellipse.size.width, ellipse.size.height);

    // If ratio comes closer to 1 ---> Circle 
    if (ratio >= 0.95 && ratio <= 1.05) 
    {
        cv::putText(image, "Circle", cv::Point(x-25, y-5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    } 

    // If not ---> Ellipse
    else 
    {
        cv::putText(image, "Ellipse", cv::Point(x-25, y-5), cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
    }
}


// Main function
int main() 
{
    // Read the image
    cv::Mat image = cv::imread("/home/kpit/Desktop/KPIT Genesis 2024/Mini Projects/Basic Shape Detection/Shape Detection/include/basicShapes.png");
    
    // Exception to handle image reading corner case
    if(image.empty()) 
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }

    // Coversion of image to Gray Scale in order simplify the object detection process
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY, 0);

    // Vector of contours to store the contours detected in the image
    std::vector<std::vector<cv::Point>> contours;

    // Vector to store the heirarchy of the contours
    std::vector<cv::Vec4i> hierarchy;

    // Finds the contours basis RETRE_TREE (full hierarchy) and stores it onto the contours and hierarchy vectors
    cv::findContours(grayImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    
    // Loop to process over every contour
    for(size_t i =0; i<contours.size(); i++) 
    {
        // Temporary storage to process over the current contour
        std::vector<cv::Point> contour = contours[i];
        std::vector<cv::Point> approx;

        // Approximates the polygonal curve of the current contour
        cv::approxPolyDP(contour, approx, 0.01*cv::arcLength(contour, true), true);

        // Stores the contour approximation on the grayscale image
        cv::drawContours(grayImage, std::vector<std::vector<cv::Point>>{approx}, 0, cv::Scalar(255, 255, 255), 5);

        // Calculates the moments of the contour approximation (centroid) in order to place the text within the shape
        cv::Moments M = cv::moments(approx);
        int x = static_cast<int>(M.m10 / M.m00);
        int y = static_cast<int>(M.m01 / M.m00);

        // If the approximation of the contour comes out to be 3 ---> Triangle
        if(approx.size() == 3) 
        {
            detectTriangle(image, approx, x, y);
        } 
        
        // If the approximation of the contour is 4 ---> Square OR Rectangle OR Trapezium
        else if(approx.size() == 4) 
        {
            detectSquareRectangleTrapezium(image, approx, x, y);
        } 
        
        // If the contour approximation comes out to be five ---> Pentagon
        else if(approx.size() == 5) 
        {
            detectPentagon(image, x, y);
        } 
        
        // If the contour approximation comes out to be six ---> Hexagon
        else if(approx.size() == 6) 
        {
            detectHexagon(image, x, y);
        } 
        
        // If the contour approximation comes out ot eight ---> Octagon OR Rectangle (with curved surface edges)
        else if(approx.size() == 8) 
        {
            detectOctagonOrRectangle(image, approx, x, y);
        } 
        
        // Else --> Circle OR Ellipse
        else 
        {
            detectCircleEllipse(image, approx, x, y);
        }
    }

    cv::imwrite("/home/kpit/Desktop/KPIT Genesis 2024/Mini Projects/Basic Shape Detection/include/DetectedShapes.png", image);
    cv::imshow("Original Image", image);
    cv::waitKey(0);
    return 0;
}
