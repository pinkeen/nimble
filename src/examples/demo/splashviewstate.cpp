#include "splashviewstate.h"

#include "logosprite.h"
#include "entersprite.h"
#include "demoviewstate.h"
#include <nimble/fadeviewstate.h>

SplashViewState::SplashViewState(Configurator *pConfig)
	: BasicViewState(pConfig)
{

}

SplashViewState::~SplashViewState()
{

}

void SplashViewState::onInit()
{
	graphics()->setBackgroundColor(Color(0.3f, 0.1f, 0.0f));
	m_enterKeyID = input()->keyID("enter");

	Animation *pLogoAnim = anims()->createAnimation("logo", 0.0f);
	Image *pLogoImg = images()->createImageFromFile(config()->resourcePath("/nimble.png"));
	pLogoAnim->addFrame(pLogoImg);
	new LogoSprite(m_pSpriteEngine);

	Animation *pEnterAnim = anims()->createAnimation("enter", 0.0f);
	Image *pEnterImg = images()->createImageFromFile(config()->resourcePath("/press.png"));
	pEnterAnim->addFrame(pEnterImg);
	new EnterSprite(m_pSpriteEngine);


	INFO("Finished loading.");
	images()->printMemStats();
}


void SplashViewState::onFrame(float lag)
{
	if(input()->keyStateReset(m_enterKeyID))
		changeState(new FadeViewState(new DemoViewState(config()), 1.0f, Color(0.0f, 0.0f, 1.0f)));
}

