#ifndef MAINVIEWSTATE_H
#define MAINVIEWSTATE_H

#include <nimble/nimble.h>

#include "sprites.h"

class MainViewState : public BasicViewState
{
	private:
		KeyID m_outlinesKey;

	public:
		MainViewState(Configurator *pConfig)
			: BasicViewState(pConfig)
		{
			m_outlinesKey = input()->keyID("f1");
		}

		~MainViewState() {}

		void onInit()
		{
			Animation *pAnimA = anims()->createAnimation("A", 0.0f);
			Animation *pAnimB = anims()->createAnimation("B", 0.0f);
			Animation *pAnimC = anims()->createAnimation("C", 0.0f);
			Animation *pAnimD = anims()->createAnimation("D", 0.0f);

			Image *pImgA = images()->createImageFromFile(config()->resourcePath("/A.png"));
			Image *pImgB = images()->createImageFromFile(config()->resourcePath("/B.png"));
			Image *pImgC = images()->createImageFromFile(config()->resourcePath("/C.png"));
			Image *pImgD = images()->createImageFromFile(config()->resourcePath("/D.png"));

			pAnimA->addFrame(pImgA);
			pAnimB->addFrame(pImgB);
			pAnimC->addFrame(pImgC);
			pAnimD->addFrame(pImgD);

			Polygon *pPA = new Polygon();
			Polygon *pPB = new Polygon();
			Polygon *pPC = new Polygon();
			Polygon *pPD = new Polygon();

			pPA->addVertex(Vec(-33,28));
			pPA->addVertex(Vec(-92,4));
			pPA->addVertex(Vec(-38,-27));
			pPA->addVertex(Vec(-33,-88));
			pPA->addVertex(Vec(13,-48));
			pPA->addVertex(Vec(73,-62));
			pPA->addVertex(Vec(49,-5));
			pPA->addVertex(Vec(80,45));
			pPA->addVertex(Vec(19,41));
			pPA->addVertex(Vec(-20,87));

			pPB->addVertex(Vec(-57, 96));
			pPB->addVertex(Vec(14, -115));
			pPB->addVertex(Vec(125, -30));
			pPB->addVertex(Vec(25, 5));
			pPB->addVertex(Vec(-20, 170));

			pPC->addVertex(Vec(-25, 58));
			pPC->addVertex(Vec(-5, 7));
			pPC->addVertex(Vec(-29, 37));
			pPC->addVertex(Vec(-87, -23));
			pPC->addVertex(Vec(-27, -77));
			pPC->addVertex(Vec(-52, -45));
			pPC->addVertex(Vec(23, -22));
			pPC->addVertex(Vec(57,-55));
			pPC->addVertex(Vec(81,-10));
			pPC->addVertex(Vec(49,27));
			pPC->addVertex(Vec(20, 2));
			pPC->addVertex(Vec(45,85));

			pPD->addVertex(Vec(-11, 44));
			pPD->addVertex(Vec(-53, 86));
			pPD->addVertex(Vec(-55, 29));
			pPD->addVertex(Vec(-80, -30));
			pPD->addVertex(Vec(-31,-37));
			pPD->addVertex(Vec(1, -80));
			pPD->addVertex(Vec(22,-31));
			pPD->addVertex(Vec(80,-13));
			pPD->addVertex(Vec(33,0));
			pPD->addVertex(Vec(61,67));

			BoundingShape *pBSA = shapes()->createBoundingPolygons("A", pPA);
			BoundingShape *pBSB = shapes()->createBoundingPolygons("B", pPB);
			BoundingShape *pBSC = shapes()->createBoundingPolygons("C", pPC);
			BoundingShape *pBSD = shapes()->createBoundingPolygons("D", pPD);

			new PlayerSprite(engine(), pAnimB, pBSB, engine()->viewRect().center(), Vec(58, 116));
			new ObstacleSprite(engine(), pAnimA, pBSA, Vec(650, 100), Vec(90, 90));
			new ObstacleSprite(engine(), pAnimC, pBSC, Vec(100, 100), Vec(88, 79));
			new ObstacleSprite(engine(), pAnimD, pBSD, Vec(650, 500), Vec(80, 80));

		}

		void onFrame(float lag)
		{
			if(input()->keyStateReset(m_outlinesKey))
				engine()->toggleDrawingBounds();
		}
};

#endif // MAINVIEWSTATE_H
