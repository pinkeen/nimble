/**
 * \file animation.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "animation.h"

Animation::Animation(const std::string &name, float fps)
	: m_name(name), m_fps(fps), m_reverse(false), m_loop(false)
{

}

/* this probably won't work, why do we need it anyway? */
Animation *Animation::clone(const std::string &newName)
{
        Animation *pNewAnim = new Animation(newName, m_fps);


	pNewAnim->m_loop = m_loop;
	pNewAnim->m_reverse = m_reverse;

	for(FramePIterator f = m_frames.begin(); f != m_frames.end(); ++f)
                pNewAnim->m_frames.push_back((*f)->clone());

	return pNewAnim;
}


void Animation::addTileFrame(Image *pImage, const Rect &tileRect, const Vec &m_alignPoint)
{
        AnimationFrame *pFrame = new AnimationFrame(pImage, tileRect, m_alignPoint);

	pushFrame(pFrame);
}

void Animation::addTileFrame(Image *pImage, const Rect &tileRect)
{
        AnimationFrame *pFrame = new AnimationFrame(pImage,
                                                    tileRect,
                                                    Vec(0.0f, 0.0f));

	pushFrame(pFrame);
}

void Animation::addFrame(Image *pImage, const Vec &m_alignPoint)
{
        AnimationFrame *pFrame = new AnimationFrame(pImage,
                                                    Rect(0.0f, 0.0f,
                                                         (float)pImage->width() - 1.0f,
                                                         (float)pImage->height() - 1.0f),
                                                    m_alignPoint);

	pushFrame(pFrame);
}

void Animation::addFrame(Image *pImage)
{
        AnimationFrame *pFrame = new AnimationFrame(pImage,
                                                    Rect(0.0f, 0.0f,
                                                         (float)pImage->width() - 1.0f,
                                                         (float)pImage->height() - 1.0f),
                                                    Vec(0.0f, 0.0f));

	pushFrame(pFrame);
}

void Animation::pushFrame(AnimationFrame *pFrame)
{
	m_frames.push_back(pFrame);
	updateBBox(pFrame->size(), pFrame->m_alignPoint);
}

void Animation::updateBBox(const Vec &size, const Vec &alignPoint)
{
	Vec tl(alignPoint);
	Vec br(size);

	tl.mult(-1.0f);
	br.sub(alignPoint);

	Rect nr(tl, br);

	m_boundBox.merge(nr);
}

Animation::~Animation()
{
	for(FramePIterator it = m_frames.begin();
		it != m_frames.end(); ++it)
	{
		delete *it;
	}
}
