#include "ejemplo1.h"

ejemplo1::ejemplo1(): Ui_Counter()
{
	setupUi(this);
	show();

 
        connect(button, SIGNAL(clicked()), this, SLOT(doButton()) );
        connect(&timer, SIGNAL(timeout()), this, SLOT(cuenta()) );
        timer.start(500);
}

ejemplo1::~ejemplo1()
{}

void ejemplo1::doButton()
{
	qDebug() << "click on button";
        timer.stop();
}


void ejemplo1::cuenta()
{
        contador++;
        lcdNumber->display(contador);
}

