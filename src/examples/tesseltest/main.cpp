/**
 * \file main.cpp
 * \author Filip Sobalski <pinkeen@gmail.com>
 */

#include <nimble/nimble.h>
#include <nimble/polygons/tesselator.h>
#include <nimble/opengl/oglgraphics.h>
#include <vector>

int main(int argc, char **argv)
{
	System sys(argc, argv);
	Configurator conf(&sys);

	Polygon p;

	p.addVertex(Vec(120, 85));
	p.addVertex(Vec(427, 142));
	p.addVertex(Vec(338, 180));
	p.addVertex(Vec(425, 265));
	p.addVertex(Vec(282, 307));
	p.addVertex(Vec(285, 410));
	p.addVertex(Vec(200, 290));
	p.addVertex(Vec(150, 480));
	p.addVertex(Vec(67, 412));
	p.addVertex(Vec(50, 30));


	Polygon x;
	x.addVertex(Vec(282, 307));
	x.addVertex(Vec(400, 400));
	x.addVertex(Vec(370, 500));
	x.addVertex(Vec(285, 410));

	p.glueCommonEdge(x);

	Tesselator t;
	PolygonGroup *pGroup = t.tesselatePolygon(&p);

	INFO("before: %u", pGroup->polygonCount());

	pGroup->minimize();

	INFO("after: %u", pGroup->polygonCount());


	Input i;
	sys.init();
	OGLGraphics g(&conf);
	g.init();

	while(!i.quit())
	{
		i.update();
		g.clearBuffer();

		for(unsigned int i = 0; i < pGroup->polygonCount(); ++i)
		{
			g.drawPolygonOutline(pGroup->polygon(i), Color(0, 1, 0, 1), Vec());

			Polygon bb(pGroup->polygon(i)->boundingBox());
			g.drawPolygonOutline(&bb, Color(1, 0, 0, 1), Vec());
		}

		//Polygon bb(pGroup->boundingBox())
		//g.drawPolygon(&bb, Color(0, 0, 1, 1));

		g.swapBuffers();

		sys.delay(100);
	}

	delete pGroup;

}
