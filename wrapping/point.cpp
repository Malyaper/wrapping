#include "point.h"
#include <cmath>

int orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {
        return 0;  // колінеарні
    }

    return (val > 0) ? 1 : 2; // за годинниковою стрілкою або проти годинникової стрілки
}