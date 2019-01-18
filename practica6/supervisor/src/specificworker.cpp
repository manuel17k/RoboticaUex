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
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{

}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	std::cout << "Destroying SpecificWorker" << std::endl;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
//       THE FOLLOWING IS JUST AN EXAMPLE
//	To use innerModelPath parameter you should uncomment specificmonitor.cpp readConfig method content
//	try
//	{
//		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
//		std::string innermodel_path = par.value;
//		innerModel = new InnerModel(innermodel_path);
//	}
//	catch(std::exception e) { qFatal("Error reading config params"); }
 
    
  innerModel = new InnerModel("/home/jorge/robocomp/files/innermodel/simpleworld.xml");

	timer.start(Period);


	return true;
}

void SpecificWorker::getTags(int numTags)
{
    for(int i=0; i<numTags; i++){
        QString id = "target0" + QString::number(i);
        QVec res = innerModel->transform("world",id);
        listTags.push_back(res);
        std::cout<<"target0"<<i<<std::endl;
        std::cout<<"RES.X: "<<res.x()<<std::endl;
        std::cout<<"RES.Y: "<<res.y()<<std::endl;
        std::cout<<"RES.Z: "<<res.z()<<std::endl;
    }
}

void SpecificWorker::compute()
{
    getTags(4);
    
    switch(state){
       
        
	case State::WAIT:
            qDebug()<< "WAIT";
            if(gotopoint_proxy->atTarget() == true){
                current = (current+1)%4 ;
                t.setActivo();
                gotopoint_proxy->stop();
                state = State::SEARCH;
            }else{
            	gotopoint_proxy->turn(0.5);
            }
            break;

    case State::SEARCH:
            qDebug()<< "SEARCH";
            if (!t.getActivo()){
            	state = State::WAIT;
            	gotopoint_proxy->stop();
            }
            break;
}
}



