/**
 *  @file abworld.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#include "ABWorld.h"

ABWorld::ABWorld(const b2Vec2& gravity):b2World(gravity)
{
}

void ABWorld::DrawData()
{
	if (m_debugDraw == NULL)
	{
		return;
	}

  for (b2Body* b = m_bodyList; b; b = b->GetNext())
  {
	  const b2Transform& xf = b->GetTransform();
	  for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
	  {
		  if (b->IsActive() == false)
		  {
			  DrawShape(f, xf, b2Color(0.5f, 0.5f, 0.3f));
		  }
		  else if (b->GetType() == b2_staticBody)
		  {
			  DrawShape(f, xf, b2Color(0.5f, 0.9f, 0.5f));
		  }
		  else if (b->GetType() == b2_kinematicBody)
		  {
			  DrawShape(f, xf, b2Color(0.5f, 0.5f, 0.9f));
		  }
		  else if (b->IsAwake() == false)
		  {
			  DrawShape(f, xf, b2Color(0.6f, 0.6f, 0.6f));
		  }
		  else
		  {
			  DrawShape(f, xf, b2Color(0.9f, 0.7f, 0.7f));
		  }
	  }
  }

}
//} /* namespace NBird */
