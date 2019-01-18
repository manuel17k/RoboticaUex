/*
 *    Copyright (C)2019 by YOUR NAME HERE
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
    void getTags(int numTags);


public slots:
	void compute();

private:
	InnerModel *innerModel;
    std::vector<QVec> listTags;//Lista tags del escenario
    enum State {SEARCH, WAIT};
    State state = State::SEARCH;
    int current;
            struct Tags{
		QMutex mutex;
        int id;
		float x;
        float y;
		float z;
		bool activo = true;
		Tags(){};
		

		bool getActivo(){
			QMutexLocker m(&mutex);
			return activo;		
		}

		void setActivo(){
			QMutexLocker m(&mutex);
			activo = true;		
		}

		bool insertarTag(int id, float coordX, float coordY, float coordZ){
			QMutexLocker m(&mutex);
			bool insert = false;
            id = id;
			x = coordX;
            y = coordY;
			z = coordZ;
			activo = false;
			insert = true;
			return insert;
		}
		
		std::list<float> extraerCoord(){
			QMutexLocker m(&mutex);
			std::list<float> tag;
            tag.push_front(z);
            tag.push_front(y);
            tag.push_front(x);
			tag.push_front(id);
            for(int i=0;i<tag.size();i++){
                 std::cout<<"Paso.."<<tag.front()<<std::endl;
            }
			return tag;
		}
   
	};
	Tags t;

};

#endif
