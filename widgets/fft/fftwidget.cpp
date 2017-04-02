/***************************************************************************
                          fftwidget.cpp  -  description
                             -------------------
    begin                : May 18 2005
    copyright            : (C) 2005 by Philip McLeod
    email                : pmcleod@cs.otago.ac.nz
 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   Please read LICENSE.txt for details.
 ***************************************************************************/
#include <qpixmap.h>
#include <qpainter.h>
#include <qmemarray.h>

#include "fftwidget.h"
#include "gdata.h"
#include "channel.h"
#include "analysisdata.h"
#include "useful.h"

FFTWidget::FFTWidget(QWidget *parent)
  : DrawWidget(parent)
{
}

FFTWidget::~FFTWidget()
{
}

void FFTWidget::paintEvent( QPaintEvent * )
{
  Channel *active = gdata->getActiveChannel();

  AnalysisData *data;
  //double dh2 = double(height()-1) / 2.0;
  double pixelStep;
  int j, x;
    
  beginDrawing(false);
  
  if(active) {
    pixelStep = double(active->fftData1.size()) / double(width());
    if(int(pointArray.size()) != width()) pointArray.resize(width());
    
    active->lock();
    data = active->dataAtCurrentChunk();

    if(data) {
      double freq = data->fundamentalFreq;
      double normalisedFreq = freq / double(active->rate()) * 2.0;
      //double numPeriods = double(active->size()) / period;
      double scaleX = normalisedFreq * double(width()); //pixels per fundamental freq
      
      //draw alternating background color indicating period
      if(gdata->view->backgroundShading() && scaleX > 4.0 && scaleX < double(width())) {
        int n = int(ceil(double(width()) / scaleX)); //number of colored patches
        p.setPen(Qt::NoPen);
        QColor color1 = colorBetween(gdata->backgroundColor(), gdata->shading1Color(), data->correlation);
        QColor color2 = colorBetween(gdata->backgroundColor(), gdata->shading2Color(), data->correlation);
        for(j = 0; j<n; j++) {
          x = toInt(scaleX*double(j));
          p.setBrush((j%2) ? color1 : color2);
          p.drawRect(x, 0, toInt(scaleX*double(j+1)) - toInt(scaleX*double(j)), height());
        }
        p.setPen(colorBetween(gdata->backgroundColor(), Qt::black, 0.3*data->correlation));
        for(j = 0; j<n; j++) {
          x = toInt(scaleX*double(j));
          p.drawLine(x, 0, x, height());
        }
      } else {
        clearBackground();
      }
      QString fundFreqText;
      fundFreqText.sprintf("Fundamental Frequency = %lf", freq);
      p.setPen(Qt::black);
      p.drawText(5, 15, fundFreqText);
    } else {
      clearBackground();
    }
    
    //draw the waveform
    //float size = active->fftData1.size();
    double ratio = double(height()) * 20.0 / 85.0; //Show 85dB
    p.setPen(QPen(active->color, 0));
    for(int j=0; j<width(); j++) { //cheap hack to go faster (by drawing less points)
      myassert(int(pixelStep*j) < active->fftData1.size());
      //pointArray.setPoint(j, j, -toInt(log10(active->fftData1.at(int(pixelStep*j))/size)*ratio));
      pointArray.setPoint(j, j, -toInt(active->fftData1.at(int(pixelStep*j))*ratio));
    }
    p.drawPolyline(pointArray);

/*
    if(data) {
      double ratio = double(width()) / double(active->nsdfData.size()); //pixels per index
      float highest = active->nsdfData.at(data->highestCorrelationIndex);
      float chosen = active->nsdfData.at(data->chosenCorrelationIndex);
      
      //draw threshold line
      p.setPen(QPen(colorBetween(colorGroup().background(), Qt::black, 0.3), 0));
      y = toInt(dh2 - (highest * active->threshold()) * dh2);
      p.drawLine(0, y, width(), y);
      
      //draw a dot at the highest correlation period
      p.setPen(Qt::black);
      p.setBrush(Qt::black);
      x = toInt(double(data->highestCorrelationIndex) * ratio);
      y = toInt(dh2 - highest * dh2);
      p.drawEllipse(x-2, y-2, 5, 5);
      
      //draw a dot at the chosen correlation period
      p.setPen(Qt::red);
      p.setBrush(Qt::red);
      x = toInt(double(data->chosenCorrelationIndex) * ratio);
      y = toInt(dh2 - chosen * dh2);
      p.drawEllipse(x-2, y-2, 5, 5);
    }
*/    
    active->unlock();
  } else {
    clearBackground();
  }
    
  endDrawing();
}
