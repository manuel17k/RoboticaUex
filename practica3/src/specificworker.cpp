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
		std::string innermodel_path = par.value;
		innerModel = new InnerModel(innermodel_path);
}
catch(std::exception e) { qFatal("Error reading config params"); }



	timer.start(Period);


	return true;
}


void SpecificWorker::compute( )
{
  //  const float threshold = 300; //millimeters
  //  float rot = 0.6;  //rads per second

    try
    {
       RoboCompGenericBase::TBaseState robotState;
       differentialrobot_proxy->getBaseState(robotState);
       
        RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data 
        std::sort( ldata.begin(), ldata.end(), [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return     a.dist < b.dist; }) ;  //sort laser data from small to large distances using a lambda function.
         
       
        if(t.getActivo()==true){
        innerModel->updateTransformValues("base", robotState.x, 0, robotState.z, 0, robotState.alpha, 0);
        Rot2D rot(robotState.alpha);

        
        
      QVec x = QVec::vec2(t.x, t.z);
		QVec r = QVec::vec2(robotState.x,robotState.z);
        QVec Y = rot.invert() * (x - r);
		qDebug() << Y;				
        
        float angle = atan2(Y.x(), Y.y());
        float mod =Y.norm2();
        
        qDebug() << "mod:" << mod <<endl;
        
         if( 50 > mod)
            {
                qDebug() << "mod dentro:" << mod <<endl;
                differentialrobot_proxy->setSpeedBase(0,0);
                t.setActivo();
                
            }
            else {
                differentialrobot_proxy->setSpeedBase(400,angle);
                }
    }
        
    }
    catch(const Ice::Exception &ex)
    {
        std::cout << ex << std::endl;
    }
}

//void SpecificWorker::compute()
//{
//	QMutexLocker locker(mutex);
	//computeCODE
// 	try
// 	{
// 		camera_proxy->getYImage(0,img, cState, bState);
// 		memcpy(image_gray.data, &img[0], m_width*m_height*sizeof(uchar));
// 		searchTags(image_gray);
// 	}
// 	catch(const Ice::Exception &e)
// 	{
// 		std::cout << "Error reading from Camera" << e << std::endl;
// 	}
//}

void SpecificWorker::setPick(const Pick &myPick)
{

    qDebug()<<myPick.x<<myPick.z;

	t.insertarCoord(myPick.x, myPick.z);
    t.setActivo();
//	qDebug() << myPick.x;	
//	qDebug() << myPick.z;	
}


