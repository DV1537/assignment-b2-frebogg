#include "figure.h"

void Figure::AddShape(Shape *sArr)
{
    amountOfShapes += 1;
    Shape **tempShapes = new Shape *[amountOfShapes];

    for (int i = 0; i < (amountOfShapes - 1); i++)
    {
        tempShapes[i] = shapes[i];
    }
    tempShapes[amountOfShapes - 1] = sArr;

    if (shapes)
    {
        delete[] shapes;
        shapes = nullptr;
    }

    shapes = tempShapes;
}

std::string Figure::GetBoundingBox() const
{
    std::string textToRet = "";
    if (amountOfShapes > 0)
    {
        double minX = 0;
        double maxX = 0;

        double minY = 0;
        double maxY = 0;

        // Loop through all shapes and their coordinates
        for (int i = 0; i < amountOfShapes; i++)
        {
            if (shapes[i])
            {
                int cordAmount = shapes[i]->GetAmountOfCoordinates();
                Coordinate *tempCordsArr = new Coordinate[cordAmount];
                shapes[i]->CopyCoordinates(tempCordsArr);

                if (i == 0)
                {
                    minX = tempCordsArr[0].GetX();
                    maxX = tempCordsArr[0].GetX();

                    minY = tempCordsArr[0].GetY();
                    maxY = tempCordsArr[0].GetY();
                }
                for (int j = 0; j < cordAmount; j++)
                {
                    double x = tempCordsArr[j].GetX();
                    double y = tempCordsArr[j].GetY();
                    if (x > maxX)
                    {
                        maxX = x;
                    }
                    else if (x < minX)
                    {
                        minX = x;
                    }
                    if (y > maxY)
                    {
                        maxY = y;
                    }
                    else if (y < minY)
                    {
                        minY = y;
                    }
                }

                if (tempCordsArr)
                {
                    delete[] tempCordsArr;
                    tempCordsArr = nullptr;
                }
            }
        }

        std::stringstream stringS;

        double topLeftX = round(minX * 1000) / 1000;
        double topLeftY = round(maxY * 1000) / 1000;

        double bottomRightX = round(maxX * 1000) / 1000;
        double bottomRightY = round(minY * 1000) / 1000;
        stringS << "Corners of the bounding box in coordinates (X,Y) \n";
        stringS << "Top left corner: (" << topLeftX << ", " << topLeftY << ") \n";
        stringS << "Bottom right corner: (" << bottomRightX << ", " << bottomRightY << ") \n";

        textToRet = stringS.str();
    }
    else
    {
        textToRet = "No shapes, no bounding box.";
    }

    return textToRet;
}

Figure::~Figure()
{
    for (int i = 0; i < amountOfShapes; i++)
    {
        if (shapes[i])
        {
            delete shapes[i];
        }
    }

    if (shapes)
    {
        delete[] shapes;
    }
}

/*
    Returns sorted array with n closest shapes
*/
Shape **Figure::GetClosest(Shape *location, int n)
{
    if (amountOfShapes > 1)
    {
        RecursiveBubbleSort(*location, n, 0);
    }
    Shape **closestShapes = new Shape *[n];

    for (int i = 0; i < n; i++)
    {
        closestShapes[i] = shapes[i];
    }
    return closestShapes;
}

/*
    Calculates the closest distance between one of each shapes coordinates.
*/
double Figure::DistanceToShape(const Shape &s1, const Shape &s2)
{
    int locAmountOfCoordinates = s2.GetAmountOfCoordinates();
    Coordinate *locCoords = new Coordinate[locAmountOfCoordinates];
    s2.CopyCoordinates(locCoords);

    int cordAmount = s1.GetAmountOfCoordinates();
    Coordinate *shapeCoords = new Coordinate[cordAmount];
    s1.CopyCoordinates(shapeCoords);

    // Setup starting distance
    double distance = sqrt((pow((shapeCoords[0].GetX() - locCoords[0].GetX()), 2)) +
                           (pow((shapeCoords[0].GetY() - locCoords[0].GetY()), 2)));

    for (int j = 0; j < cordAmount; j++)
    {
        double x = shapeCoords[j].GetX();
        double y = shapeCoords[j].GetY();

        // Compare distance with every coordinate in location shape
        for (int k = 0; k < locAmountOfCoordinates; k++)
        {
            double currentDistance = sqrt((pow((x - locCoords[k].GetX()), 2)) +
                                          (pow((y - locCoords[k].GetY()), 2)));

            if (currentDistance < distance)
            {
                distance = currentDistance;
            }
        }
    }

    delete[] locCoords;
    locCoords = nullptr;

    delete[] shapeCoords;
    shapeCoords = nullptr;

    return distance;
}

/*
    Recursive version of Bubble sort
    Modified version of: https://www.geeksforgeeks.org/recursive-bubble-sort/

    Compares distance with each shape in the shapes array to another shape(loc).
    Sorts the array n number of times.
*/
void Figure::RecursiveBubbleSort(Shape &loc, int iterations, int currentIndex)
{
    if (currentIndex == (iterations)) // Return when we've reached the required amount of iterations
    {
        return;
    }
    double currentDistance = DistanceToShape(*shapes[currentIndex], loc);

    // Compares distance with current index and next index
    for (int i = currentIndex; i < (amountOfShapes - 1); i++)
    {
        double otherDistance = DistanceToShape(*shapes[i + 1], loc);
        if (currentDistance > otherDistance) 
        {
            // Swap
            Shape *temp = shapes[currentIndex];
            shapes[currentIndex] = shapes[i + 1];
            shapes[i + 1] = temp;
            currentDistance = DistanceToShape(*shapes[currentIndex], loc); // Update current distance
        }
    }

    RecursiveBubbleSort(loc, iterations, (currentIndex + 1));
}

int Figure::GetAmountOfShapes() const
{
    return amountOfShapes;
}