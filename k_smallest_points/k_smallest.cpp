#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

using point = pair<double, double>;

int get_dist(const point &p) {
	return p.first * p.first + p.second * p.second;
}

vector<point> kSmallest(vector<point> &points, int k) {
	// Compare points by dist, for sorting
	auto cmp = [](point &x, point &y) {
		return get_dist(x) < get_dist(y);
	};

	// Sort by dist
	nth_element(points.begin(), points.begin() + k, points.end(), cmp);

	return points;
}

int main() {
	int k = 2;
	std::vector<point> points({{1, 1}, {0, 0}, {0, 2}, {3, 3}});
	points = kSmallest(points, k);

	// Print points
	for (auto &point : points) {
		cout << point.first << " " << point.second << endl;
	}

	return 0;
}
