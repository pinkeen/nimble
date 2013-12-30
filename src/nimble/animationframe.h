/**
 * \file animationframe.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */

#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include "image.h"
#include "vector.h"
#include "rect.h"

class AnimationFrame
{
        protected:
                AnimationFrame(Image *pImage, const Rect &tileRect, const Vec &m_alignPoint);

                friend class Animation;

	private:
                Image *m_pImage;

		/** Position of the tile in the tileset */
		Rect m_tileRect;

                /** Normalized tile rect. Precomputed for OGL. */
		Rect m_normTileRect;

		/**
		 * Align Point is used to align different
                 * frames of animation.
		 */
		Vec m_alignPoint;
                Vec m_size;

	public:

                inline Image* image() const { return m_pImage; }
                inline const Rect &tileRect() const { return m_tileRect; }
		inline const Rect &normTileRect() const { return m_normTileRect; }
                inline const Vec &alignPoint() const { return m_alignPoint; }
                inline const Vec &size() const { return m_size; }

                AnimationFrame* clone();

};

#endif // ANIMATIONFRAME_H
