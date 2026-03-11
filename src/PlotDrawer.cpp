#include "PlotDrawer.h"

//::PlotDrawer(QCustomPlot* cp)
//    : binSize(60) //интервал в секундах
//    , autoRescale(true)
//{

    // this->customPlot = cp;

    // start = QDateTime(QDate(2026, 1, 1), QTime(9,59,50));

    // start.setTimeSpec(Qt::UTC);
    // startTime = start.currentSecsSinceEpoch();

    // initMainChart();
    // initVolChart();

    // customPlot->yAxis->setVisible(true);
    // customPlot->yAxis2->setVisible(true);
    // customPlot->xAxis->grid()->setVisible(true);
    // customPlot->yAxis->grid()->setVisible(true);

    // //линия текущей цены
    // // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    // mTag1 = new AxisTag(candlesticks->valueAxis());
    // mTag1->setPen(candlesticks->pen());

    // infLine = new QCPItemStraightLine(customPlot);

    // customPlot->setInteractions(/*QCP::iRangeDrag |*/ QCP::iRangeZoom);
    // customPlot->setMouseTracking(true);

    // mDraggingCustomItem = false;
//}


//void PlotDrawer::setNewRange(QWheelEvent* e)
//{
    // QCPRange range_y_good = customPlot->yAxis->range();

    // QCPRange range_y = customPlot->yAxis2->range();
    // double upper_tmp_y = range_y.upper;
    // double lower_tmp_y = range_y.lower;
    // if (e->angleDelta().y() < 0) //отдалить
    // {
    //     customPlot->yAxis2->setRange(lower_tmp_y*0.99,upper_tmp_y*1.01);
    // }
    // customPlot->yAxis->setRange(range_y_good);





    // if (isXAxisChosen) {
    //     QCPRange range_x = customPlot->xAxis->range();
    //     double lower_tmp_x = range_x.lower;
    //     double upper_tmp_x = range_x.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_x-=1000;
    //         upper_tmp_x+=1000;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_x+=1000;
    //         upper_tmp_x-=1000;
    //     }
    //     customPlot->xAxis->setRange(lower_tmp_x,upper_tmp_x);
    // } else if (isYAxisChosen) {
    //     QCPRange range_y = customPlot->yAxis2->range();
    //     double lower_tmp_y = range_y.lower;
    //     double upper_tmp_y = range_y.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_y*=0.99;
    //         upper_tmp_y*=1.01;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_y*=1.01;
    //         upper_tmp_y*=0.99;
    //     }
    //     customPlot->yAxis2->setRange(lower_tmp_y,upper_tmp_y);
    // } else {
    //     QCPRange range_x = customPlot->xAxis->range();
    //     double lower_tmp_x = range_x.lower;
    //     double upper_tmp_x = range_x.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_x-=1000;
    //         upper_tmp_x+=1000;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_x+=1000;
    //         upper_tmp_x-=1000;
    //     }
    //     customPlot->xAxis->setRange(lower_tmp_x,upper_tmp_x);
    //     QCPRange range_y = customPlot->yAxis2->range();
    //     double lower_tmp_y = range_y.lower;
    //     double upper_tmp_y = range_y.upper;

    //     if (e->angleDelta().y() < 0) //отдалить
    //     {
    //         lower_tmp_y*=0.99;
    //         upper_tmp_y*=1.01;
    //     }
    //     else //приблизить
    //     {
    //         lower_tmp_y*=1.01;
    //         upper_tmp_y*=0.99;
    //     }
    //     customPlot->yAxis2->setRange(lower_tmp_y,upper_tmp_y);
    // }

//    customPlot->replot();
//}

//void PlotDrawer::mouseMoved(QMouseEvent *e)
//{
    // double x_pixel = e->pos().x();
    // double x_value = customPlot->xAxis->pixelToCoord(x_pixel);

    // QString toolTipText;
    // isMouseOverBar(x_value);
    // {
    // }
    // // qDebug() << e->position().x();
    // // qDebug() << e->position().y();

    // //drag and drop
    // if (mDraggingCustomItem)
    // {
    //     QCPRange niceRange = customPlot->yAxis->range();

    //     double upper_y = customPlot->yAxis2->range().upper;
    //     double lower_y = customPlot->yAxis2->range().lower;

    //     double upper_x = customPlot->xAxis->range().upper;
    //     double lower_x = customPlot->xAxis->range().lower;

    //     double current_x = e->pos().x();
    //     double current_y = e->pos().y();

    //     double step_x = mDragStartPos.x() - current_x;
    //     double step_y = mDragStartPos.y() - current_y;

    //     customPlot->xAxis->setRange(lower_x - step_x, upper_x - step_x);
    //     customPlot->yAxis2->setRange(lower_y - step_y, upper_y - step_y);

    //     mDragStartPos = e->pos();

    //     customPlot->yAxis->setRange(niceRange);
    //     customPlot->replot();
    // }
//}

//void PlotDrawer::mousePressed(QMouseEvent *e)
//{
    // mDraggingCustomItem = true;
    // mDragStartPos = e->pos();
//}

//void PlotDrawer::mouseReleased(QMouseEvent *e)
//{
    //mDraggingCustomItem = false;
//}
