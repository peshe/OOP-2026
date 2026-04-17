#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include "String.hpp"
using namespace std;

class Letter {
    String sender;
    String receiver;
    String content;
    bool read;
    public: 
        Letter(String sender = "", String receiver = "", String content = "") : sender(sender), receiver(receiver), content(content), read(false) {}

        void toggleRead() { read = !read; }
        void markRead() { read = true; }
        void markUnread() { read = false; }

        String getSender() const { return sender; }
        String getReceiver() const { return receiver; }
        String getContent() const { return content; }
        bool isRead() const { return read; }

        void printLetter() const {
            cout << "  From: " << sender.c_str() << "\n";
            cout << "  To:   " << receiver.c_str() << "\n";
            cout << "  Body: " << content.c_str() << "\n";
            cout << "  Read: " << (read ? "yes" : "no") << "\n\n";
        }

        Letter(const char* from, const char* to, const char* body)
            : sender(from), receiver(to), content(body), read(false) {}
};



class Mailbox {
    String address;
    size_t capacity;
    Letter* letters;
    size_t count;
    void writeUint32(ostream& f, uint32_t v) const { 
        f.write(reinterpret_cast<const char*>(&v), sizeof(v));
    }

    void writeStr(ostream& f, const String& s) const{
        writeUint32(f, (uint32_t)s.len);
        f.write(s.data, s.len);
    }

    static uint32_t readUint32(istream& f) {
        uint32_t v; 
        f.read(reinterpret_cast<char*>(&v), sizeof(v));
        return v;
    }

    static String readStr(istream& f) {
        uint32_t len = readUint32(f);
        char* buf = new char[len + 1];
        f.read(buf, len);
        buf[len] = '\0';
        String s(buf);
        delete[] buf;
        return s;
    }

    public:

    String getAddress() const { return address; }
    size_t getCount() const { return count; }
    Letter getLetter(size_t index) const { if (index < count) return letters[index]; return Letter(); }

    Mailbox(const char* addr, size_t cap = 10) : address(addr), capacity(cap), count(0) {
        letters = new Letter[cap];
    }

    Mailbox(const Mailbox&) = delete;
    Mailbox& operator=(const Mailbox&) = delete;

    ~Mailbox() { delete[] letters; }

    bool add(const Letter& letter) {
        if (count >= capacity) {
            cout << "Mailbox full. Letter from " << letter.getSender().c_str() << " rejected.\n";
            return false;
        }
        letters[count++] = letter;
        return true;
    }

    const Letter* readNext() {
        for (size_t i = 0; i < count; i++) {
            if (!letters[i].isRead()) {
                letters[i].markRead();
                return &letters[i];
            }
        }
        return nullptr;
    }

    void deleteRead() {
        size_t newCount = 0;
        for (size_t i = 0; i < count; i++) {
            if (!letters[i].isRead()) {
                if (i != newCount)
                    letters[newCount] = letters[i];
                newCount++;
            }
        }
        for (size_t i = newCount; i < count; i++)
            letters[i] = Letter();
        count = newCount;
    }

    void serialize(const char* filename) const {
        ofstream f(filename, ios::binary);
        writeStr(f, address);
        writeUint32(f, (uint32_t)capacity);
        writeUint32(f, (uint32_t)count);

        size_t flagBytes = (count + 7) / 8;
        unsigned char* flags = new unsigned char[flagBytes]();
        for (size_t i = 0; i < count; i++)
            if (letters[i].isRead())
                flags[i / 8] |= (unsigned char)(1 << (i % 8));
        f.write(reinterpret_cast<const char*>(flags), flagBytes);
        delete[] flags;

        for (size_t i = 0; i < count; i++) {
            writeStr(f, letters[i].getSender());
            writeStr(f, letters[i].getReceiver());
            writeStr(f, letters[i].getContent());
        }
    }

    static Mailbox* deserialize(const char* filename) {
        ifstream f(filename, ios::binary);
        if (!f) return nullptr;

        String address = Mailbox::readStr(f);
        uint32_t capacity = Mailbox::readUint32(f);
        uint32_t count = Mailbox::readUint32(f);

        Mailbox* mb = new Mailbox(address.c_str(), capacity);
        mb->count = count;
        mb->address = address;
        mb->capacity = capacity;

        size_t flagBytes = (count + 7) / 8;
        unsigned char* flags = new unsigned char[flagBytes]();
        f.read(reinterpret_cast<char*>(flags), flagBytes);

        for (uint32_t i = 0; i < count; i++) {
            String k = Mailbox::readStr(f);
            String v = Mailbox::readStr(f);
            String b = Mailbox::readStr(f);
            Letter letter(k, v, b);
            if ((flags[i / 8] >> (i % 8)) & 1)
                letter.markRead();
            else
                letter.markUnread();
            mb->letters[i] = letter;
        }

        delete[] flags;
        return mb;
    }
};



int main() {
    Mailbox mb("sofia@mail.bg", 5);

    mb.add(Letter("alice@mail.bg",  "sofia@mail.bg", "Hello, how are you?"));
    mb.add(Letter("bob@mail.bg",    "sofia@mail.bg", "Meeting tomorrow at 10am."));
    mb.add(Letter("shop@store.com", "sofia@mail.bg", "Your package has arrived."));

    mb.readNext()->printLetter();

    mb.serialize("mailbox.bin");
    cout << "Serialized mailbox to mailbox.bin\n\n";

    Mailbox* loaded = Mailbox::deserialize("mailbox.bin");
    cout << "Deserialized mailbox: " << loaded->getAddress().c_str()
         << " (" << loaded->getCount() << " letters)\n\n";
    for (size_t i = 0; i < loaded->getCount(); i++)
        loaded->getLetter(i).printLetter();

    delete loaded;
    return 0;
}
