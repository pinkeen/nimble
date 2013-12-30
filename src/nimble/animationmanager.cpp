#include "animationmanager.h"

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
        clear();
}

Animation* AnimationManager::createAnimation(const std::string &name, float fps)
{
        AnimPIterator it = m_anims.find(name);

        if(it!= m_anims.end())
                return it->second;

        Animation *pAnim = new Animation(name, fps);
        addAnimation(pAnim);

        return pAnim;
}

void AnimationManager::addAnimation(Animation *pAnim)
{
        m_anims[pAnim->name()] = pAnim;
}

Animation* AnimationManager::animation(const std::string &name)
{
        AnimPIterator it = m_anims.find(name);

        ASSERT(it != m_anims.end(), "Could not find animation '%s'!",
               name.c_str());

        return it->second;
}

void AnimationManager::clear()
{
        for(AnimPIterator i = m_anims.begin(); i != m_anims.end(); ++i)
                delete i->second;

        m_anims.clear();
}
