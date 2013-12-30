#include "basicviewstate.h"

BasicViewState::BasicViewState(Configurator *pConfig)
	: ViewState(pConfig)
{
	m_pImageHolder = new ImageManager(m_pGraphics);
	m_pAnimationHolder = new AnimationManager();
	m_pTimerManager = new TimerManager();
	m_pBoundingShapeManager = new BoundingShapeManager();
	m_pSpriteEngine = new SpriteEngine(m_pConfig, m_pAnimationHolder, m_pInput, m_pTimerManager, m_pBoundingShapeManager);

	m_altKey = input()->keyID("lalt");
	m_enterKey = input()->keyID("enter");
}

BasicViewState::~BasicViewState()
{
	delete m_pImageHolder;
	delete m_pAnimationHolder;
	delete m_pSpriteEngine;
	delete m_pTimerManager;
	delete m_pBoundingShapeManager;
}

void BasicViewState::frame(float lag)
{
	if(input()->keyComboStateReset(m_altKey, m_enterKey))
		graphics()->toggleFullscreen();

	m_pTimerManager->step(lag);
	m_pSpriteEngine->step(lag);
	onFrame(lag);

	m_pSpriteEngine->draw();
}
