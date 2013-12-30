/**
 * \file image.h
 * \author Filip Sobalski <pinkeen@gmail.com>
 */
#ifndef IMAGE_H
#define IMAGE_H

class Image
{
	protected:
		Image();

		int m_width;
		int m_height;

		bool m_hasAlpha;
                int m_bpp;

        public:

                inline int height() const { return m_height; }
                inline int width() const { return m_width; }
                inline bool hasAlpha() const { return m_hasAlpha; }

                inline const unsigned int bytes() const
                        { return m_width * m_height * (m_bpp >> 3); }


                virtual ~Image();



};

#endif // IMAGE_H
