#ifndef ejemplo1_H
#define ejemplo1_H

#include <IceUtil/Timer.h>


#include <QtGui>
#include "ui_counterDlg.h"

class ejemplo1 : public QWidget, public Ui_Counter
{
public:
    QTimer timer;
    int contador = 0;
   
Q_OBJECT
    public:
        ejemplo1();
        virtual ~ejemplo1();
        
    public slots:
            void doButton();
             void cuenta();
};
 
        

#endif // ejemplo1_H
