#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;        // encapsulated data
    int rollNo;
    double marks;
    static int count;   // shared by all Student objects (Week 5)

public:
    // Parameterized constructor with member initializer list (Week 3)
    Student(const string &n, int r, double m) : name(n), rollNo(r), marks(m) {
        ++count;
    }

    // Copy constructor - keeps the static counter correct for copies
    Student(const Student &other) : name(other.name), rollNo(other.rollNo), marks(other.marks) {
        ++count;
    }

    // Destructor - object dies, count goes down
    ~Student() {
        --count;
    }

    // Getters are const: they don't modify the object (Week 4)
    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
    double getMarks() const { return marks; }

    // Overloaded functions (Week 2): same name, different parameters
    void setMarks(double m) { // single total
        if (m >= 0 && m <= 100)
            marks = m;
        else
            cout << "Invalid marks, ignored.\n";
    }

    void setMarks(double m1, double m2, double m3) { // average of three tests
        setMarks((m1 + m2 + m3) / 3.0);
    }

    // Static member function: no 'this', only touches static data
    static int getCount() {
        return count;
    }

    // Overloaded > operator (Week 6): compare by marks
    bool operator>(const Student &rhs) const {
        return marks > rhs.marks;
    }

    // Friend functions (Week 5): non-members that can see private data
    friend ostream &operator<<(ostream &os, const Student &s);
    friend char grade(const Student &s);
};

// Static data member defined exactly once outside the class
int Student::count = 0;

ostream &operator<<(ostream &os, const Student &s) {
    os << "Name: " << s.name << " | Roll: " << s.rollNo << " | Marks: " << s.marks;
    return os;
}

char grade(const Student &s) {
    if (s.marks >= 90) return 'A';
    if (s.marks >= 75) return 'B';
    if (s.marks >= 60) return 'C';
    if (s.marks >= 40) return 'D';
    return 'F';
}

int main() {
    cout << "Students at start: " << Student::getCount() << "\n";

    Student s1("Asha", 101, 82.5);
    Student s2("Ravi", 102, 67.0);
    Student s3("Meena", 103, 0);

    cout << "Students after creating 3: " << Student::getCount() << "\n";

    // Overloaded setMarks
    s3.setMarks(91.0);          // single value
    s2.setMarks(70, 80, 90);    // average of 3 tests = 80
    s1.setMarks(150);           // invalid, rejected

    cout << s1 << " | Grade: " << grade(s1) << "\n";
    cout << s2 << " | Grade: " << grade(s2) << "\n";
    cout << s3 << " | Grade: " << grade(s3) << "\n";

    // Overloaded > operator
    cout << "Is " << s1.getName() << " > " << s2.getName() << "? "
         << (s1 > s2 ? "Yes" : "No") << "\n";
    cout << "Is " << s2.getName() << " > " << s3.getName() << "? "
         << (s2 > s3 ? "Yes" : "No") << "\n";

    // Scope block shows destructor + static count going back down
    {
        Student temp("Temp", 999, 50);
        cout << "Inside block, count: " << Student::getCount() << "\n";
    }

    cout << "After block, count: " << Student::getCount() << "\n";

    return 0;
}
