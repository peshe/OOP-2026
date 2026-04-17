#include <cstring>
#include <fstream>
#include <iostream>
#include "String.hpp"
using namespace std;

enum Genre { NONE = 0, POP = 1, ROCK = 2, JAZZ = 4, CLASSICAL = 8, OTHER = 16 };

class Artist {
    String alias;
    unsigned int genres;

public:
    Artist() : genres(NONE) {}
    Artist(const char* name, unsigned int g = NONE) : alias(name), genres(g) {}

    const char* getAlias() const { return alias.c_str(); }
    unsigned int getGenres() const { return genres; }
};

class Song {
    String title;
    unsigned int duration;
    Artist* artist;

public:
    Song() : duration(0), artist(nullptr), title("") {}
    Song(const char* t, unsigned int d, Artist* a) : title(t), duration(d), artist(a) {}

    const char* getTitle() const { return title.c_str(); }
    unsigned int getDuration() const { return duration; }
    Artist* getArtist() const { return artist; }

    void print(ostream& out) const {
        out << title.c_str() << " | "
            << (artist ? artist->getAlias() : "Unknown")
            << " | " << duration << "s\n";
    }
};

class Playlist {
    String name;
    Song* songs;
    size_t count;
    size_t capacity;

    void grow() {
        size_t newCap = capacity == 0 ? 2 : capacity * 2;
        Song* grown = new Song[newCap];
        for (size_t i = 0; i < count; i++)
            grown[i] = songs[i];
        delete[] songs;
        songs = grown;
        capacity = newCap;
    }

public:
    Playlist(const char* n) : name(n), songs(nullptr), count(0), capacity(0) {}

    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    ~Playlist() { delete[] songs; }

    void add(const Song& song) {
        if (count >= capacity) grow();
        songs[count++] = song;
    }

    void remove(const char* title) {
        for (size_t i = 0; i < count; i++) {
            if (strcmp(songs[i].getTitle(), title) == 0) {
                for (size_t j = i; j < count - 1; j++)
                    songs[j] = songs[j + 1];
                songs[count - 1] = Song();
                count--;
                return;
            }
        }
        cout << "Song \"" << title << "\" not found.\n";
    }

    unsigned int totalDuration() const {
        unsigned int total = 0;
        for (size_t i = 0; i < count; i++)
            total += songs[i].getDuration();
        return total;
    }

    void generateReport() const {
        const char* prefix = "report_";
        const char* suffix = ".txt";
        size_t len = strlen(prefix) + name.length() + strlen(suffix);
        char* filename = new char[len + 1];
        strcpy(filename, prefix);
        strcat(filename, name.c_str());
        strcat(filename, suffix);

        ofstream f(filename);
        for (size_t i = 0; i < count; i++)
            songs[i].print(f);

        cout << "Report written to " << filename << "\n";
        delete[] filename;
    }
};

int main() {
    Artist beatles("The Beatles", POP | ROCK);
    Artist miles("Miles Davis", JAZZ);

    Song s1("Hey Jude",      431, &beatles);
    Song s2("Come Together", 259, &beatles);
    Song s3("Kind of Blue",  562, &miles);
    Song s4("Orphan Track",  180, nullptr);

    Playlist pl("MyPlaylist");
    pl.add(s1);
    pl.add(s2);
    pl.add(s3);
    pl.add(s4);

    cout << "Total duration: " << pl.totalDuration() << "s\n";
    pl.generateReport();

    pl.remove("Come Together");
    cout << "After removal, total duration: " << pl.totalDuration() << "s\n";
    pl.generateReport();

    return 0;
}
