#include "imagemanager.h"

#include "logger.h"

unsigned int ImageManager::m_totalImageCount = 0;
unsigned int ImageManager::m_totalBytes = 0;


ImageManager::ImageManager(Graphics *pGraphics)
        : m_pGraphics(pGraphics), m_bytes(0)
{
}

ImageManager::~ImageManager()
{
        m_totalImageCount -= m_imgs.size();
        m_totalBytes -= m_bytes;
        clear();
}

Image* ImageManager::createImageFromFile(const std::string &filename)
{
        ImagePIterator it = m_imgs.find(filename);

        if(it != m_imgs.end())
                return it->second;

        Image *pImg = m_pGraphics->createImageFromFile(filename);
        m_imgs[filename] = pImg;

        unsigned int sz = pImg->bytes();
        m_totalImageCount++;
        m_totalBytes += sz;
        m_bytes += sz;

        return pImg;
}

void ImageManager::clear()
{
        for(ImagePIterator i = m_imgs.begin(); i != m_imgs.end(); ++i)
                delete i->second;

        m_imgs.clear();
}

void ImageManager::printTotalMemStats()
{
	INFO("Loaded %d images of total size %.2f KiB", totalImageCount(), (float)totalBytes() / 1024.0f);
}

void ImageManager::printMemStats()
{
	INFO("Loaded %d images of total size %.2f KiB", imageCount(), (float)bytes() / 1024.0f);
}
