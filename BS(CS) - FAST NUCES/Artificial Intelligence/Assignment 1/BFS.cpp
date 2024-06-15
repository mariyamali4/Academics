#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;


class Node {
public:
	int arr[3][3];
//	Node* parent;

	Node() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[i][j] = 0;
			}
		}

	//	parent = nullptr;
	}

	Node(int arr1[3][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[i][j] = arr1[i][j];
			}
		}

	//	parent = nullptr;
	}

	Node(const Node& n) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[i][j] = n.arr[i][j];
			}
		}
	}

	void operator = (const Node& n) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->arr[i][j] = n.arr[i][j];
			}
		}
	}


	bool operator==(const Node& n) const {
		 for (int i = 0; i < 3; i++) {
		      for (int j = 0; j < 3; j++) {
		          if (arr[i][j] != n.arr[i][j]) {
		              return false;
		          }
		      }
		 }
		 return true;
	}

	friend ostream& operator<<(ostream& out, const Node& n) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j == 0)
					out << " |";
				out << n.arr[i][j] << " | ";
			}
			out << endl;
		}
		out << endl;
		return out;
	}





	int getX() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (arr[i][j] == 0)
					return j;
			}
		}
	}

	int getY() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (arr[i][j] == 0)
					return i;
			}
		}
	}




	void moveLeft(int x, int y) {
		int temp = arr[y][x-1];
		arr[y][x-1] = arr[y][x];
		arr[y][x] = temp;
	}

	void moveRight(int x, int y) {
		int temp = arr[y][x + 1];
		arr[y][x + 1] = arr[y][x];
		arr[y][x] = temp;
	}

	void moveUp(int x, int y) {
		int temp = arr[y-1][x];
		arr[y-1][x] = arr[y][x];
		arr[y][x] = temp;
	}

	void moveDown(int x, int y) {
		int temp = arr[y + 1][x];
		arr[y + 1][x] = arr[y][x];
		arr[y][x] = temp;
	}


	bool validMove(int x, int y) {
		if ((x >= 0 && x < 3) && (y >= 0 && y < 3))
			return true;
		else return false;
	}


	bool isEqual(int arr2[3][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (this->arr[i][j] != arr2[i][j])
					return false;
			}
		}
		return true;
	}

	bool isGoal() {
		int goal1[3][3] = { {0,1,2}, {3, 4, 5},{6, 7, 8} };
		int goal2[3][3] = { {1,2,3}, {4, 5, 6},{7, 8, 0} };

		return (isEqual(goal1) || isEqual(goal2));
	}
};



namespace std {
	template <>
	struct hash<Node> {
		size_t operator()(const Node& n) const {
			size_t key = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					key = key * 5 + n.arr[i][j];
				}
			}
			return key;
		}
	};
}




int BFS(Node initial) {
	queue <Node> tree;
	unordered_set <Node> visited;

	int depth = 0;

	tree.push(initial);
	visited.insert(initial);

	while (!tree.empty()) {
		int size = tree.size();
 
		for (int i = 0; i < size; i++) {
			Node curr = tree.front();
			tree.pop();

			if (curr.isGoal()) {
				cout << endl << endl << "--- Goal State ---"<<endl;
				cout<<curr;
				return depth;
			}

			Node child(curr);

		//	cout << curr;

			if (child.validMove(child.getX(), child.getY()-1)) {
				child.moveUp(child.getX(), child.getY());
				
					if (visited.find(child) == visited.end()) {
						tree.push(child);
						visited.insert(child);
					}
				}


			child = curr;
			if (child.validMove(child.getX(), child.getY()+1)) {
				child.moveDown(child.getX(), child.getY());
				
					if (visited.find(child) == visited.end()) {
						tree.push(child);
						visited.insert(child);
					}
				}


			child = curr;
			if (child.validMove(child.getX()-1, child.getY())) {
				child.moveLeft(child.getX(), child.getY());
				
					if (visited.find(child) == visited.end()) {
						tree.push(child);
						visited.insert(child);
					}
				}


			child = curr;
			if (child.validMove(child.getX()+1, child.getY())) {
				child.moveRight(child.getX(), child.getY());
				
					if (visited.find(child) == visited.end()) {
						tree.push(child);
						visited.insert(child);
					}
				}
			

		}
	//	cout << endl << endl<<"------------------------------" << endl;
		depth++;
	}
	return -1;
}








/*
void printPath(Node* n) {
	if (n == nullptr)
		return;
	cout << *n;
	printPath(n->parent);
}


int BFS_V2(Node& initial) {
	queue <Node*> tree;
	unordered_set <Node> visited;

	int depth = 0;

	tree.push(&initial);
	visited.insert(initial);

	while (!tree.empty()) {
		int size = tree.size();

		for (int i = 0; i < size; i++) {
			Node* curr = tree.front();
			tree.pop();

			if ((*curr).isGoal()) {
				cout << endl << endl << "--- Goal State ---" << endl;
				//	cout << curr;
				printPath(curr);
				return depth;
			}

			Node child = *curr;

			//	cout << curr;

			if (child.validMove(child.getX(), child.getY() - 1)) {
				child.moveUp(child.getX(), child.getY());

				if (visited.find(child) == visited.end()) {
					tree.push(&child);
					visited.insert(child);

					child.parent = curr;
				}
			}


			child = *curr;
			if (child.validMove(child.getX(), child.getY() + 1)) {
				child.moveDown(child.getX(), child.getY());

				if (visited.find(child) == visited.end()) {
					tree.push(&child);
					visited.insert(child);

					child.parent = curr;
				}
			}


			Node child = *curr;
			if (child.validMove(child.getX() - 1, child.getY())) {
				child.moveLeft(child.getX(), child.getY());

				if (visited.find(child) == visited.end()) {
					tree.push(&child);
					visited.insert(child);

					child.parent = curr;
				}
			}


			Node child = *curr;
			if (child.validMove(child.getX() + 1, child.getY())) {
				child.moveRight(child.getX(), child.getY());

				if (visited.find(child) == visited.end()) {
					tree.push(&child);
					visited.insert(child);

					child.parent = curr;
				}
			}

		}
		depth++;
	}
	return -1;
}

*/










int main() {
	int arr1[3][3] = { {7,2,4}, {5, 0, 6},{8, 3, 1} };
//	int arr1[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 0, 8} };


	Node initial(arr1);

	cout << endl<< "--- Initial State ---"<<endl;
	cout << initial;
	cout << endl << endl;


	int n = BFS(initial);
	if (n < 0)
		cout << endl << endl << "\t\t\tOops! Given state not solvable!" << endl << endl << endl;
	else cout << endl << endl << "Depth of the tree: " << n << endl;

}