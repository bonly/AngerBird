/**
 *  @file abdraw.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "ABDraw.h"
#include "pre.h"
void ABDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
   if (vertexCount < 3)
     return;
   gpDC->setColor(0,255,0);
   for (int32 i=0; i<vertexCount; ++i)
   {
     gpDC->drawLine(M2P(vertices[i].x), M2P(vertices[i].y), M2P(vertices[i+1].x), M2P(vertices[i+1].y));
   }
}

void ABDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
   if (vertexCount < 3)
     return;
   gpDC->setColor(255,0,0);
   for (int32 i=0; i<vertexCount; ++i)
   {
     gpDC->drawLine(M2P(vertices[i].x), M2P(vertices[i].y), M2P(vertices[i+1].x), M2P(vertices[i+1].y));
   }
}

void ABDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
   gpDC->setColor(0,255,0);
   gpDC->drawLine(center.x-radius,center.y-radius, center.x-radius, center.y+radius);
   gpDC->drawLine(center.x-radius,center.y+radius, center.x+radius, center.y+radius);
   gpDC->drawLine(center.x+radius,center.y+radius, center.x+radius, center.y-radius);
   gpDC->drawLine(center.x+radius,center.y-radius, center.x-radius, center.y-radius);
}

void ABDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
   gpDC->setColor(255,0,0);
   gpDC->drawLine(center.x-radius,center.y-radius, center.x-radius, center.y+radius);
   gpDC->drawLine(center.x-radius,center.y+radius, center.x+radius, center.y+radius);
   gpDC->drawLine(center.x+radius,center.y+radius, center.x+radius, center.y-radius);
   gpDC->drawLine(center.x+radius,center.y-radius, center.x-radius, center.y-radius);
}

void ABDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
  gpDC->setColor(0,255,0);
  gpDC->drawLine(M2P(p1.x),M2P(p1.y), M2P(p2.x), M2P(p2.y));
}

void ABDraw::DrawTransform(const b2Transform& xf)
{

}


//} /* namespace NBird */
