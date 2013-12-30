/**
 * \file animation.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef ANIMATION_H
#define ANIMATION_H

#include "animationframe.h"

#include <vector>
#include <string>

class Animation
{
        protected:
                Animation(const std::string &name, float fps);

		friend class AnimationManager;

	private:
		std::string m_name;

		std::vector<AnimationFrame*> m_frames;

		float m_fps;
		bool m_reverse;
		bool m_loop;

                typedef std::vector<AnimationFrame*>::iterator FramePIterator;

		Rect m_boundBox;

		void updateBBox(const Vec &size, const Vec &alignPoint);
		void pushFrame(AnimationFrame *pFrame);

	public:
		~Animation();

                inline void setFps(float fps) { m_fps = fps; }
		inline void setReverse(bool reverse) { m_reverse = reverse; }
		inline void setLoop(bool loop) { m_loop = loop; }

		inline float fps() const { return m_fps; }
		inline bool reverse() const { return m_reverse; }
		inline bool loop() const { return m_loop; }
		inline int frameCount() const { return m_frames.size(); }
		inline const Rect &boundingBox() const { return m_boundBox; }
		inline const std::string &name() const { return m_name; }

                inline AnimationFrame* getFrame(int num) { return m_frames.at(num); }

		void addFramesFromUniformTileset(Image *pTilesetImage, const Vec &tileSize, int howmany);
                void addTileFrame(Image *pImage, const Rect &tileRect, const Vec &m_alignPoint);
                void addTileFrame(Image *pImage, const Rect &tileRect);
                void addFrame(Image *pImage, const Vec &m_alignPoint);
                void addFrame(Image *pImage);

                Animation* clone(const std::string &newName);
};

#endif // ANIMATION_H
