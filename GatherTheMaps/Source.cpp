#include <iostream>
#include <cstring>

constexpr int NUM_OF_DAYS = 31;
bool dp[50][50] = { {false} }; //地図を所持しているかどうか [人][地図] = hasMap
bool isFree[50][31] = { {false} };

int main() {
	int n;
	while (std::cin >> n && n) {
		bool next = false;
		std::memset(dp, false, 50*50);
		std::memset(isFree, false, 50*31);
		for (int i = 0; i < n; i++) {
			int f;
			std::cin >> f;
			//100%集まらない
			if (!f) {
				std::cout << -1 << std::endl;
				next = true;
			}
			for (int j = 0; j < f; j++) {
				int day;
				std::cin >> day;
				isFree[i][day] = true;
			}
		}
		if (next) continue;
		for (int i = 0; i < n; i++) {
			dp[i][i] = true;
		}

		bool isOk[50] = { false };
		for (int i = 1; i < NUM_OF_DAYS; i++) {
			//予定が空いている人を探す
			for (int j = 0; j < n; j++) {
				isOk[j] = isFree[j][i];
			}

			//予定が開いている人の間で、地図を結合
			for (int j = 0; j < n; j++) { //人
				if (!isFree[j][i]) continue; //その人は予定が空いていない
				for (int k = 0; k < n; k++) { //地図融合 人
					if (isOk[k]) {
						for (int l = 0; l < n; l++) { //地図
							dp[j][l] = dp[j][l] || dp[k][l];
						}
					}
				}
			}

			//集まったかどうか
			for (int j = 0; j < n && !next; j++) {
				bool isGather = true;
				for (int k = 0; k < n; k++) {
					isGather = isGather && dp[j][k];
				}
				if (isGather) {
					std::cout << i << std::endl;
					next = true;
				}
			}
		}
		if (!next) std::cout << -1 << std::endl;
	}
	return 0;
}
