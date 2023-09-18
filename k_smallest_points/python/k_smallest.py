"""
Given a list of points, return the k smallest by Euclidean distance.
"""

import dataclasses
import heapq

class Point:
	def __init__(self, x, y):
		self.x = x
		self.y = y

	def get_dist(self) -> int:
		return self.x ** 2 + self.y ** 2

	def __str__(self) -> str:
		return "%d %d" % (self.x, self.y)

def kSmallest(points: list[Point], k: int) -> list[Point]:
	return heapq.nsmallest(k, points, key=lambda x: x.get_dist())

# Main entry point
points = []
points.append(Point(1, 1))
points.append(Point(0, 1))
points.append(Point(1, 0))
points.append(Point(2, 0))

k = 2
smallest = kSmallest(points, k)

for point in smallest:
	print(point)
