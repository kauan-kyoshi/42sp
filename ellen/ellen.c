#include <stdio.h>

int main() {
	float x, y;

	y = 1.5f;

	while (y > -1.5f)
	{
		x = -1.5f;

		while (x < 1.5f)
		{
			float z = x * x + y * y - 1;

			if (z * z * z - x * x * y * y * y <= 0.0f) {
				printf("*");
			} else {
				printf(" ");
			}
			x += 0.05f;
		}
		printf("\n");
		y -= 0.1f;
	}

	printf("\n                     Namora cmg agora ? :3 \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	return 0;
}