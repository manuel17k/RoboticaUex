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

}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	try
	{
	
		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
		innerModel = std::make_shared<InnerModel>(par.value);
	}

	catch(std::exception e) { qFatal("Error reading config params"); }

	timer.start(Period);
	return true;
}

void SpecificWorker::compute( )
{
         RoboCompGenericBase::TBaseState robotState;
differentialrobot_proxy->getBaseState(robotState);
    
RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData(); //read laser data 

  innerModel->updateTransformValues("base", robotState.x, 0, robotState.z ,0, robotState.alpha, 0);

  switch( state )

 {

   case State::IDLE:

   if ( t.getActivo() == true )

    state = State::GOTO;

    break;

   case State::GOTO:

    gotoTarget();

    break;

   case State::BUG:

    bug();

    break;

  }

}

void SpecificWorker::gotoTarget()
{
    float vAvance;
    float vRot;
    std::pair<float, float> coord = t.extraerCoord();

    if( obstacle() == true)   // If ther is an obstacle ahead, then transit to BUG
    {
        state = State::BUG;
        return;
    }

    if(t.getActivo()==true){
        QVec rt = innerModel->transform("base", QVec::vec3(coord.first,0,coord.second), "world");
        float dist =rt.norm2();

    if( dist > 50)
    {
        vRot = atan2(rt.x(), rt.z());
    
    if(vRot > 0.5){
        vRot = 0.5;
    }
    
    if(vRot< -0.5){
        vRot= -0.5;
    }

    vAvance = 400;
    differentialrobot_proxy->setSpeedBase(vAvance,vRot);
        
    }else{
    state = State::IDLE;
    differentialrobot_proxy->setSpeedBase(0,0);
    t.setActivo();
    return;
    }
    }
}

void SpecificWorker::bug()

{ 
    
    float rot = 1.0;
      
    RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData(); //read laser data 
    
  std::sort( ldata.begin()+8, ldata.end()-8, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return a.dist < b.dist; });
  
  
  if (ldata[8].dist < 350 || ldata[ldata.size()-8].dist < 350){
    
    if (ldata[8].angle < 0)
      rot = 1.0;
    else
      rot = -1.0;
    
    differentialrobot_proxy->setSpeedBase(0, 0.3*rot);
  }
  else{
    differentialrobot_proxy->setSpeedBase(300, 0);
    usleep(200000);
    state = State::GOTO;
  }
  
  if (targetAtSight()){
    state = State::GOTO;
}
}

bool SpecificWorker::obstacle()

{
         
  RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData(); //read laser data 
 
  std::sort( ldata.begin()+8, ldata.end()-8, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return a.dist < b.dist; });

 if( ldata[8].dist < 350 || ldata[ldata.size()-8].dist < 350)
   return true;
 else
return false;
}

bool SpecificWorker::targetAtSight()

{    
    QPolygonF polygon;
       ldata = laser_proxy->getLaserData();

for (auto l : ldata)
{
   QVec lr = innerModel->laserTo("world", "laser", l.dist, l.angle);
   polygon << QPointF(lr.x(), lr.z());
}
std::pair<float, float> coord = t.extraerCoord();
QVec t = QVec::vec2(coord.first, coord.second);
return  polygon.containsPoint( QPointF(t.x(), t.z() ), Qt::WindingFill ); 

}

void SpecificWorker::setPick(const Pick &myPick)
{

    qDebug()<<myPick.x<<myPick.z;

	t.insertarCoord(myPick.x, myPick.z);
    t.setActivo();
}
