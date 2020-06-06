#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <QString>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include "triangleInDimSpace.h"
#include <algorithm>

    class init
    {
        public:
        //Конструктор
        init(const int argc, const char **argv)
        {
            if(!(argv[0][0] == '.' && argv[0][1] == '/'))
            {
                nameProgram = argv[0];
            }else{
                nameProgram = argv[0];
                nameProgram.erase(0,2);
            }

            if(checkCountArg(argc, argv))
                        argument = std::string(argv[2]);
            else
            {
                std::cout << help1rst << std::endl;
                exit(-1);
            }
        }

        //Функции

        void startProgram()
        {
            analysis start_(argument);
            double* arr5MaxAreas = new double[5];
            int countMaxAreas = 0;
            start_.returnResult(arr5MaxAreas,countMaxAreas);
            coutResult(arr5MaxAreas,countMaxAreas);
            delete[] arr5MaxAreas;
        }

        void coutResult(double *arr, int &count)
        {
            std::cout << count;
            switch (count) {
                case 1:
                    std::cout  << " площадь треугольника:" << std::endl;
                    break;
                case 2:
                case 3:
                case 4:
                    std::cout  << " самых больших площади данных треугольников:" << std::endl;
                    break;
                case 5:
                    std::cout  << " самых больших площадей данных треугольников:" << std::endl;
                    break;
            }

            for(int i = 0;i < count; i++)
            {
                std::cout << "№" << (i+1) << " " << arr[i] << std::endl;
            }
        }
    private:
            //Переменные

            std::string argument;
            std::string nameProgram;
            const std::string help1rst = nameProgram + " [argument] <number>";

            //Класс

            class analysis
            {
                public:

                analysis(std::string path)
                {
                    /*
                     Работаю с файлом:
                        Открываю
                        Проверяю, что файл существует
                        считаю размер файла
                     */
                    fileTr.open(path);
                    if(!fileTr.is_open())
                    {
                        std::cout << "Файл не существует или недостаточно прав доступа" << std::endl;
                        exit(-3);
                    }

                    fileTr.seekg(0, std::ios::end); // считаю размер файла
                    int fileSize = fileTr.tellg();
                    /*
                    Считываю все символы из файла:
                    Перевожу курсор в начало
                    Проверяю считался ли файл
                    Закрываю файл
                    */
                    fileTr.seekg(0);
                    streamIn = new char[fileSize];

                    for(int i = 0; i < fileSize; i++) //Считываю символы из файла
                    {
                        fileTr.get(streamIn[i]);
                    }

                    if(fileTr.fail())
                    {
                        std::cout << "Ошибка числа не прочитаны" << std::endl;
                        exit(-4);
                    }

                    fileTr.close();
                    /*
                        Проверяю числа в
                    */
                    int countElements = calcCountElem(streamIn,fileSize);
                    if(!(countElements % 6 == 0)) //Проверка количества чисел в файле
                    {
                        std::cout << "Количество абсцисс и ординат не кратно 6. " << std::endl;
                        exit(-4);
                    }

                    QString str = QString(streamIn);
                    QRegExp reg = QRegExp("-\\d\\.\\d+|\\d+\\.\\d+|-\\d+|\\d+");
                    std::vector<double> vec;
                    int pos = 0;

                    while ((pos = reg.indexIn(str, pos)) != -1) {
                        std::string cap = reg.cap(0).toStdString();
                        vec.push_back(atof(cap.c_str()));
                        pos += reg.matchedLength();
                    }
                    arrTriangle = new triangleInDimSpace[vec.size()/6];
                    for(size_t i = 0; i < vec.size(); i=i+6) {
                        arrTriangle[(i/6)].setPointArrTr(vec,i);
                    }
                }

                void returnResult(double*& arr5MaxAreas, int &countAreas)
                {
                    int const countTr = triangleInDimSpace::getCount();
                    double arrAreas[countTr];
                    triangleInDimSpace::returnArrAreas(arrTriangle, arrAreas);
                    std::sort(arrAreas,arrAreas+countTr, forSortFunct);
                    countAreas = 5;
                    for (int i = 0; i < countAreas; i++)
                    {
                        if(arrAreas[i] <= 0.0)
                        {
                            countAreas = i;
                            break;
                        }
                    }
                    if(countAreas == 0)
                    {
                        std::cout << "Данные числа не образуют треугольников" << std::endl;
                        exit(-5);
                    }
                    else
                    {
                        delete[] arr5MaxAreas;
                        arr5MaxAreas = new double[countAreas];
                    }
                    arr5MaxAreas = new double[countAreas];
                    for (int i = 0; i < countAreas; i++)
                    {
                        {
                            arr5MaxAreas[i] = arrAreas[i];
                        }
                    }
                }

                ~analysis()
                {
                    delete[] streamIn;
                }

                private:
                    std::ifstream fileTr;
                    char *streamIn;
                    triangleInDimSpace *arrTriangle;

                    static bool forSortFunct(double a, double b) { return (a>b); } //Функция для сортировки

                    bool itNumber(const char &simbol) //Функция проверяет
                    {
                        if((int)simbol >= 48 && (int)simbol <= 57)
                                return true;
                        return false;
                    }

                    bool itPoint(const char &simbol)
                    {
                        if(simbol == '.')
                            return true;
                        return false;
                    }

                    int calcCountElem(const char *arr, const int SIZE) // Функция считает кол-во чисел в файле
                    {
                        int returnCount = 0;

                        for(int i = 0; i < SIZE; i++)
                        {
                            if((int)arr[i] >= 48 && (int)arr[i] <= 57)
                            {
                                continue;
                            }
                            else
                            {
                                if(i > 0)
                                {
                                    if(arr[i] != '.')
                                    {
                                        if((int)arr[i-1] >= 48 && (int)arr[i-1] <= 57)
                                        {

                                            returnCount++;
                                        }
                                    }
                                }
                            }
                        }

                        return returnCount;
                    }
            };

            bool checkCountArg(const int argc, const char **argv) //Функция проверяет кол-во элементов
            {
                switch(argc)
                {
                    case 3:
                        std::string argument1 = std::string(argv[1]);
                        if(argument1 == "-mA" || argument1 == "--maxArea")
                        {
                            return true;
                        }
                        break;
                }
                return false;
            }
        };

#endif // PROGRAM_H
