#include "Base.h"

float GetLen(Vector2f p1, Vector2f p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

}
float GetLen(Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}