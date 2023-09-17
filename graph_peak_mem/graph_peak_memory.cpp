// Compute the peak memory consumption of a compute graph


#include <vector>
#include <iostream>
#include <unordered_set> 

using namespace std;

class Node {
};

class Tensor: public Node {
public:
	Tensor(const vector<int> &dims) {
		this->dims = dims;	
	}
	vector<int> dims;
	int get_size() {
		int numel = 1;
		for (const auto &dim : dims) {
			numel *= dim;
		}
		return numel;
	}
};

class Op: public Node {
public:
	Op(const vector<Tensor *> &operands, const vector<Tensor *> &results) {
		this->operands = operands;
		this->results = results;
	}
	vector<Tensor *> operands;
	vector<Tensor *> results;
};

int compute_max_memory(const vector<Op *> &graph) {
	// Discover tensors
	vector<Tensor *> tensors;
	for (const auto op : graph) {
		for (Tensor *operand : op->operands) {
			tensors.push_back(operand);
		}	
		for (Tensor *result: op->results) {
			tensors.push_back(result);
		}	
	}

	// Liveness for each line
	int max_size = 0;
	unordered_set<Tensor *> live_variables; // One for each tensor
	for (int op_iter = graph.size() - 1; op_iter >= 0; op_iter--) {
		// Traverses backwards

		const auto &op = graph.at(op_iter);

		// Results are live FOR THIS ITER ONLY
		for (Tensor *result : op->results) {
			live_variables.insert(result);
		}

		// Operands become live
		for (Tensor *operand : op->operands) {
			live_variables.insert(operand);
		}

		// Get memory size
		int total_size = 0;
		for (const auto tensor : live_variables) {
			total_size += tensor->get_size();
		}
		max_size = max(max_size, total_size);

		// Update live variables for future iters

		// Results die
		for (Tensor *result : op->results) {
			live_variables.erase(result);
		}
	}

	return max_size;
}

int main() {

	// Init the graph: A -> op1 -> B -> op2 -> C;
	Tensor A({2});
	Tensor B({2});
	Tensor C({2});
	Op op1({&A}, {&B});
	Op op2({&B}, {&C});

	vector<Node *> graph{&op1, &op2};

	const auto mem = compute_max_memory({&op1, &op2});

	cout << mem << endl;

	return 0;
}

