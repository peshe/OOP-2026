# Задачи
## Задача 1
- Напишете структура която да пази информацията за файла.
## Задача 2
- Дефинирайте функциите `File* openFile(const char* filename, bool append, bool readonly, bool writeonly, bool readwrite)`
## Задача 3
- Дефинирайте функциите `void deleteFile(File? f)`
## Задача 4
- Дефинирайте функциите `const char* getFileName(File* f)`
## Задача 5
- Дефинирайте функцията `char* readFile(File* f, size_t size)`
## Задача 6
- Дефинирайте функцията `bool writeFile(File* f, const char* buff)`
## Задача 7
- Дефинирайте функцията `const char* rootFilepath()` и `const char* baseFilePath()`, които връщат "/" и "./".
## Задача 8
- Дефинирайте функцията `char* addFolder(const char* path, const char* folder)`, което добавя директория към подадения път.
## Задача 9
- Дефинирайте функцията `char* addFile(const char* path, const char* path)`, което добавя файл към подадения път.
## Задача 10
- Дефинирайте функцията `bool gotoStart(File* f)` - премества локацията на файловия указател в началото.
## Задача 11
- Дефинирайте функцията `char* readLine(File* f)` - чете един ред.
## Задача 12
- Дефинирайте функцията `bool isFileEmpty(File* f)` - казва дали файла е празен.
## Задача 13
- Дефинирайте функцията `bool fileSize(File* f)` - казва размера на файла.
