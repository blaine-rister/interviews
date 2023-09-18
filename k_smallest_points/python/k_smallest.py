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

@dataclasses.dataclass(order=True) # Generates comparison functions
class DistPoint:
	dist: int 
	point: Point = dataclasses.field(compare=False) # Ignores this field in auto-generated comparison functions

	def __init__(self, point):
		self.dist = -point.get_dist() # Negate distance, to sort by largest element
		self.point = point

def kSmallest(points: list[Point], k: int) -> list[Point]:
	# Point -> distpoints
	distpoints = [DistPoint(p) for p in points]	

	# Heapify (linear time) and get the k smallest
	heapq.heapify(distpoints)
	while len(distpoints) > k:
		heapq.heappop(distpoints)

	# distpoints -> points
	return reversed([dp.point for dp in distpoints])

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
