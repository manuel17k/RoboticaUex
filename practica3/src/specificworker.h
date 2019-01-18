/*
 *    Copyright (C)2018 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
       \brief
       @author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(MapPrx& mprx);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
	void setPick(const Pick &myPick);

public slots:
	void compute();

private:
	InnerModel *innerModel;

	int coordIniRobX;
	int coordIniRobZ;
	
	struct Target{
		QMutex mutex;
		float x;
		float z;
		bool activo = false;
		Target(){};
		

		bool getActivo(){
//			QMutexLocker m(&mutex);
			return activo;		
		}

		void setActivo(){
			QMutexLocker m(&mutex);
			activo = true;		
		}

		bool insertarCoord(float coordX, float coordY){
			QMutexLocker m(&mutex);
			bool insert = false;			
			x = coordX;
			z = coordY;
			activo = false;
			insert = true;
			return insert;
		}
		
		std::pair<float , float > extraerCoord(){
			QMutexLocker m(&mutex);
			std::pair<float, float> tar;
			tar.first = x;
			tar.second = z;
			return tar;
		}
		
		bool enDestino(float coordX, float coordY){
            if(coordX == x && coordY == z){
                return true;
            }
            return false;
        }
	};
	Target t;
};

#endif
