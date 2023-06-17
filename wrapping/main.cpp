#include "kmeans.h"
#include "gift_wrapping.h"
#include "visualization.h"
#include <iostream>
#include <random>

int main() {
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;

    std::vector<Point> points(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> coord_distribution(-100.0, 100.0);

    std::cout << "Generating random coordinates for the points..." << std::endl;
    for (int i = 0; i < n; ++i) {
        points[i].x = coord_distribution(gen);
        points[i].y = coord_distribution(gen);
        std::cout << "(" << points[i].x << ", " << points[i].y << ")" << std::endl;
    }

    int k;
    std::cout << "Enter the number of clusters: ";
    std::cin >> k;

    std::vector<int> labels = kmeans(points, k);

    std::cout << "Cluster labels:" << std::endl;
    for (const auto& label : labels) {
        std::cout << label << std::endl;
    }

    std::vector<Point> hull_points = gift_wrapping(points);

    std::cout << "Convex hull points:" << std::endl;
    for (const auto& point : hull_points) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    visualize(points, labels, hull_points);

    return 0;
}
