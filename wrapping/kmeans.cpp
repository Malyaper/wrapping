#include "kmeans.h"
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>

double euclidean_distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

std::vector<Point> initialize_centroids(const std::vector<Point>& points, int k) {
    std::srand(std::time(0));
    std::vector<Point> centroids(k);
    for (int i = 0; i < k; ++i) {
        int idx = std::rand() % points.size();
        centroids[i] = points[idx];
    }
    return centroids;
}

std::vector<int> assign_points_to_clusters(const std::vector<Point>& points, const std::vector<Point>& centroids) {
    std::vector<int> labels(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        double min_dist = std::numeric_limits<double>::max();
        int closest_centroid = -1;
        for (size_t j = 0; j < centroids.size(); ++j) {
            double dist = euclidean_distance(points[i], centroids[j]);
            if (dist < min_dist) {
                min_dist = dist;
                closest_centroid = j;
            }
        }
        labels[i] = closest_centroid;
    }
    return labels;
}

std::vector<Point> update_centroids(const std::vector<Point>& points, const std::vector<int>& labels, int k) {
    std::vector<Point> centroids(k, { 0, 0 });
    std::vector<int> count(k, 0);

    for (size_t i = 0; i < points.size(); ++i) {
        centroids[labels[i]].x += points[i].x;
        centroids[labels[i]].y += points[i].y;
        count[labels[i]]++;
    }

    for (int i = 0; i < k; ++i) {
        centroids[i].x /= count[i];
        centroids[i].y /= count[i];
    }

    return centroids;
}

std::vector<int> kmeans(const std::vector<Point>& points, int k, int max_iterations) {
    std::vector<Point> centroids = initialize_centroids(points, k);
    std::vector<int> labels;

    for (int i = 0; i < max_iterations; ++i) {
        labels = assign_points_to_clusters(points, centroids);
        std::vector<Point> new_centroids = update_centroids(points, labels, k);

        centroids = new_centroids;
    }
    return labels;
}