#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define NOCOLLISION(xa1, ya1, xa2, ya2, xb1, yb1, xb2, yb2) \
		( ((xb1) > (xa2)) || ((yb1) > (ya2)) || ((xb2) < (xa1)) || ((yb2) < (ya1)) )

#define DEGTORAD(x) ((x) * M_PI / 180.f)

#define CALLMEMBER(pObject, pMember) ((pObject)->*(pMember))

#define SIGNF(x) ((x) < 0.0f ? -1.0f : 1.0f)

#endif // MACROS_H
