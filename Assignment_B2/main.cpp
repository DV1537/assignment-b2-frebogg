#include "functions.h"

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        std::ifstream myReadFile;
        myReadFile.open(argv[1]);

        if (myReadFile)
        {
            Shape *firstShape = nullptr;
            Shape *currentShape = nullptr;
            Figure fig;
            std::string line = "";

            int amountOfCoordinates = 0;
            int cordArrSize = 0;

            Coordinate *cordArr = new Coordinate[cordArrSize];

            while (getline(myReadFile, line))
            {
                double cordX = 0.0;
                double cordY = 0.0;

                int coordCounter = 0;

                std::istringstream iss(line);
                std::string currentText = "";

                while (iss >> currentText)
                {
                    if (ValidNumber(currentText))
                    {
                        double readNr = stod(currentText);
                        coordCounter += 1;

                        // Create a coordinate for every 2nd value
                        if ((coordCounter % 2) == 0)
                        {
                            cordY = readNr;
                            cordArrSize += 1;

                            AddCoordinateToArray(cordArr, cordX, cordY, cordArrSize);
                            amountOfCoordinates += 1;
                        }
                        else if ((coordCounter % 2) != 0)
                        {
                            cordX = readNr;
                        }
                    }
                    else
                    {
                        return 1;
                    }
                }

                if ((coordCounter % 2) != 0)
                {
                    return 1;
                }
                else if (amountOfCoordinates > 0 && ((coordCounter % 2) == 0))
                {
                    SetShape(currentShape, cordArr, amountOfCoordinates);
                    if (!firstShape)
                    {
                        firstShape = currentShape;
                    }
                    else
                    {
                        fig.AddShape(currentShape);
                    }

                    amountOfCoordinates = 0;
                    cordArrSize = 0;

                    if (cordArr)
                    {
                        delete[] cordArr;
                        cordArr = nullptr;
                    }
                }
            }

            myReadFile.close();
            if (firstShape)
            {
                const int amountOfClosestShapes = 3; // Just used for the assignment
                if (amountOfClosestShapes > 0 && fig.GetAmountOfShapes() >= amountOfClosestShapes)
                {
                    Shape **closestShapes = fig.GetClosest(firstShape, amountOfClosestShapes);

                    std::cout << "First shape: " << firstShape->CoordinatesToString() << '\n';
                    std::cout << amountOfClosestShapes << " closest shapes points" << '\n';

                    for (int i = 0; i < amountOfClosestShapes; i++)
                    {
                        std::cout << (i + 1) << "| " << closestShapes[i]->CoordinatesToString() << '\n';
                    }

                    delete[] closestShapes;
                    closestShapes = nullptr;
                }
                else
                {
                    return 1;
                }

                delete firstShape;
                firstShape = nullptr;
            }
        }
        else
        {
            return 1;
        }
    }

    return 0;
}
