#include "raytrace.hpp"

#include <cmath>

std::vector<Vector2> raytrace(Vector2 StartPosition, int Segments, std::vector<Rectangle>& Obstacles, int Range) {
    const float degreesPerTrace = 360.0 / float(Segments);

    std::vector<Vector2> collisionPoints;
    for (int i = 0; i < Segments; i++) {
        const float degreeToTrace = degreesPerTrace * i;
        const float radiansToTrace = degreeToTrace * (PI / 180.0f);

        float x, y;
        x = StartPosition.x + Range * std::cos(radiansToTrace);
        y = StartPosition.y + Range * std::sin(radiansToTrace);

        Vector2 closestCollisionPoint = { 0, 0 };
        for (auto& obstacle : Obstacles) {
            Vector2 collisionPoint = { 0, 0 };
            for (int j = 0; j < 4; j++) {
                switch (j) {
                    case 0:
                        if (CheckCollisionLines(StartPosition, { x, y }, { obstacle.x, obstacle.y }, { obstacle.x + obstacle.width, obstacle.y }, &collisionPoint))
                            j = 4;
                        break;
                    case 1:
                        if (CheckCollisionLines(StartPosition, { x, y }, { obstacle.x, obstacle.y + obstacle.height }, { obstacle.x + obstacle.width, obstacle.y + obstacle.height }, &collisionPoint))
                            j = 4;
                        break;
                    case 2:
                        if (CheckCollisionLines(StartPosition, { x, y }, { obstacle.x, obstacle.y }, { obstacle.x, obstacle.y + obstacle.height }, &collisionPoint))
                            j = 4;
                        break;
                    case 3:
                        if (CheckCollisionLines(StartPosition, { x, y }, { obstacle.x + obstacle.width, obstacle.y }, { obstacle.x + obstacle.width, obstacle.y + obstacle.height }, &collisionPoint))
                            j = 4;
                        break;
                }
            }
            if (collisionPoint.x != 0 || collisionPoint.y != 0) {
                if (closestCollisionPoint.x == 0 && closestCollisionPoint.y == 0) {
                    closestCollisionPoint = collisionPoint;
                } else if (std::abs(collisionPoint.x - StartPosition.x) < std::abs(closestCollisionPoint.x - StartPosition.x) && std::abs(collisionPoint.y - StartPosition.y) < std::abs(closestCollisionPoint.y - StartPosition.y)) {
                    closestCollisionPoint = collisionPoint;
                }
            }
        }

        if (closestCollisionPoint.x != 0 && closestCollisionPoint.y != 0) {
            collisionPoints.push_back(closestCollisionPoint);
        }
    }
    return collisionPoints;
}
