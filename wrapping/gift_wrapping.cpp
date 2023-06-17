#include "gift_wrapping.h"
#include "point.h"

std::vector<Point> gift_wrapping(const std::vector<Point>& points) {
    if (points.size() < 3) {
        return points;
    }

    std::vector<Point> hull;
    int leftmost_point = 0;

    for (int i = 1; i < points.size(); i++) {
        if (points[i].x < points[leftmost_point].x) {
            leftmost_point = i;
        }
    }

    int p = leftmost_point, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % points.size();
        for (int i = 0; i < points.size(); i++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }
        p = q;
    } while (p != leftmost_point);

    return hull;
}
