#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <string>
#include <map>

#include "animation.h"
#include "logger.h"

class AnimationManager
{
        private:
                std::map<std::string, Animation*> m_anims;
                typedef std::map<std::string, Animation*>::iterator AnimPIterator;

        protected:
                void addAnimation(Animation *pAnim);

        public:
		AnimationManager();
		~AnimationManager();

		Animation* animation(const std::string &name);

                Animation* createAnimation(const std::string &name, float fps);

                void clear();

                inline int animCount() const { return m_anims.size(); }
};

#endif // ANIMATIONMANAGER_H
