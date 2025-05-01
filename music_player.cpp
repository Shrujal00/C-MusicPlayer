#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void listMusicFiles(const string &directory, vector<string> &musicFiles) {
    int index = 1;
    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".mp3") {
            musicFiles.push_back(entry.path().string());
            cout << index++ << ". " << entry.path().filename().string() << endl;
        }
    }
}

int main() {
    string musicFolder = "."; // Current directory
    vector<string> musicFiles;
    
    cout << "Scanning for MP3 files...\n";
    listMusicFiles(musicFolder, musicFiles);

    if (musicFiles.empty()) {
        cout << "No MP3 files found.\n";
        return 0;
    }

    sf::Music music;
    int choice;
    
    cout << "Enter the number of the song to play: ";
    cin >> choice;

    if (choice < 1 || choice > musicFiles.size()) {
        cout << "Invalid choice!\n";
        return 0;
    }

    if (!music.openFromFile(musicFiles[choice - 1])) {
        cout << "Error loading file.\n";
        return 1;
    }

    music.play();
    cout << "Playing: " << musicFiles[choice - 1] << "\n";

    char command;
    while (true) {
        cout << "\nCommands: (p) Pause | (r) Resume | (s) Stop | (q) Quit\n";
        cin >> command;

        if (command == 'p') {
            music.pause();
            cout << "Paused.\n";
        } else if (command == 'r') {
            music.play();
            cout << "Resumed.\n";
        } else if (command == 's') {
            music.stop();
            cout << "Stopped.\n";
            break;
        } else if (command == 'q') {
            music.stop();
            break;
        }
    }

    return 0;
}
