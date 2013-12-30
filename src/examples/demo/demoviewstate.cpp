#include "demoviewstate.h"

#include <nimble/logger.h>
#include <nimble/fadeviewstate.h>

#include "demosprite.h"
#include "splashviewstate.h"

DemoViewState::DemoViewState(Configurator *pConfig)
	: BasicViewState(pConfig)
{
}

DemoViewState::~DemoViewState()
{

}

void DemoViewState::onInit()
{
	graphics()->setBackgroundColor(Color());

	m_escKeyID = m_pInput->keyID("esc");

	Animation *pDemoAnim = anims()->createAnimation("demoAnim", 2.0f);

	Image *pDemoImg1 = images()->createImageFromFile(config()->resourcePath("/air.png"));
	Image *pDemoImg2 = images()->createImageFromFile(config()->resourcePath("/air2.png"));

	pDemoAnim->setLoop(true);
	pDemoAnim->setReverse(true);
	pDemoAnim->addFrame(pDemoImg1);
	pDemoAnim->addFrame(pDemoImg2);

	Animation *pPartAnim = anims()->createAnimation("particle", 0.0f);
	Image *pPartImg = images()->createImageFromFile(config()->resourcePath("/particle.png"));
	pPartAnim->addFrame(pPartImg);

	new DemoSprite(engine());

	INFO("Finished loading.");
	images()->printMemStats();
}

void DemoViewState::onFrame(float lag)
{
	if(input()->keyStateReset(m_escKeyID))
		changeState(new FadeViewState(new SplashViewState(config()), 1.0f, Color(1.0f, 1.0f, 1.0f)));

}

