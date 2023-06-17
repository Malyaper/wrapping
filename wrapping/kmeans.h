#pragma once

#include "point.h"
#include <vector>

std::vector<int> kmeans(const std::vector<Point>& points, int k, int max_iterations = 100);
std::vector<Point> initialize_centroids(const std::vector<Point>& points, int k);
std::vector<int> assign_points_to_clusters(const std::vector<Point>& points, const std::vector<Point>& centroids);
std::vector<Point> update_centroids(const std::vector<Point>& points, const std::vector<int>& labels, int k);
