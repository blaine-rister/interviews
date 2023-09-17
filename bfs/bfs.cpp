#include <queue>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

class Node {
public:
	int id;
	vector<Node *> successors;

	Node(int id, vector<Node *> successors) {
		this->id = id;
		this->successors = successors;
	}	
};

void bfs(Node *const root) {
	unordered_set<Node *> visited;
	queue<Node *> q;

	q.push(root);
	while (!q.empty()) { 
		// Get the next root, check if it's been visited
		auto node = q.front();
		q.pop();
		if (visited.find(node) != visited.end()) {
			continue;
		}
		visited.insert(node);

		// Print id 
		cout << node->id << endl;

		// Push successors
		for (const auto &successor : node->successors) {
			q.push(successor);
		}	
	}		
}

int main() {

	// Create a graph
	// 0 -> 1 -> 2
	//   -> 3
	auto node3 = Node(3, {});
	auto node2 = Node(2, {});
	auto node1 = Node(1, {&node2});
	auto node0 = Node(0, {&node1, &node3});

	bfs(&node0);

	return 0;
}
