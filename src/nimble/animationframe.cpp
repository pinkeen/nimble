/**
 * \file animationframe.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#include "animationframe.h"
#include "logger.h"


AnimationFrame::AnimationFrame(Image *pImage, const Rect &tileRect, const Vec &alignPoint)
        : m_pImage(pImage), m_tileRect(tileRect), m_normTileRect(m_tileRect),
        m_alignPoint(alignPoint)
{
        m_normTileRect.norm((float)pImage->width() - 1.0f, (float)pImage->height() - 1.0f);
        m_size = m_tileRect.size();
}

AnimationFrame* AnimationFrame::clone()
{
        AnimationFrame *pFrame = new AnimationFrame(m_pImage, m_tileRect, m_alignPoint);
        return pFrame;
}



