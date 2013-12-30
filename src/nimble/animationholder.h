#ifndef ANIMATIONHOLDER_H
#define ANIMATIONHOLDER_H

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

                Animation* getAnimation(const std::string &name);

                Animation* createAnimation(const std::string &name, float fps);

                void clear();

                inline int animCount() const { return m_anims.size(); }
};

#endif // ANIMATIONHOLDER_H
