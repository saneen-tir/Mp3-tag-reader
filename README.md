# 🎵 MP3 Tag Reader and Editor in C

A **command-line application** developed in **C** to read and modify MP3 metadata (**ID3 tags**).  
The project focuses on the **ID3v2.3 standard**, allowing users to extract and edit various tag fields embedded in MP3 files.  
It provides a structured and user-friendly interface for working with binary MP3 files, offering both viewing and editing capabilities.

---

## 🚀 Features

- 📖 Read and display **ID3v2.3 metadata** from MP3 files  
- ✏️ Edit and update specific tags such as **Title, Artist, Album, Year, Genre, Track**, and **Comment**  
- 🧾 Display the **ID3 version** and metadata in a clean, structured format  
- 💡 **Help menu (`-h`)** for guidance on command-line usage  
- ⚠️ Proper **error handling** for unsupported, missing, or malformed tags  
- 🧩 **Modular design** for maintainability and easy extension  

---

## 🛠️ Technologies & Concepts

- **C Programming:** Pointers, string manipulation, arrays, and structures  
- **Binary File I/O:** Reading and writing MP3 files  
- **Command-Line Arguments:** Flexible and user-friendly tool usage  
- **Modular Programming:** Separate functions for reading, editing, and validating tags  
- **Debugging & Problem Solving:** Handling edge cases in MP3 metadata  

---

## 📚 Key Learnings

- Gained hands-on experience **parsing binary file structures**  
- Learned the **ID3v2.3 tag format** and how metadata is stored inside MP3 files  
- Practiced **pointer and string manipulation** in C  
- Strengthened understanding of **modular program design**  
- Developed **robust error handling** for real-world data inconsistencies  

---

## 🧩 Usage

To view the help menu and available commands, run:
./a.out -h

To display all available mp3 tags, run:
./a.out -v song.mp3

Example command for editing title tag:
./a.out -e -t song.mp3 "New Title"



```bash
./a.out -h
