#include <iostream>
#include <vector>
#include <queue>
#define ENDL '\n'
#define INF 99999999

using namespace std;
using ll = long long;

int N, E;

void Dijkstra(vector<vector<pair<int, int>>>& pathTable, vector<int>& shortestTable, int start);

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> E;
	int start = 1;
	int dest = N;
	int mustV1, mustV2;
	vector<vector<pair<int, int>>>pathTable(N + 1);
	vector<int>shortestTableOfStart(N + 1, INF);
	vector<int>shortestTableOfMustV1(N + 1, INF);
	vector<int>shortestTableOfMustV2(N + 1, INF);

	for (int i = 0; i < E; i++) {
		int vertex1, vertex2, weight;
		cin >> vertex1 >> vertex2 >> weight;
		pathTable[vertex1].push_back(make_pair(vertex2, weight));
		pathTable[vertex2].push_back(make_pair(vertex1, weight));
	}
	cin >> mustV1 >> mustV2;

	Dijkstra(pathTable, shortestTableOfStart, start);
	Dijkstra(pathTable, shortestTableOfMustV1, mustV1);
	Dijkstra(pathTable, shortestTableOfMustV2, mustV2);

	int path1 = shortestTableOfStart[mustV1] + shortestTableOfMustV1[mustV2] + shortestTableOfMustV2[dest];
	int path2 = shortestTableOfStart[mustV2] + shortestTableOfMustV2[mustV1] + shortestTableOfMustV1[dest];
	int shortestToDest = min(path1, path2);
	
	if (shortestToDest >= INF) cout << -1;
	else cout << shortestToDest;
	
	return 0;
}
void Dijkstra(vector<vector<pair<int, int>>>& pathTable, vector<int>& shortestTable, int start) {
	priority_queue<pair<int, int>>pq;
	vector<bool> visited(N + 1, false);
	pq.push(make_pair(0, start));
	shortestTable[start] = 0;
	while (!pq.empty()) {
		int nextIDX = pq.top().second;
		int nextIDXWeight = -pq.top().first;
		pq.pop();
		if (visited[nextIDX] == true)continue;
		visited[nextIDX] = true;
		for (auto x : pathTable[nextIDX]) {
			int next2IDX = x.first;
			int next2IDXWeight = x.second;
			if (visited[next2IDX] == true) continue;
			if (shortestTable[next2IDX] > nextIDXWeight + next2IDXWeight) {
				shortestTable[next2IDX] = nextIDXWeight + next2IDXWeight;
				pq.push(make_pair(-(nextIDXWeight + next2IDXWeight), next2IDX));
			}
		}

	}
}