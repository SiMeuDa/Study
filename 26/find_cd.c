/* AI GENERATED */
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

char found_path[1024] = "";
int match_count = 0; // 찾은 폴더 개수를 저장할 변수

void find_dir_recursive(const char *base_path, const char *target_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    if (!(dir = opendir(base_path))) return;

    while ((entry = readdir(dir)) != NULL) {
        // 이미 2개 이상 찾았으면 더 이상 탐색할 필요 없음
        if (match_count >= 2) break;

        char path[1024];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);
        if (lstat(path, &statbuf) == -1) continue;

        if (S_ISDIR(statbuf.st_mode)) {
            // 이름이 일치하는 폴더를 찾았을 때
            if (strcmp(entry->d_name, target_name) == 0) {
                match_count++;
                if (match_count == 1) {
                    strcpy(found_path, path); // 첫 번째 경로는 저장
                }
            }
            // 하위 폴더 계속 탐색
            find_dir_recursive(path, target_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: fcd <directory_name>\n");
        return 1;
    }

    find_dir_recursive(".", argv[1]);

    if (match_count == 1) {
        // 정확히 1개만 찾았을 때만 cd 명령어 출력
        printf("cd %s\n", found_path);
    } else if (match_count >= 2) {
        // 2개 이상일 때 요청하신 에러 메시지 출력
        printf("[Error]: There is more than two path\n");
    } else {
        // 못 찾았을 때
        printf("[Error]: There is no Directory\n");
    }

    return 0;
}

