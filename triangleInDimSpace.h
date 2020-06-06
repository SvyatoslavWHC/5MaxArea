#ifndef TRIANGLEINDIMSPACE_H
#define TRIANGLEINDIMSPACE_H

#include <cmath>
#include <iostream>
#include <vector>

class triangleInDimSpace
{
        public:

        //Конструкторы

            triangleInDimSpace()
            {
                for(int i = 0; i < 3; i++)
                {
                    arrPoint[i].setter( 0.0 , 0.0 );
                }
                count++;
                ex1st = 0;
            }

            triangleInDimSpace(double x1, double y1, double x2,
                                        double y2, double x3, double y3)
            {
                arrPoint[0].setter(x1,y1);
                arrPoint[1].setter(x2,y2);
                arrPoint[2].setter(x3,y3);
                count++;
                ex1st = this->checkExistenceTriangle();
            }

            triangleInDimSpace(const double *ptrArrP)
            {
                for(int i = 0; i < 6; i=+2)
                    {
                        arrPoint[i/2].setter(ptrArrP[i], ptrArrP[i+1]);
                    }
                count++;
                ex1st = this->checkExistenceTriangle();
            }

        //Функции

            void setPointArrTr(const double *ptrArrP)
            {
                arrPoint[0].setter(ptrArrP[0],ptrArrP[1]);
                arrPoint[1].setter(ptrArrP[2],ptrArrP[3]);
                arrPoint[2].setter(ptrArrP[4],ptrArrP[5]);
                ex1st = this->checkExistenceTriangle();
            }

            void setPointArrTr(std::vector<double>& ptrArrP, int nowCounter)
            {
                arrPoint[0].setter(ptrArrP.at(nowCounter),ptrArrP.at(nowCounter+1));
                arrPoint[1].setter(ptrArrP.at(nowCounter+2),ptrArrP.at(nowCounter+3));
                arrPoint[2].setter(ptrArrP.at(nowCounter+4),ptrArrP.at(nowCounter+5));
                ex1st = this->checkExistenceTriangle();
            }

            double returnArea()
            {
                if(ex1st)
                {
                    calcLenght();
                    calcArea();
                    return area;
                }
                else
                {
                    return 0;
                }
            }

            // Статичные функции
            static int getCount()
            {
                return count;
            }

            static int getCount(triangleInDimSpace& Triangle)
            {
                return Triangle.count;
            }

            static void returnArrAreas(triangleInDimSpace* arrTriangle, double* arrAreas)
            {
                int count = triangleInDimSpace::getCount();
                for(int i = 0;i < count; i++)
                {
                    arrAreas[i] = arrTriangle[i].returnArea();
                }
            }

            private:

            //Классы
            class pointInDimSpace
            {
                private:
                    double x,y;

                public:

                //Конструкторы

                    pointInDimSpace()
                    {
                            this->x=0.0;
                            this->y=0.0;
                    }

                    pointInDimSpace(const double &x, const double &y)
                    {
                        this->x = x;
                        this->y = y;
                    }

                //Функции

                    void setter(const double &x, const double &y)
                    {
                        this->x = x;
                        this->y = y;
                    }

                    double dottedDistance(pointInDimSpace *point) // Расчитать растояние
                    {
                        double dist = sqrt((point->x - this->x)
                                            +
                                            (point->y - this->y));
                        return dist;
                    }

                    double getX() {
                        return x;
                    }

                    double getY() {
                        return y;
                    }
            };

            //Пременные

                pointInDimSpace arrPoint[3];
                double arrTrLenght[3];
                double area;
                static int count;
                bool ex1st;

            //Скрытые функции

                void calcLenght()
                {
                    arrTrLenght[0] = sqrt(pow(( arrPoint[1].getX() - arrPoint[0].getX() ), 2) + pow(( arrPoint[1].getY() - arrPoint[0].getY() ), 2));
                    arrTrLenght[1] = sqrt(pow(( arrPoint[2].getX() - arrPoint[1].getX() ), 2) + pow(( arrPoint[2].getY() - arrPoint[1].getY() ), 2));
                    arrTrLenght[2] = sqrt(pow(( arrPoint[0].getX() - arrPoint[2].getX() ), 2) + pow(( arrPoint[0].getY() - arrPoint[2].getY() ), 2));
                }

                void calcArea()
                {
                    double halfPerimeter = ((arrTrLenght[0] + arrTrLenght[1] + arrTrLenght[2])/2);
                    area = sqrt(halfPerimeter * (halfPerimeter-arrTrLenght[0]) * (halfPerimeter - arrTrLenght[1]) * (halfPerimeter - arrTrLenght[2]));
                }

                bool checkExistenceTriangle()
                {
                    calcLenght();

                    if (arrTrLenght[0] > 0 && arrTrLenght[1] > 0 && arrTrLenght[2] > 0)
                    {
                        if (arrTrLenght[0] + arrTrLenght[1] > arrTrLenght[2])
                        {
                            if (arrTrLenght[1] + arrTrLenght[2] > arrTrLenght[0])
                            {
                                if (arrTrLenght[2] + arrTrLenght[0] > arrTrLenght[1])
                                {
                                    return true;
                                }
                            }
                        }
                    }
                    return false;
                }

            };

// Инициализация статической переменной
int triangleInDimSpace::count = 0;


#endif // TRIANGLEINDIMSPACE_H
