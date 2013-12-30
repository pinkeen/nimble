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
			Animation *pAPlayer = anims()->createAnimation("Player", 20.0f);
			Animation *pAPlayerWalk = anims()->createAnimation("PlayerWalk", 20.0f);
			Animation *pAPlayerShoot = anims()->createAnimation("PlayerShoot", 20.0f);
			Animation *pABarrel = anims()->createAnimation("Barrel", 0.0f);
			Animation *pAExplosion = anims()->createAnimation("Explosion", 0.0f);
			Animation *pAFlame = anims()->createAnimation("Flame", 0.0f);
			Animation *pAContainer = anims()->createAnimation("Container", 0.0f);
			Animation *pAMonster = anims()->createAnimation("Monster", 0.0f);
			Animation *pAMonsterBurn = anims()->createAnimation("MonsterBurn", 0.0f);

			pAPlayer->setLoop(true);
			pAPlayer->setReverse(true);
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand1.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand2.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand3.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand4.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand5.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand6.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand7.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand8.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand9.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand10.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand11.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand12.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand13.png")));
			pAPlayer->addFrame(images()->createImageFromFile(config()->resourcePath("/stand14.png")));

			pAPlayerWalk->setLoop(true);
			pAPlayerWalk->addFrame(images()->createImageFromFile(config()->resourcePath("/walk1.png")));
			pAPlayerWalk->addFrame(images()->createImageFromFile(config()->resourcePath("/walk2.png")));
			pAPlayerWalk->addFrame(images()->createImageFromFile(config()->resourcePath("/walk3.png")));
			pAPlayerWalk->addFrame(images()->createImageFromFile(config()->resourcePath("/walk4.png")));
			pAPlayerWalk->addFrame(images()->createImageFromFile(config()->resourcePath("/walk5.png")));
			pAPlayerWalk->addFrame(images()->createImageFromFile(config()->resourcePath("/walk6.png")));


			pAPlayerShoot->setLoop(true);
			pAPlayerShoot->setReverse(true);
			pAPlayerShoot->addFrame(images()->createImageFromFile(config()->resourcePath("/shoot1.png")));
			pAPlayerShoot->addFrame(images()->createImageFromFile(config()->resourcePath("/shoot2.png")));
			pAPlayerShoot->addFrame(images()->createImageFromFile(config()->resourcePath("/shoot3.png")));
			pAPlayerShoot->addFrame(images()->createImageFromFile(config()->resourcePath("/shoot4.png")));

			pABarrel->addFrame(images()->createImageFromFile(config()->resourcePath("/barrel.png")));

			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion1.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion2.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion3.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion4.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion5.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion6.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion7.png")));
			pAExplosion->addFrame(images()->createImageFromFile(config()->resourcePath("/explosion8.png")));

			pAFlame->addFrame(images()->createImageFromFile(config()->resourcePath("/flame8.png")));
			
			pAMonster->setLoop(true);
			pAMonster->setReverse(true);
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster1.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster2.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster3.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster4.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster5.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster6.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster7.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster8.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster9.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster10.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster11.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster12.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster13.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster14.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster15.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster16.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster17.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster18.png")));
			pAMonster->addFrame(images()->createImageFromFile(config()->resourcePath("/monster19.png")));

			pAMonsterBurn->addFrame(images()->createImageFromFile(config()->resourcePath("/monsterburn1.png")));
			pAMonsterBurn->addFrame(images()->createImageFromFile(config()->resourcePath("/monsterburn2.png")));
			pAMonsterBurn->addFrame(images()->createImageFromFile(config()->resourcePath("/monsterburn3.png")));
			pAMonsterBurn->addFrame(images()->createImageFromFile(config()->resourcePath("/monsterburn4.png")));

			pAContainer->addFrame(images()->createImageFromFile(config()->resourcePath("/container.png")));


			/*Animation *pABCG = anims()->createAnimation("Bcg", 0.0f);
			pABCG->addFrame(images()->createImageFromFile(config()->resourcePath("/bcg.jpg")));

			new Sprite(engine(), -1, 0, pABCG, Vec(-300, -300), false, false, true, "Bcg");*/

			shapes()->createBoundingPolygons("Player", pAPlayer, 0.7f);
			shapes()->createBoundingPolygons("Monster", pAMonster, 1.0f);
			shapes()->createBoundingPolygons("Flame", pAFlame, 0.5f);
			shapes()->createBoundingPolygons("Container", pAContainer, 1.0f);

			new PlayerSprite(engine(), Vec(100, 100));

			for(int i = 0; i < 10; ++i)
			{
				new MonsterSprite(engine(), Vec(Utils::randFloat(100.0f, 600.0f), Utils::randFloat(100.0f, 600.0f)));
			}

			Vec sz(pAContainer->boundingBox().size());

			int l = 20;

			for(int x = 0; x < l; ++x)
			{
				new ContainerSprite(engine(), Vec((float)x * sz.x(), 0.0f));
				new ContainerSprite(engine(), Vec((float)x * sz.x(), (float)(l - 1) * sz.y()));
			}

			for(int y = 1; y < (l - 1); ++y)
			{
				new ContainerSprite(engine(), Vec(0.0f, (float)y * sz.y()));
				new ContainerSprite(engine(), Vec((float)(l - 1) * sz.y(), (float)y * sz.y()));
			}


			images()->printMemStats();
		}

		void onFrame(float lag)
		{
			if(input()->keyStateReset(m_outlinesKey))
				engine()->toggleDrawingBounds();
		}
};

#endif // MAINVIEWSTATE_H
