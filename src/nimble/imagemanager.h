#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <string>
#include <map>

#include "image.h"
#include "graphics.h"
#include "logger.h"

class ImageManager
{
        protected:
                Graphics *m_pGraphics;

        private:
                static unsigned int m_totalImageCount;
                static unsigned int m_totalBytes;

                unsigned int m_bytes;

                std::map<std::string, Image*> m_imgs;
                typedef std::map<std::string, Image*>::iterator ImagePIterator;

        public:
		ImageManager(Graphics *pGraphics);
		~ImageManager();

                Image* createImageFromFile(const std::string &filename);

                void clear();

                inline unsigned int imageCount() const { return m_imgs.size(); }
                inline unsigned int bytes() const { return m_bytes; }

                static unsigned int totalImageCount() { return m_totalImageCount; }
		static unsigned int totalBytes() { return m_totalBytes; }

		static void printTotalMemStats();
		void printMemStats();
};

#endif // IMAGEMANAGER_H
