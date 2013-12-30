#include <nimble/nimble.h>

int main(int argc, char **argv)
{
	System sys(argc, argv);

	unsigned int st = sys.ticks();

	Vec x(Utils::randFloat(), Utils::randFloat());

	for(int i = 0; i < 10000000; ++i)
	{
		Vec y(x);
		x.sub(Utils::randFloat(), Utils::randFloat());

		Vec z(x);
		z.sub(y);
	}

	unsigned int en = sys.ticks();

	INFO("Took %f seconds.", (float)(en - st) / 1000.0f);
}
