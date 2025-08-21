// ProjectTwo.cpp
// Nicholas Justus – CS300 Project Two: Advising Assistance Program

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for holding course information
struct Course {
    string courseId;                 // e.g. CSCI100
    string name;                     // e.g. Introduction to CS
    vector<string> prerequisites;    // list of course IDs
};

// Simple hash table using vector<Course> buckets
class HashTable {
private:
    static const unsigned int DEFAULT_SIZE = 179;
    vector<vector<Course>> buckets;

    unsigned int hashFunc(string key) {
        unsigned int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % DEFAULT_SIZE;
    }

public:
    HashTable() {
        buckets.resize(DEFAULT_SIZE);
    }

    void Insert(Course course) {
        unsigned int idx = hashFunc(course.courseId);
        buckets[idx].push_back(course);
    }

    Course* Search(string courseId) {
        unsigned int idx = hashFunc(courseId);
        for (auto& c : buckets[idx]) {
            if (c.courseId == courseId)
                return &c;
        }
        return nullptr;
    }

    vector<Course> GetAll() {
        vector<Course> allCourses;
        for (auto& bucket : buckets) {
            for (auto& course : bucket) {
                allCourses.push_back(course);
            }
        }
        return allCourses;
    }
};

// Loads courses from file INTO hash table
void loadCourses(const string& filename, HashTable& table) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file,
