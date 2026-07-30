#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void splitUppercaseOnly(const std::string& inputFilename, int n) {
    if (n <= 0) {
        std::cerr << "오류: 분할할 파일 개수는 1 이상이어야 합니다." << std::endl;
        return;
    }

    // 1. 입력 파일 열기
    std::ifstream inFile(inputFilename);
    if (!inFile.is_open()) {
        std::cerr << "오류: 입력 파일을 열 수 없습니다 (" << inputFilename << ")" << std::endl;
        return;
    }

    // 2. N개의 출력 파일 스트림 벡터 생성 및 파일 열기
    std::vector<std::ofstream> outFiles(n);
    for (int i = 0; i < n; ++i) {
        std::string outFilename = "result" + std::to_string(i + 1) + ".txt";
        outFiles[i].open(outFilename);
        if (!outFiles[i].is_open()) {
            std::cerr << "오류: 출력 파일을 생성할 수 없습니다 (" << outFilename << ")" << std::endl;
            return;
        }
    }

    // 3. 문자 단위로 읽어서 대문자만 순서대로 분배
    char ch;
    int index = 0;
    
    while (inFile.get(ch)) {
        // 알파벳 대문자('A' ~ 'Z')인 경우만 필터링
        if (ch >= 'A' && ch <= 'Z') {
            outFiles[index % n].put(ch); // 해당 순서의 파일에 저장
            index++;                     // 대문자가 저장되었을 때만 인덱스 증가
        }
    }

    // 4. 열려있는 모든 파일 닫기
    inFile.close();
    for (int i = 0; i < n; ++i) {
        outFiles[i].close();
    }

    std::cout << "성공: 대문자만 추출하여 " << n << "개의 파일로 분할 완료했습니다." << std::endl;
}

int main(int argc, char* argv[]) {
    // 테스트용 임시 파일 생성 (소문자, 숫자, 공백이 섞여 있는 예시)
    std::string testFilename = argv[1];
    int splitCount;
    std::cout << "분할할 파일의 개수를 입력하세요 (예: 3): ";
    std::cin >> splitCount;

    // 분할 함수 호출
    splitUppercaseOnly(testFilename, splitCount);

    return 0;
}

